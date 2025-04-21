from signatures import (
    D0Type,
    D0Func,
    typecheck_D0,
    check_apply,
)


class D0Expr:
    def __init__(self):
        self.sig: D0Type = None


class D0Var(D0Expr):
    def __init__(self, name: str, sig: D0Type):
        assert typecheck_D0(sig)
        self.sig = sig
        self.name = name

    def __repr__(self):
        return f"Var_{self.name}"


class D0Apply(D0Expr):
    def __init__(self, func: D0Expr, xs: list[D0Expr]):
        assert isinstance(func.sig, D0Func)
        assert typecheck_D0(func.sig)
        for x in xs:
            assert typecheck_D0(x.sig)
        assert check_apply(func.sig, [x.sig for x in xs])
        self.sig = func.sig.t_to
        self.func = func
        self.xs = xs

    def __repr__(self):
        return f"Apply({self.func.__repr__()}, {self.xs.__repr__()})"


def collect_var_name_sig(expr: D0Expr) -> dict[str, D0Type]:
    """
    Collects all variable names and their signatures from a D0Expr.

    Args:
        expr: A D0Expr object to analyze

    Returns:
        A dictionary mapping variable names to their signatures
    """
    result = {}

    if isinstance(expr, D0Var):
        # If it's a variable, add its name and signature to the result
        result[expr.name] = expr.sig
    elif isinstance(expr, D0Apply):
        # If it's an application, collect variables from the function and arguments

        # Process the function part
        func_vars = collect_var_name_sig(expr.func)
        result.update(func_vars)

        # Process all the arguments
        for arg in expr.xs:
            arg_vars = collect_var_name_sig(arg)
            result.update(arg_vars)

    return result
