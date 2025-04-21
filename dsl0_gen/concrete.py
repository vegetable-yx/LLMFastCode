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


class D0Primitive:
    def __init__(self, name: str, sig: D0Atom):
        self.sig: D0Type = sig
        self.name = f"p_{name}"
        # self.impl_head: str = None
        # self.impl_body: str = None


class D0ConcreteExpr:
    def __init__(self):
        self.sig: D0Type = None


class D0ConcreteExprPrimitive(D0ConcreteExpr):
    def __init__(self, x: D0Primitive):
        assert typecheck_D0(x.sig)
        self.x = x
        self.sig = x.sig

    def __repr__(self):
        return self.x.__repr__()


class D0ConcreteExprApply(D0ConcreteExpr):
    def __init__(self, func: D0ConcreteExpr, xs: list[D0ConcreteExpr]):
        assert isinstance(func.sig, D0Func)
        assert typecheck_D0(func.sig)
        for x in xs:
            assert typecheck_D0(x.sig)
        assert check_apply(func.sig, [x.sig for x in xs])
        self.sig = func.sig.t_to
        self.func = func
        self.xs = xs

    def __repr__(self):
        return f"CApp({self.func.__repr__()}, {self.xs.__repr__()})"


def make_concrete_expr(
    expr: D0Expr, name_mapping: dict[str, D0Primitive]
) -> D0ConcreteExpr:
    if isinstance(expr, D0Var):
        if expr.name not in name_mapping:
            raise ValueError(f"Variable '{expr.name}' not found in name_mapping")

        primitive = name_mapping[expr.name]
        if not check_type_eq(expr.sig, primitive.sig):
            raise ValueError(
                f"Type mismatch for variable '{expr.name}': "
                f"expected {expr.sig}, got {primitive.sig}"
            )

        return D0ConcreteExprPrimitive(primitive)

    elif isinstance(expr, D0Apply):
        concrete_func = make_concrete_expr(expr.func, name_mapping)
        concrete_args = [make_concrete_expr(xe, name_mapping) for xe in expr.xs]

        return D0ConcreteExprApply(concrete_func, concrete_args)
    else:
        raise TypeError(f"Unsupported expression type: {type(expr)}")


class D0MakeInput(D0Primitive):
    def __init__(self, name: str, sig: D0Atom, size: int):
        self.sig: D0Vec = D0Vec(sig, size)
        self.name = f"i_{name}"

    def __repr__(self):
        return f"INPUT[{self.name}]"

    def emit(self, ctr: int):
        c = ctr
        c += 1
        tmp_var = f"tmp_{c}"
        code = f"{self.sig.t_element}* {tmp_var} = {self.name};"
        print(code)
        return c, tmp_var


class D0MakeConst(D0Primitive):
    def __init__(self, name: str, sig: D0Atom, size: int, values: list):
        assert len(values) == size
        self.sig: D0Vec = D0Vec(sig, size)
        self.name = f"c_{name}"
        self.values = values

    def __repr__(self):
        return f"{self.name}"

    def emit(self, ctr: int):
        c = ctr
        c += 1
        tmp_var = f"tmp_{c}"
        code = f"{self.sig.t_element} {tmp_var}[{self.sig.size}] = {{ {','.join([str(i) for i in self.values])} }};"
        print(code)
        return c, tmp_var


class D0MakeFunc(D0Primitive):
    def __init__(self, name: str, sig: D0Func, do_emit):
        self.sig: D0Func = sig
        self.name = f"f_{name}"
        self.do_emit = do_emit

    def __repr__(self):
        return f"{self.name}"

    def emit(self, ctr: int, arg_temps: list[str]):
        return self.do_emit(self, ctr, arg_temps)


def emit_concrete_expr(expr: D0ConcreteExpr, cnt: int = 0):
    c = cnt
    if isinstance(expr, D0ConcreteExprPrimitive):
        if isinstance(expr.x, D0MakeInput):
            return expr.x.emit(c)
        elif isinstance(expr.x, D0MakeConst):
            return expr.x.emit(c)
        elif isinstance(expr.x, D0MakeFunc):
            raise NotImplementedError("Should not emit function here")
    elif isinstance(expr, D0ConcreteExprApply):
        arg_tmp_names = []
        for arg_x in expr.xs:
            c, tmp = emit_concrete_expr(arg_x, c)
            arg_tmp_names.append(tmp)
        return expr.func.x.emit(c, arg_tmp_names)
    raise NotImplementedError("Unreachable")


def compute_concrete_expr_depth(expr: D0ConcreteExpr) -> int:
    """
    Computes the depth of a concrete expression tree.

    The depth is defined as:
    - 0 for primitive expressions (leaf nodes)
    - 1 + max(depth of all subexpressions) for application expressions

    Args:
        expr: A D0ConcreteExpr to analyze

    Returns:
        The depth of the expression tree
    """
    if isinstance(expr, D0ConcreteExprPrimitive):
        # Primitive expressions are leaf nodes, so their depth is 0
        return 0
    elif isinstance(expr, D0ConcreteExprApply):
        # For applications, compute depth of function and all arguments
        func_depth = compute_concrete_expr_depth(expr.func)

        # Find the maximum depth among all arguments
        max_arg_depth = 0
        for arg in expr.xs:
            arg_depth = compute_concrete_expr_depth(arg)
            max_arg_depth = max(max_arg_depth, arg_depth)

        # The depth is 1 plus the maximum depth of function and arguments
        return 1 + max(func_depth, max_arg_depth)
    else:
        raise TypeError(f"Unsupported expression type: {type(expr)}")


def collect_concrete_expr_inputs(expr: D0ConcreteExpr) -> list[D0MakeInput]:
    """
    Collects all input nodes from a concrete expression tree.

    Args:
        expr: A D0ConcreteExpr to analyze

    Returns:
        A list of all D0MakeInput objects found in the expression
    """
    inputs = []

    if isinstance(expr, D0ConcreteExprPrimitive):
        # Check if this primitive is an input
        if isinstance(expr.x, D0MakeInput):
            inputs.append(expr.x)
    elif isinstance(expr, D0ConcreteExprApply):
        # Recursively collect inputs from the function
        inputs.extend(collect_concrete_expr_inputs(expr.func))

        # Recursively collect inputs from all arguments
        for arg in expr.xs:
            inputs.extend(collect_concrete_expr_inputs(arg))
    else:
        raise TypeError(f"Unsupported expression type: {type(expr)}")

    return inputs
