from signatures import D0Atom, D0Vec, D0Func
from expressions import D0Var, D0Apply
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
)
from primitives import (
    ones_mat,
    rand_mat,
    mat_transpose,
    mat_add,
    mat_mul,
)


# z = A^T * A * x + y

N = 16
var_A = D0Var("A", D0Vec(D0Atom("float"), N * N))
var_x = D0Var("x", D0Vec(D0Atom("float"), N))
var_y = D0Var("y", D0Vec(D0Atom("float"), N))
var_z = D0Var("z", D0Vec(D0Atom("float"), N))
var_transpose = D0Var(
    "transpose", D0Func([D0Vec(D0Atom("float"), N * N)], D0Vec(D0Atom("float"), N * N))
)
var_vadd = D0Var(
    "vadd",
    D0Func(
        [D0Vec(D0Atom("float"), N), D0Vec(D0Atom("float"), N)],
        D0Vec(D0Atom("float"), N),
    ),
)
var_mmul = D0Var(
    "mmul",
    D0Func(
        [D0Vec(D0Atom("float"), N * N), D0Vec(D0Atom("float"), N * N)],
        D0Vec(D0Atom("float"), N * N),
    ),
)
var_mvul = D0Var(
    "mvul",
    D0Func(
        [D0Vec(D0Atom("float"), N * N), D0Vec(D0Atom("float"), N)],
        D0Vec(D0Atom("float"), N),
    ),
)

f = D0Apply(
    var_vadd,
    [
        D0Apply(
            var_mvul,
            [D0Apply(var_mmul, [D0Apply(var_transpose, [var_A]), var_A]), var_x],
        ),
        var_y,
    ],
)

# print(f)

name_mapping = {
    # "A": rand_mat[f"rand_mat_{N}x{N}"],
    "A": D0MakeInput("A", D0Atom("float"), N * N),
    "x": D0MakeInput("x", D0Atom("float"), N),
    # "y": D0MakeInput("y", D0Atom("float"), N),
    "y": rand_mat[f"rand_mat_{N}x{1}"],
    "transpose": mat_transpose[f"mat_transpose_{N}x{N}"],
    "vadd": mat_add[f"mat_add_{N}x{1}"],
    "mmul": mat_mul[f"mat_mul_{N}x{N}x{N}"],
    "mvul": mat_mul[f"mat_mul_{N}x{N}x{1}"],
}
# print(name_mapping)

concrete_f = make_concrete_expr(f, name_mapping)
# print("// " + repr(concrete_f))
head = "void slow_performance("
heads = []
for v in name_mapping.values():
    if isinstance(v, D0MakeInput):
        param_def = f"{v.sig.t_element}* {v.name}"
        heads.append(param_def)
param_def = f"{f.func.sig.t_to.t_element}* result"
heads.append(param_def)
head += ",".join(heads)
head += ") {"
print(head)
cnt, res = emit_concrete_expr(concrete_f)
print(
    f"for (int i_{cnt} = 0; i_{cnt} < {f.func.sig.t_to.size}; i_{cnt}++) result[i_{cnt}] = {res}[i_{cnt}]; }}"
)

for v in name_mapping.values():
    if isinstance(v, D0MakeInput):
        param_def = f"// {v.name} {v.sig.t_element} {v.sig.size}"
        print(param_def)
param_def = f"// result {f.func.sig.t_to.t_element} {f.func.sig.t_to.size}"
print(param_def)
