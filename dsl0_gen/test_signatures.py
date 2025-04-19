import unittest
from signatures import D0Atom, D0Vec, D0Func, typecheck_D0, check_type_eq, check_apply


class TestD0Types(unittest.TestCase):
    def test_atom_creation(self):
        """Test creating D0Atom instances"""
        int_type = D0Atom("int")
        self.assertEqual(int_type.sig_name, "int")
        self.assertEqual(repr(int_type), "int")

        float_type = D0Atom("float")
        self.assertEqual(float_type.sig_name, "float")
        self.assertEqual(repr(float_type), "float")

        double_type = D0Atom("double")
        self.assertEqual(double_type.sig_name, "double")
        self.assertEqual(repr(double_type), "double")

    def test_atom_invalid_creation(self):
        """Test creating D0Atom with invalid signature raises assertion error"""
        with self.assertRaises(AssertionError):
            D0Atom("string")

        with self.assertRaises(AssertionError):
            D0Atom("bool")

    def test_vec_creation(self):
        """Test creating D0Vec instances"""
        int_type = D0Atom("int")
        vec_int_5 = D0Vec(int_type, 5)

        self.assertEqual(vec_int_5.t_element, int_type)
        self.assertEqual(vec_int_5.size, 5)
        self.assertEqual(repr(vec_int_5), "(int)[5]")

        # Test empty vector
        vec_int_0 = D0Vec(int_type, 0)
        self.assertEqual(vec_int_0.size, 0)
        self.assertEqual(repr(vec_int_0), "(int)[0]")

        # Test nested vector
        vec_vec_int = D0Vec(vec_int_5, 3)
        self.assertEqual(vec_vec_int.t_element, vec_int_5)
        self.assertEqual(vec_vec_int.size, 3)
        self.assertEqual(repr(vec_vec_int), "((int)[5])[3]")

    def test_vec_invalid_creation(self):
        """Test creating D0Vec with invalid size raises assertion error"""
        int_type = D0Atom("int")

        with self.assertRaises(AssertionError):
            D0Vec(int_type, -1)

    def test_func_creation(self):
        """Test creating D0Func instances"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")

        # Simple function int -> float
        func1 = D0Func([int_type], float_type)
        self.assertEqual(func1.t_from, [int_type])
        self.assertEqual(func1.t_to, float_type)
        self.assertEqual(repr(func1), "([int] -> float)")

        # Function with multiple arguments (int, float) -> int
        func2 = D0Func([int_type, float_type], int_type)
        self.assertEqual(func2.t_from, [int_type, float_type])
        self.assertEqual(func2.t_to, int_type)

        # Function with vector argument and return
        vec_int = D0Vec(int_type, 3)
        func3 = D0Func([vec_int], vec_int)
        self.assertEqual(func3.t_from, [vec_int])
        self.assertEqual(func3.t_to, vec_int)

        # Function with no arguments () -> int
        func4 = D0Func([], int_type)
        self.assertEqual(func4.t_from, [])
        self.assertEqual(func4.t_to, int_type)

        # Nested function: func taking a function as argument
        func5 = D0Func([func1], int_type)
        self.assertEqual(func5.t_from, [func1])
        self.assertEqual(func5.t_to, int_type)


class TestTypeChecking(unittest.TestCase):
    def test_typecheck_atom(self):
        """Test typecheck_D0 with atomic types"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")
        double_type = D0Atom("double")

        self.assertTrue(typecheck_D0(int_type))
        self.assertTrue(typecheck_D0(float_type))
        self.assertTrue(typecheck_D0(double_type))

    def test_typecheck_vec(self):
        """Test typecheck_D0 with vector types"""
        int_type = D0Atom("int")
        vec_int = D0Vec(int_type, 5)
        vec_vec_int = D0Vec(vec_int, 3)

        self.assertTrue(typecheck_D0(vec_int))
        self.assertTrue(typecheck_D0(vec_vec_int))

        # Vector with size 0 is valid
        vec_int_0 = D0Vec(int_type, 0)
        self.assertTrue(typecheck_D0(vec_int_0))

    def test_typecheck_func(self):
        """Test typecheck_D0 with function types"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")

        # Simple function
        func1 = D0Func([int_type], float_type)
        self.assertTrue(typecheck_D0(func1))

        # Function with multiple args
        func2 = D0Func([int_type, float_type], int_type)
        self.assertTrue(typecheck_D0(func2))

        # Function with vector args
        vec_int = D0Vec(int_type, 3)
        func3 = D0Func([vec_int], int_type)
        self.assertTrue(typecheck_D0(func3))

        # Nested function
        func4 = D0Func([func1], int_type)
        self.assertTrue(typecheck_D0(func4))

        # Empty argument function
        func5 = D0Func([], int_type)
        self.assertTrue(typecheck_D0(func5))

    def test_invalid_types(self):
        """Test typecheck_D0 with invalid types"""
        # Non D0Type objects should return False
        self.assertFalse(typecheck_D0("int"))
        self.assertFalse(typecheck_D0(42))
        self.assertFalse(typecheck_D0([]))
        self.assertFalse(typecheck_D0(None))


class TestTypeEquality(unittest.TestCase):
    def test_atom_equality(self):
        """Test check_type_eq with atomic types"""
        int_type1 = D0Atom("int")
        int_type2 = D0Atom("int")
        float_type = D0Atom("float")

        self.assertTrue(check_type_eq(int_type1, int_type2))
        self.assertFalse(check_type_eq(int_type1, float_type))

    def test_vec_equality(self):
        """Test check_type_eq with vector types"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")

        vec_int_3 = D0Vec(int_type, 3)
        vec_int_3_copy = D0Vec(int_type, 3)
        vec_int_5 = D0Vec(int_type, 5)
        vec_float_3 = D0Vec(float_type, 3)

        # Same element type, same size
        self.assertTrue(check_type_eq(vec_int_3, vec_int_3_copy))

        # Same element type, different size
        self.assertFalse(check_type_eq(vec_int_3, vec_int_5))

        # Different element type, same size
        self.assertFalse(check_type_eq(vec_int_3, vec_float_3))

        # Nested vector equality
        vec_vec_int = D0Vec(vec_int_3, 2)
        vec_vec_int_copy = D0Vec(vec_int_3_copy, 2)
        vec_vec_float = D0Vec(vec_float_3, 2)

        self.assertTrue(check_type_eq(vec_vec_int, vec_vec_int_copy))
        self.assertFalse(check_type_eq(vec_vec_int, vec_vec_float))

    def test_func_equality(self):
        """Test check_type_eq with function types"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")
        double_type = D0Atom("double")

        # Simple functions
        func1 = D0Func([int_type], float_type)
        func1_copy = D0Func([int_type], float_type)
        func2 = D0Func([int_type], double_type)  # Different return type
        func3 = D0Func([float_type], float_type)  # Different param type

        self.assertTrue(check_type_eq(func1, func1_copy))
        self.assertFalse(check_type_eq(func1, func2))
        self.assertFalse(check_type_eq(func1, func3))

        # Functions with multiple arguments
        func4 = D0Func([int_type, float_type], double_type)
        func4_copy = D0Func([int_type, float_type], double_type)
        func5 = D0Func([float_type, int_type], double_type)  # Different order of params

        self.assertTrue(check_type_eq(func4, func4_copy))
        self.assertFalse(check_type_eq(func4, func5))

        # Different number of parameters
        func6 = D0Func([int_type, float_type, double_type], int_type)
        func7 = D0Func([int_type, float_type], int_type)

        self.assertFalse(check_type_eq(func6, func7))

        # Empty argument functions
        func8 = D0Func([], int_type)
        func8_copy = D0Func([], int_type)
        func9 = D0Func([], float_type)

        self.assertTrue(check_type_eq(func8, func8_copy))
        self.assertFalse(check_type_eq(func8, func9))

    def test_mixed_type_equality(self):
        """Test check_type_eq with different types"""
        int_type = D0Atom("int")
        vec_int = D0Vec(int_type, 3)
        func = D0Func([int_type], int_type)

        # Different type classes should not be equal
        self.assertFalse(check_type_eq(int_type, vec_int))
        self.assertFalse(check_type_eq(int_type, func))
        self.assertFalse(check_type_eq(vec_int, func))


class TestFunctionApplication(unittest.TestCase):
    def test_apply_simple(self):
        """Test check_apply with simple function applications"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")

        # Function (int) -> float
        func = D0Func([int_type], float_type)

        # Valid application
        self.assertTrue(check_apply(func, [int_type]))

        # Invalid application - wrong argument type
        self.assertFalse(check_apply(func, [float_type]))

        # Invalid application - wrong number of arguments
        self.assertFalse(check_apply(func, []))
        self.assertFalse(check_apply(func, [int_type, int_type]))

    def test_apply_multiple_args(self):
        """Test check_apply with functions taking multiple arguments"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")
        double_type = D0Atom("double")

        # Function (int, float) -> double
        func = D0Func([int_type, float_type], double_type)

        # Valid application
        self.assertTrue(check_apply(func, [int_type, float_type]))

        # Invalid applications
        self.assertFalse(check_apply(func, [float_type, int_type]))  # Wrong order
        self.assertFalse(check_apply(func, [int_type, int_type]))  # Wrong second type
        self.assertFalse(check_apply(func, [int_type]))  # Too few arguments
        self.assertFalse(
            check_apply(func, [int_type, float_type, double_type])
        )  # Too many

    def test_apply_vectors(self):
        """Test check_apply with functions taking vector arguments"""
        int_type = D0Atom("int")
        vec_int_3 = D0Vec(int_type, 3)
        vec_int_5 = D0Vec(int_type, 5)

        # Function (int[3]) -> int
        func = D0Func([vec_int_3], int_type)

        # Valid application
        self.assertTrue(check_apply(func, [vec_int_3]))

        # Invalid application - wrong vector size
        self.assertFalse(check_apply(func, [vec_int_5]))

    def test_apply_empty_args(self):
        """Test check_apply with functions taking no arguments"""
        int_type = D0Atom("int")

        # Function () -> int
        func = D0Func([], int_type)

        # Valid application
        self.assertTrue(check_apply(func, []))

        # Invalid application - any arguments provided
        self.assertFalse(check_apply(func, [int_type]))

    def test_apply_to_non_function(self):
        """Test check_apply with non-function types"""
        int_type = D0Atom("int")

        # Should return False for non-function types
        self.assertFalse(check_apply(int_type, [int_type]))

    def test_apply_higher_order(self):
        """Test check_apply with higher order functions"""
        int_type = D0Atom("int")
        float_type = D0Atom("float")

        # Simple function (int) -> float
        func1 = D0Func([int_type], float_type)

        # Higher order function ((int) -> float) -> int
        func2 = D0Func([func1], int_type)

        # Valid application
        self.assertTrue(check_apply(func2, [func1]))

        # Invalid application - wrong function
        wrong_func = D0Func([float_type], int_type)
        self.assertFalse(check_apply(func2, [wrong_func]))


if __name__ == "__main__":
    unittest.main()
