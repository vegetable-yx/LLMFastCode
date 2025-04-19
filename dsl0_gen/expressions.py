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
