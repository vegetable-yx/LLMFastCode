from signatures import D0Atom, D0Vec, D0Func
from expressions import D0Expr, D0Var, D0Apply, collect_var_name_sig
from concrete import (
    D0Primitive,
    D0ConcreteExpr,
    D0ConcreteExprPrimitive,
    D0ConcreteExprApply,
    make_concrete_expr,
    D0MakeInput,
    D0MakeConst,
    D0MakeFunc,
    emit_concrete_expr,
    compute_concrete_expr_depth,
    collect_concrete_expr_inputs,
)
from primitives import (
    ones_mat,
    mat_transpose,
    mat_add,
    mat_mul,
)
from itertools import product
from random import sample, shuffle, choice

sizes = sorted(list(set([j * (2**i) for i in range(4, 8) for j in range(1, 2)])))

vars = [D0Var(f"A_{i}", D0Vec(D0Atom("float"), i)) for i in sizes]
funcs = [
    D0Var(f"f1_{i}_{j}", D0Func([D0Vec(D0Atom("float"), i)], D0Vec(D0Atom("float"), j)))
    for i in sizes
    for j in sizes
] + [
    D0Var(
        f"f2_{i}_{j}_{k}",
        D0Func(
            [D0Vec(D0Atom("float"), i), D0Vec(D0Atom("float"), j)],
            D0Vec(D0Atom("float"), k),
        ),
    )
    for i in sizes
    for j in sizes
    for k in sizes
]

concrete_vars = (
    [D0MakeInput(f"x_{i}", D0Atom("float"), i) for i in sizes]
    + [D0MakeInput(f"y_{i}", D0Atom("float"), i) for i in sizes]
    + [D0MakeInput(f"z_{i}", D0Atom("float"), i) for i in sizes]
    + list(mat_transpose.values())
    + list(mat_add.values())
    + list(mat_mul.values())
)

typed_concrete_vars = {}
for v in concrete_vars:
    sig = v.sig
    if repr(v.sig) not in typed_concrete_vars:
        typed_concrete_vars[repr(v.sig)] = []
    typed_concrete_vars[repr(v.sig)].append(v)

# print(typed_concrete_vars)

exprs: list[D0Expr] = [] + vars + funcs
typed_exprs = {}
for v in exprs:
    sig = v.sig
    if repr(v.sig) not in typed_exprs:
        typed_exprs[repr(v.sig)] = []
    typed_exprs[repr(v.sig)].append(v)


for round in range(2):
    tmp = []
    for f in exprs:
        if isinstance(f.sig, D0Func):
            # print(f)
            for args in product(*[typed_exprs[repr(t_arg)] for t_arg in f.sig.t_from]):
                # for args in product(exprs, repeat=len(f.sig.t_from)):
                try:
                    e = D0Apply(f, list(args))
                    tmp.append(e)
                    # print(e)
                except:
                    pass

    for v in tmp:
        sig = v.sig
        if repr(v.sig) not in typed_exprs:
            typed_exprs[repr(v.sig)] = []
        typed_exprs[repr(v.sig)].append(v)

    exprs += tmp
    # exprs = sample(exprs, len(exprs) // 2)

# print(len(exprs))
# shuffle(exprs)

results = []
i = 0
for i in range(len(exprs)):
    try:
        expr = choice(exprs)
        name_sig = collect_var_name_sig(expr)
        name_mapping = {
            name: choice(typed_concrete_vars[repr(sig)])
            for name, sig in name_sig.items()
        }
        # print(name_sig)
        # print(name_mapping)
        # print()
        results.append((make_concrete_expr(expr, name_mapping), name_mapping))
    except:
        pass
# print(len(results))


def emit_code(concrete_expr: D0ConcreteExpr, name_mapping: dict):
    # print("// " + repr(concrete_expr))
    for v in name_mapping.values():
        if isinstance(v, D0MakeInput):
            param_def = f"// {v.name} {v.sig.t_element} {v.sig.size}"
            print(param_def)
    param_def = f"// result {concrete_expr.func.sig.t_to.t_element} {concrete_expr.func.sig.t_to.size}"
    print(param_def)

    head = "void slow_performance("
    heads = []
    for v in name_mapping.values():
        if isinstance(v, D0MakeInput):
            param_def = f"{v.sig.t_element}* {v.name}"
            heads.append(param_def)
    param_def = f"{concrete_expr.func.sig.t_to.t_element}* result"
    heads.append(param_def)
    head += ",".join(heads)
    head += ") {"
    print(head)
    cnt, res = emit_concrete_expr(concrete_expr)
    print(
        f"for (int i_{cnt} = 0; i_{cnt} < {concrete_expr.func.sig.t_to.size}; i_{cnt}++) result[i_{cnt}] = {res}[i_{cnt}]; }}"
    )

    # for v in name_mapping.values():
    #     if isinstance(v, D0MakeInput):
    #         param_def = f"// {v.name} {v.sig.t_element} {v.sig.size}"
    #         print(param_def)
    # param_def = f"// result {f.func.sig.t_to.t_element} {f.func.sig.t_to.size}"
    # print(param_def)
    print("/*" + "*" * 80 + "*/")


shuffle(results)
cnt = 0
for fe, name_mapping in results:
    if compute_concrete_expr_depth(fe) < 2:
        continue
    emit_code(fe, name_mapping)
    cnt += 1
    if cnt == 100:
        break
