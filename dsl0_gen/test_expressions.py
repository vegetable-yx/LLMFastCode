import unittest
from signatures import D0Atom, D0Vec, D0Func
from expressions import D0Expr, D0Var, D0Apply


class TestD0Expr(unittest.TestCase):
    def test_base_expr(self):
        """Test the base D0Expr class"""
        expr = D0Expr()
        self.assertIsNone(expr.sig)


class TestD0Var(unittest.TestCase):
    def test_var_creation(self):
        """Test creating D0Var instances with valid types"""
        # Create variables with atomic types
        int_type = D0Atom("int")
        float_type = D0Atom("float")
        double_type = D0Atom("double")

        var_int = D0Var("x", int_type)
        var_float = D0Var("y", float_type)
        var_double = D0Var("z", double_type)

        self.assertEqual(var_int.sig, int_type)
        self.assertEqual(var_int.name, "x")
        self.assertEqual(repr(var_int), "Var_x")

        self.assertEqual(var_float.sig, float_type)
        self.assertEqual(var_float.name, "y")
        self.assertEqual(repr(var_float), "Var_y")

        self.assertEqual(var_double.sig, double_type)
        self.assertEqual(var_double.name, "z")
        self.assertEqual(repr(var_double), "Var_z")

        # Create variables with vector types
        vec_int = D0Vec(int_type, 3)
        var_vec = D0Var("v", vec_int)

        self.assertEqual(var_vec.sig, vec_int)
        self.assertEqual(var_vec.name, "v")
        self.assertEqual(repr(var_vec), "Var_v")

        # Create variables with function types
        func_type = D0Func([int_type], float_type)
        var_func = D0Var("f", func_type)

        self.assertEqual(var_func.sig, func_type)
        self.assertEqual(var_func.name, "f")
        self.assertEqual(repr(var_func), "Var_f")

    def test_var_invalid_type(self):
        """Test creating D0Var with invalid types raises assertion error"""
        # Create an object that's not a valid D0Type
        invalid_type = "not_a_type"

        with self.assertRaises(AssertionError):
            D0Var("invalid", invalid_type)


class TestD0Apply(unittest.TestCase):
    def setUp(self):
        """Set up common types and variables for testing"""
        self.int_type = D0Atom("int")
        self.float_type = D0Atom("float")
        self.double_type = D0Atom("double")

        # Create vector types
        self.vec_int_3 = D0Vec(self.int_type, 3)
        self.vec_float_2 = D0Vec(self.float_type, 2)

        # Create function types
        self.func_int_to_float = D0Func([self.int_type], self.float_type)
        self.func_float_to_int = D0Func([self.float_type], self.int_type)
        self.func_int_int_to_float = D0Func(
            [self.int_type, self.int_type], self.float_type
        )
        self.func_empty_to_int = D0Func([], self.int_type)
        self.func_vec_to_int = D0Func([self.vec_int_3], self.int_type)

        # Create variables with the function types
        self.var_func_int_to_float = D0Var("f", self.func_int_to_float)
        self.var_func_float_to_int = D0Var("g", self.func_float_to_int)
        self.var_func_int_int_to_float = D0Var("h", self.func_int_int_to_float)
        self.var_func_empty_to_int = D0Var("nilary", self.func_empty_to_int)
        self.var_func_vec_to_int = D0Var("vecfunc", self.func_vec_to_int)

        # Create variables with atomic types
        self.var_int = D0Var("x", self.int_type)
        self.var_float = D0Var("y", self.float_type)
        self.var_double = D0Var("z", self.double_type)

        # Create variables with vector types
        self.var_vec_int = D0Var("v", self.vec_int_3)

    def test_apply_simple(self):
        """Test applying a function with a single argument"""
        # Apply: f(x) where f: int -> float and x: int
        apply_f_x = D0Apply(self.var_func_int_to_float, [self.var_int])

        self.assertEqual(apply_f_x.sig, self.float_type)
        self.assertEqual(apply_f_x.func, self.var_func_int_to_float)
        self.assertEqual(apply_f_x.xs, [self.var_int])
        self.assertIn("Apply(Var_f,", repr(apply_f_x))

        # Apply: g(y) where g: float -> int and y: float
        apply_g_y = D0Apply(self.var_func_float_to_int, [self.var_float])

        self.assertEqual(apply_g_y.sig, self.int_type)
        self.assertEqual(apply_g_y.func, self.var_func_float_to_int)
        self.assertEqual(apply_g_y.xs, [self.var_float])

    def test_apply_multiple_args(self):
        """Test applying a function with multiple arguments"""
        # Apply: h(x, x) where h: (int, int) -> float and x: int
        apply_h_x_x = D0Apply(
            self.var_func_int_int_to_float, [self.var_int, self.var_int]
        )

        self.assertEqual(apply_h_x_x.sig, self.float_type)
        self.assertEqual(apply_h_x_x.func, self.var_func_int_int_to_float)
        self.assertEqual(apply_h_x_x.xs, [self.var_int, self.var_int])

    def test_apply_empty_args(self):
        """Test applying a function with no arguments"""
        # Apply: nilary() where nilary: () -> int
        apply_nilary = D0Apply(self.var_func_empty_to_int, [])

        self.assertEqual(apply_nilary.sig, self.int_type)
        self.assertEqual(apply_nilary.func, self.var_func_empty_to_int)
        self.assertEqual(apply_nilary.xs, [])

    def test_apply_vector_args(self):
        """Test applying a function with vector arguments"""
        # Apply: vecfunc(v) where vecfunc: int[3] -> int and v: int[3]
        apply_vecfunc = D0Apply(self.var_func_vec_to_int, [self.var_vec_int])

        self.assertEqual(apply_vecfunc.sig, self.int_type)
        self.assertEqual(apply_vecfunc.func, self.var_func_vec_to_int)
        self.assertEqual(apply_vecfunc.xs, [self.var_vec_int])

    def test_apply_composition(self):
        """Test nested function applications (function composition)"""
        # First apply: f(x) where f: int -> float and x: int
        apply_f_x = D0Apply(self.var_func_int_to_float, [self.var_int])

        # Then apply: g(f(x)) where g: float -> int and f(x): float
        apply_g_f_x = D0Apply(self.var_func_float_to_int, [apply_f_x])

        self.assertEqual(apply_g_f_x.sig, self.int_type)
        self.assertEqual(apply_g_f_x.func, self.var_func_float_to_int)
        self.assertEqual(apply_g_f_x.xs, [apply_f_x])

    def test_apply_invalid_type(self):
        """Test applying with invalid function or argument types"""
        # Non-function as function
        with self.assertRaises(AssertionError):
            D0Apply(self.var_int, [self.var_float])

        # Wrong argument type
        with self.assertRaises(AssertionError):
            D0Apply(self.var_func_int_to_float, [self.var_float])

        # Wrong number of arguments - too few
        with self.assertRaises(AssertionError):
            D0Apply(self.var_func_int_int_to_float, [self.var_int])

        # Wrong number of arguments - too many
        with self.assertRaises(AssertionError):
            D0Apply(self.var_func_int_to_float, [self.var_int, self.var_int])

    def test_apply_complex_composition(self):
        """Test more complex nested function applications"""
        # Apply: f(x) where f: int -> float and x: int
        apply_f_x = D0Apply(self.var_func_int_to_float, [self.var_int])

        # Apply: g(f(x)) where g: float -> int and f(x): float
        apply_g_f_x = D0Apply(self.var_func_float_to_int, [apply_f_x])

        # Apply: f(g(f(x))) where f: int -> float and g(f(x)): int
        apply_f_g_f_x = D0Apply(self.var_func_int_to_float, [apply_g_f_x])

        self.assertEqual(apply_f_g_f_x.sig, self.float_type)

        # Now try a multi-argument function with nested applications
        # Apply: h(x, g(f(x))) where h: (int, int) -> float, x: int, g(f(x)): int
        apply_h_x_g_f_x = D0Apply(
            self.var_func_int_int_to_float, [self.var_int, apply_g_f_x]
        )

        self.assertEqual(apply_h_x_g_f_x.sig, self.float_type)
        self.assertEqual(apply_h_x_g_f_x.func, self.var_func_int_int_to_float)
        self.assertEqual(apply_h_x_g_f_x.xs, [self.var_int, apply_g_f_x])


if __name__ == "__main__":
    unittest.main()
