from signatures import (
    D0Type,
    D0Atom,
    D0Vec,
    D0Func,
    typecheck_D0,
    check_type_eq,
    check_apply,
)
from expressions import D0Expr, D0Var, D0Apply
from concrete import (
    D0Primitive,
    D0ConcreteExpr,
    D0ConcreteExprPrimitive,
    D0ConcreteExprApply,
    make_concrete_expr,
    D0MakeInput,
    D0MakeConst,
    D0MakeFunc,
)
import random

BASE = 7
STEP = 4
N = sorted(
    list(set([j * (2**i) for i in range(0, STEP + BASE) for j in range(1, 5)]))
)
# print(N)

ones_mat = {
    f"ones_mat_{i}x{j}": D0MakeConst(
        f"ones_mat_{i}x{j}", D0Atom("float"), i * j, [1.0 for _ in range(i * j)]
    )
    for i in N
    for j in N
}

# rand_mat = {
#     f"rand_mat_{i}x{j}": D0MakeConst(
#         f"rand_mat_{i}x{j}",
#         D0Atom("float"),
#         i * j,
#         [float(random.randint(-10, 10)) for _ in range(i * j)],
#     )
#     for i in N
#     for j in N
# }


def gen_mat_transpose(i: int, j: int):
    def do_emit(self: D0MakeFunc, ctr: int, arg_temps: list[str]):
        assert len(arg_temps) == 1
        c = ctr
        c += 1
        tmp_var = f"tmp_{c}"
        print(f"{self.sig.t_to.t_element} {tmp_var}[{i}*{j}];")
        print(f"for (int i_{c} = 0; i_{c} < {i}; i_{c}++) {{")
        print(f"for (int j_{c} = 0; j_{c} < {j}; j_{c}++) {{")
        print(f"tmp_{c}[j_{c}*{i} + i_{c}] = {arg_temps[0]}[i_{c}*{j} + j_{c}];")
        print(f"}}")
        print(f"}}")
        return c, tmp_var

    return do_emit


mat_transpose = {
    f"mat_transpose_{i}x{j}": D0MakeFunc(
        f"mat_transpose_{i}x{j}",
        D0Func([D0Vec(D0Atom("float"), i * j)], D0Vec(D0Atom("float"), i * j)),
        do_emit=gen_mat_transpose(i, j),
    )
    for i in N
    for j in N
}


def gen_mat_add(i: int, j: int):
    def do_emit(self: D0MakeFunc, ctr: int, arg_temps: list[str]):
        assert len(arg_temps) == 2
        c = ctr
        c += 1
        tmp_var = f"tmp_{c}"
        print(f"{self.sig.t_to.t_element} {tmp_var}[{i}*{j}];")
        print(f"for (int i_{c} = 0; i_{c} < {i}; i_{c}++) {{")
        print(f"for (int j_{c} = 0; j_{c} < {j}; j_{c}++) {{")
        print(
            f"tmp_{c}[i_{c}*{j} + j_{c}] = {arg_temps[0]}[i_{c}*{j} + j_{c}]+{arg_temps[1]}[i_{c}*{j} + j_{c}];"
        )
        print(f"}}")
        print(f"}}")
        return c, tmp_var

    return do_emit


mat_add = {
    f"mat_add_{i}x{j}": D0MakeFunc(
        f"mat_add_{i}x{j}",
        D0Func(
            [D0Vec(D0Atom("float"), i * j), D0Vec(D0Atom("float"), i * j)],
            D0Vec(D0Atom("float"), i * j),
        ),
        do_emit=gen_mat_add(i, j),
    )
    for i in N
    for j in N
}


def gen_mat_mul(i: int, j: int, k: int):
    def do_emit(self: D0MakeFunc, ctr: int, arg_temps: list[str]):
        assert len(arg_temps) == 2
        c = ctr
        c += 1
        tmp_var = f"tmp_{c}"
        print(f"{self.sig.t_to.t_element} {tmp_var}[{i}*{k}];")
        print(f"for (int i_{c} = 0; i_{c} < {i}; i_{c}++) {{")
        print(f"for (int k_{c} = 0; k_{c} < {k}; k_{c}++) {{")
        print(f"tmp_{c}[i_{c}*{k} + k_{c}] = 0;")
        print(f"for (int j_{c} = 0; j_{c} < {j}; j_{c}++) {{")
        print(
            f"tmp_{c}[i_{c}*{k} + k_{c}] += {arg_temps[0]}[i_{c}*{j} + j_{c}]*{arg_temps[1]}[j_{c}*{k} + k_{c}];"
        )
        print(f"}}")
        print(f"}}")
        print(f"}}")
        return c, tmp_var

    return do_emit


mat_mul = {
    f"mat_mul_{i}x{j}x{k}": D0MakeFunc(
        f"mat_mul_{i}x{j}x{k}",
        D0Func(
            [D0Vec(D0Atom("float"), i * j), D0Vec(D0Atom("float"), j * k)],
            D0Vec(D0Atom("float"), i * k),
        ),
        do_emit=gen_mat_mul(i, j, k),
    )
    for i in N
    for j in N
    for k in N
}
