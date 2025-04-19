# Types used in DSL0


class D0Type:
    pass


class D0Atom(D0Type):
    def __init__(self, sig: str):
        assert sig in ["int", "float", "double"]
        self.sig_name = sig

    def __repr__(self):
        return self.sig_name


class D0Vec(D0Type):
    def __init__(self, t_element: D0Type, size: int):
        assert size >= 0
        self.t_element = t_element
        self.size = size

    def __repr__(self):
        return f"({self.t_element.__repr__()})[{self.size}]"


class D0Func(D0Type):
    def __init__(self, t_from: list[D0Type], t_to: D0Type):
        assert type(t_from) == list
        self.t_from = t_from
        self.t_to = t_to

    def __repr__(self):
        return f"({self.t_from.__repr__()} -> {self.t_to.__repr__()})"


def typecheck_D0(t: D0Type) -> bool:
    if isinstance(t, D0Atom):
        return True
    elif isinstance(t, D0Vec):
        return typecheck_D0(t.t_element)
    elif isinstance(t, D0Func):
        flag = True
        for ti in t.t_from:
            flag = flag and typecheck_D0(ti)
        return flag and typecheck_D0(t.t_to)
    return False


def check_type_eq(tx: D0Type, ty: D0Type):
    if isinstance(tx, D0Atom):
        if isinstance(ty, D0Atom):
            return tx.sig_name == ty.sig_name
    elif isinstance(tx, D0Vec):
        if isinstance(ty, D0Vec):
            return check_type_eq(tx.t_element, ty.t_element) and (tx.size == ty.size)
    elif isinstance(tx, D0Func):
        if isinstance(ty, D0Func):
            if len(tx.t_from) == len(ty.t_from):
                flag = True
                for i in range(len(tx.t_from)):
                    flag = flag and check_type_eq(tx.t_from[i], ty.t_from[i])
                return flag and check_type_eq(tx.t_to, ty.t_to)
    return False


def check_apply(t_func: D0Func, t_xs: list[D0Type]):
    if isinstance(t_func, D0Func):
        if len(t_func.t_from) == len(t_xs):
            flag = True
            for i in range(len(t_xs)):
                flag = flag and check_type_eq(t_func.t_from[i], t_xs[i])
            return flag
    return False
