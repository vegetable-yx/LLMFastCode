import unittest
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
)


class TestD0Primitive(unittest.TestCase):
    def test_primitive_creation(self):
        """Test creating D0Primitive instances"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")
        double_type = D0Atom("double")

        prim_int = D0Primitive("add", int_type)
        prim_float = D0Primitive("multiply", float_type)
        prim_double = D0Primitive("divide", double_type)

        self.assertEqual(prim_int.sig, int_type)
        self.assertEqual(prim_int.name, "p_add")

        self.assertEqual(prim_float.sig, float_type)
        self.assertEqual(prim_float.name, "p_multiply")

        self.assertEqual(prim_double.sig, double_type)
        self.assertEqual(prim_double.name, "p_divide")


class TestD0ConcreteExpr(unittest.TestCase):
    def test_base_concrete_expr(self):
        """Test the base D0ConcreteExpr class"""
        expr = D0ConcreteExpr()
        self.assertIsNone(expr.sig)


class TestD0ConcreteExprPrimitive(unittest.TestCase):
    def test_concrete_expr_primitive(self):
        """Test creating D0ConcreteExprPrimitive instances"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")

        # Create primitives
        prim_int = D0Primitive("add", int_type)
        prim_float = D0Primitive("multiply", float_type)

        # Create concrete expressions from primitives
        concrete_int = D0ConcreteExprPrimitive(prim_int)
        concrete_float = D0ConcreteExprPrimitive(prim_float)

        # Check signature propagation
        self.assertEqual(concrete_int.sig, int_type)
        self.assertEqual(concrete_float.sig, float_type)

        # Check primitive reference
        self.assertEqual(concrete_int.x, prim_int)
        self.assertEqual(concrete_float.x, prim_float)

        # Test representation
        self.assertEqual(repr(concrete_int), repr(prim_int))
        self.assertEqual(repr(concrete_float), repr(prim_float))

    def test_invalid_primitive(self):
        """Test creating D0ConcreteExprPrimitive with invalid primitive"""
        # Create a "primitive" with an invalid type
        invalid_prim = D0Primitive("invalid", "not_a_type")

        # Should raise an assertion error
        with self.assertRaises(AssertionError):
            D0ConcreteExprPrimitive(invalid_prim)


class TestD0ConcreteExprApply(unittest.TestCase):
    def setUp(self):
        """Set up common types and primitives for testing"""
        self.int_type = D0Atom("int")
        self.float_type = D0Atom("float")

        # Create function types
        self.func_int_to_float = D0Func([self.int_type], self.float_type)
        self.func_float_to_int = D0Func([self.float_type], self.int_type)
        self.func_int_int_to_float = D0Func(
            [self.int_type, self.int_type], self.float_type
        )

        # Create primitives
        self.prim_int = D0Primitive("int_val", self.int_type)
        self.prim_float = D0Primitive("float_val", self.float_type)

        # Create function primitives
        self.prim_func_int_to_float = D0MakeFunc("int_to_float", self.func_int_to_float)
        self.prim_func_float_to_int = D0MakeFunc("float_to_int", self.func_float_to_int)
        self.prim_func_int_int_to_float = D0MakeFunc(
            "add_ints", self.func_int_int_to_float
        )

        # Create concrete expressions
        self.concrete_int = D0ConcreteExprPrimitive(self.prim_int)
        self.concrete_float = D0ConcreteExprPrimitive(self.prim_float)
        self.concrete_func_int_to_float = D0ConcreteExprPrimitive(
            self.prim_func_int_to_float
        )
        self.concrete_func_float_to_int = D0ConcreteExprPrimitive(
            self.prim_func_float_to_int
        )
        self.concrete_func_int_int_to_float = D0ConcreteExprPrimitive(
            self.prim_func_int_int_to_float
        )

    def test_concrete_expr_apply_simple(self):
        """Test creating simple D0ConcreteExprApply instances"""
        # Apply int_to_float(int_val)
        apply_f_x = D0ConcreteExprApply(
            self.concrete_func_int_to_float, [self.concrete_int]
        )

        self.assertEqual(apply_f_x.sig, self.float_type)
        self.assertEqual(apply_f_x.func, self.concrete_func_int_to_float)
        self.assertEqual(apply_f_x.xs, [self.concrete_int])
        self.assertIn("CApp(", repr(apply_f_x))

        # Apply float_to_int(float_val)
        apply_g_y = D0ConcreteExprApply(
            self.concrete_func_float_to_int, [self.concrete_float]
        )

        self.assertEqual(apply_g_y.sig, self.int_type)
        self.assertEqual(apply_g_y.func, self.concrete_func_float_to_int)
        self.assertEqual(apply_g_y.xs, [self.concrete_float])

    def test_concrete_expr_apply_multiple_args(self):
        """Test applying function with multiple arguments"""
        # Apply add_ints(int_val, int_val)
        apply_h_x_x = D0ConcreteExprApply(
            self.concrete_func_int_int_to_float, [self.concrete_int, self.concrete_int]
        )

        self.assertEqual(apply_h_x_x.sig, self.float_type)
        self.assertEqual(apply_h_x_x.func, self.concrete_func_int_int_to_float)
        self.assertEqual(apply_h_x_x.xs, [self.concrete_int, self.concrete_int])

    def test_concrete_expr_apply_composition(self):
        """Test nested function applications"""
        # First apply: int_to_float(int_val)
        apply_f_x = D0ConcreteExprApply(
            self.concrete_func_int_to_float, [self.concrete_int]
        )

        # Then apply: float_to_int(int_to_float(int_val))
        apply_g_f_x = D0ConcreteExprApply(self.concrete_func_float_to_int, [apply_f_x])

        self.assertEqual(apply_g_f_x.sig, self.int_type)
        self.assertEqual(apply_g_f_x.func, self.concrete_func_float_to_int)
        self.assertEqual(apply_g_f_x.xs, [apply_f_x])

    def test_concrete_expr_apply_invalid(self):
        """Test invalid function applications"""
        # Wrong argument type
        with self.assertRaises(AssertionError):
            D0ConcreteExprApply(self.concrete_func_int_to_float, [self.concrete_float])

        # Wrong number of arguments - too few
        with self.assertRaises(AssertionError):
            D0ConcreteExprApply(
                self.concrete_func_int_int_to_float, [self.concrete_int]
            )

        # Wrong number of arguments - too many
        with self.assertRaises(AssertionError):
            D0ConcreteExprApply(
                self.concrete_func_int_to_float, [self.concrete_int, self.concrete_int]
            )

        # Non-function as function
        with self.assertRaises(AssertionError):
            D0ConcreteExprApply(self.concrete_int, [self.concrete_float])


class TestMakeConcreteExpr(unittest.TestCase):
    def setUp(self):
        """Set up common types, variables and primitives for testing"""
        self.int_type = D0Atom("int")
        self.float_type = D0Atom("float")

        # Create function types
        self.func_int_to_float = D0Func([self.int_type], self.float_type)
        self.func_float_to_int = D0Func([self.float_type], self.int_type)

        # Create variables
        self.var_x = D0Var("x", self.int_type)
        self.var_y = D0Var("y", self.float_type)
        self.var_f = D0Var("f", self.func_int_to_float)
        self.var_g = D0Var("g", self.func_float_to_int)

        # Create primitives
        self.prim_x = D0Primitive("x_val", self.int_type)
        self.prim_y = D0Primitive("y_val", self.float_type)
        self.prim_f = D0MakeFunc("int_to_float", self.func_int_to_float)
        self.prim_g = D0MakeFunc("float_to_int", self.func_float_to_int)

        # Create name mapping
        self.name_mapping = {
            "x": self.prim_x,
            "y": self.prim_y,
            "f": self.prim_f,
            "g": self.prim_g,
        }

    def test_make_concrete_var(self):
        """Test make_concrete_expr with variable expressions"""
        # Convert var_x to concrete expression
        concrete_x = make_concrete_expr(self.var_x, self.name_mapping)

        self.assertIsInstance(concrete_x, D0ConcreteExprPrimitive)
        self.assertEqual(concrete_x.sig, self.int_type)
        self.assertEqual(concrete_x.x, self.prim_x)

        # Convert var_f to concrete expression
        concrete_f = make_concrete_expr(self.var_f, self.name_mapping)

        self.assertIsInstance(concrete_f, D0ConcreteExprPrimitive)
        self.assertEqual(concrete_f.sig, self.func_int_to_float)
        self.assertEqual(concrete_f.x, self.prim_f)

    def test_make_concrete_apply(self):
        """Test make_concrete_expr with apply expressions"""
        # Create apply expression: f(x)
        apply_f_x = D0Apply(self.var_f, [self.var_x])

        # Convert to concrete expression
        concrete_apply = make_concrete_expr(apply_f_x, self.name_mapping)

        self.assertIsInstance(concrete_apply, D0ConcreteExprApply)
        self.assertEqual(concrete_apply.sig, self.float_type)
        self.assertIsInstance(concrete_apply.func, D0ConcreteExprPrimitive)
        self.assertEqual(concrete_apply.func.x, self.prim_f)
        self.assertEqual(len(concrete_apply.xs), 1)
        self.assertIsInstance(concrete_apply.xs[0], D0ConcreteExprPrimitive)
        self.assertEqual(concrete_apply.xs[0].x, self.prim_x)

    def test_make_concrete_nested_apply(self):
        """Test make_concrete_expr with nested apply expressions"""
        # Create nested apply expression: g(f(x))
        apply_f_x = D0Apply(self.var_f, [self.var_x])
        apply_g_f_x = D0Apply(self.var_g, [apply_f_x])

        # Convert to concrete expression
        concrete_apply = make_concrete_expr(apply_g_f_x, self.name_mapping)

        self.assertIsInstance(concrete_apply, D0ConcreteExprApply)
        self.assertEqual(concrete_apply.sig, self.int_type)
        self.assertIsInstance(concrete_apply.func, D0ConcreteExprPrimitive)
        self.assertEqual(concrete_apply.func.x, self.prim_g)
        self.assertEqual(len(concrete_apply.xs), 1)
        self.assertIsInstance(concrete_apply.xs[0], D0ConcreteExprApply)

    def test_make_concrete_missing_var(self):
        """Test make_concrete_expr with variable not in mapping"""
        # Create a variable not in name_mapping
        var_z = D0Var("z", self.int_type)

        # Should raise ValueError
        with self.assertRaises(ValueError):
            make_concrete_expr(var_z, self.name_mapping)

    def test_make_concrete_type_mismatch(self):
        """Test make_concrete_expr with type mismatch"""
        # Create variable with incorrect type
        var_x_float = D0Var("x", self.float_type)  # x is mapped to int in name_mapping

        # Should raise ValueError
        with self.assertRaises(ValueError):
            make_concrete_expr(var_x_float, self.name_mapping)

    def test_make_concrete_unsupported_type(self):
        """Test make_concrete_expr with unsupported expression type"""
        # Create a non-D0Expr object
        not_an_expr = "not_an_expr"

        # Should raise TypeError
        with self.assertRaises(TypeError):
            make_concrete_expr(not_an_expr, self.name_mapping)


class TestD0MakeInput(unittest.TestCase):
    def test_make_input(self):
        """Test creating D0MakeInput instances"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")

        # Create input vectors
        input_int_3 = D0MakeInput("ints", int_type, 3)
        input_float_5 = D0MakeInput("floats", float_type, 5)

        # Check that signature is a vector
        self.assertIsInstance(input_int_3.sig, D0Vec)
        self.assertEqual(input_int_3.sig.t_element, int_type)
        self.assertEqual(input_int_3.sig.size, 3)
        self.assertEqual(input_int_3.name, "i_ints")

        self.assertIsInstance(input_float_5.sig, D0Vec)
        self.assertEqual(input_float_5.sig.t_element, float_type)
        self.assertEqual(input_float_5.sig.size, 5)
        self.assertEqual(input_float_5.name, "i_floats")


class TestD0MakeConst(unittest.TestCase):
    def test_make_const(self):
        """Test creating D0MakeConst instances"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")

        # Create constant vectors
        const_int_3 = D0MakeConst("ints", int_type, 3, [1, 2, 3])
        const_float_2 = D0MakeConst("floats", float_type, 2, [1.5, 2.5])

        # Check that signature is a vector
        self.assertIsInstance(const_int_3.sig, D0Vec)
        self.assertEqual(const_int_3.sig.t_element, int_type)
        self.assertEqual(const_int_3.sig.size, 3)
        self.assertEqual(const_int_3.name, "c_ints")
        self.assertEqual(const_int_3.values, [1, 2, 3])

        self.assertIsInstance(const_float_2.sig, D0Vec)
        self.assertEqual(const_float_2.sig.t_element, float_type)
        self.assertEqual(const_float_2.sig.size, 2)
        self.assertEqual(const_float_2.name, "c_floats")
        self.assertEqual(const_float_2.values, [1.5, 2.5])

        # Test representation
        self.assertEqual(repr(const_int_3), "c_ints")
        self.assertEqual(repr(const_float_2), "c_floats")

    def test_make_const_invalid(self):
        """Test creating D0MakeConst with invalid values"""
        int_type = D0Atom("int")

        # Values length doesn't match size
        with self.assertRaises(AssertionError):
            D0MakeConst("ints", int_type, 3, [1, 2])  # Only 2 values for size 3

        with self.assertRaises(AssertionError):
            D0MakeConst("ints", int_type, 2, [1, 2, 3])  # 3 values for size 2


class TestD0MakeFunc(unittest.TestCase):
    def test_make_func(self):
        """Test creating D0MakeFunc instances"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")

        # Create function types
        func_int_to_float = D0Func([int_type], float_type)
        func_float_to_int = D0Func([float_type], int_type)

        # Create function primitives
        func_prim1 = D0MakeFunc("int_to_float", func_int_to_float)
        func_prim2 = D0MakeFunc("float_to_int", func_float_to_int)

        # Check properties
        self.assertEqual(func_prim1.sig, func_int_to_float)
        self.assertEqual(func_prim1.name, "f_int_to_float")

        self.assertEqual(func_prim2.sig, func_float_to_int)
        self.assertEqual(func_prim2.name, "f_float_to_int")

        # Test representation
        self.assertEqual(repr(func_prim1), "f_int_to_float")
        self.assertEqual(repr(func_prim2), "f_float_to_int")


if __name__ == "__main__":
    unittest.main()
