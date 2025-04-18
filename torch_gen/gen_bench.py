# First version of program generator, not working correctly.
# May lead to OOM.

import torch
import random
import os
from itertools import product
import numpy as np
from typing import List, Tuple, Dict, Any, Callable, Set, Union


class TorchProgramGenerator:
    def __init__(self):
        # Define the set of PyTorch operations we'll use
        self.ops = {
            # Creation ops
            "zeros_like": {
                "func": lambda x: torch.zeros_like(x),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "ones_like": {
                "func": lambda x: torch.ones_like(x),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "randn_like": {
                "func": lambda x: torch.randn_like(x),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "clone": {
                "func": lambda x: x.clone(),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            # Math ops
            "add": {
                "func": lambda x, y: x + y,
                "num_inputs": 2,
                "shape_requirements": [("broadcastable", 0, 1)],
            },
            "sub": {
                "func": lambda x, y: x - y,
                "num_inputs": 2,
                "shape_requirements": [("broadcastable", 0, 1)],
            },
            "mul": {
                "func": lambda x, y: x * y,
                "num_inputs": 2,
                "shape_requirements": [("broadcastable", 0, 1)],
            },
            "div": {
                "func": lambda x, y: x / (y + 1e-8),  # Avoid division by zero
                "num_inputs": 2,
                "shape_requirements": [("broadcastable", 0, 1)],
            },
            "matmul": {
                "func": lambda x, y: torch.matmul(x, y),
                "num_inputs": 2,
                "shape_requirements": [("matmul_compatible", 0, 1)],
            },
            "kronecker_product": {
                "func": lambda x, y: torch.kron(x, y),
                "num_inputs": 2,
                "shape_requirements": [],
            },
            # Unary ops
            "sin": {
                "func": lambda x: torch.sin(x),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "cos": {
                "func": lambda x: torch.cos(x),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "exp": {
                "func": lambda x: torch.exp(x),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "log": {
                "func": lambda x: torch.log(torch.abs(x) + 1e-8),  # Avoid log(0)
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "abs": {
                "func": lambda x: torch.abs(x),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "sqrt": {
                "func": lambda x: torch.sqrt(
                    torch.abs(x) + 1e-8
                ),  # Avoid sqrt of negative
                "num_inputs": 1,
                "shape_requirements": [],
            },
            # Reduction ops
            "sum": {
                "func": lambda x: torch.sum(x, dim=-1),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "mean": {
                "func": lambda x: torch.mean(x, dim=-1),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "max": {
                "func": lambda x: torch.max(x, dim=-1)[0],
                "num_inputs": 1,
                "shape_requirements": [("non_empty", 0)],
            },
            # Shape ops
            "transpose": {
                "func": lambda x: x.transpose(-2, -1) if x.dim() >= 2 else x,
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "reshape": {
                "func": lambda x: self._safe_reshape(x),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "permute": {
                "func": lambda x: self._safe_permute(x),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "squeeze": {
                "func": lambda x: (
                    torch.squeeze(x, dim=-1) if x.dim() > 1 and x.shape[-1] == 1 else x
                ),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "unsqueeze": {
                "func": lambda x: torch.unsqueeze(x, dim=-1),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            # Other ops
            "normalize": {
                "func": lambda x: torch.nn.functional.normalize(x, p=2, dim=-1),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "softmax": {
                "func": lambda x: torch.nn.functional.softmax(x, dim=-1),
                "num_inputs": 1,
                "shape_requirements": [],
            },
            "topk": {
                "func": lambda x: torch.topk(x, k=min(2, x.shape[-1]), dim=-1)[0],
                "num_inputs": 1,
                "shape_requirements": [("non_empty", 0)],
            },
            "cat": {
                "func": lambda x, y: torch.cat([x, y], dim=-1),
                "num_inputs": 2,
                "shape_requirements": [("cat_compatible", 0, 1)],
            },
            "stack": {
                "func": lambda x, y: torch.stack([x, y], dim=0),
                "num_inputs": 2,
                "shape_requirements": [("same_shape", 0, 1)],
            },
        }

        # Operators by number of inputs
        self.ops_by_inputs = {1: [], 2: []}
        for op_name, op_info in self.ops.items():
            self.ops_by_inputs[op_info["num_inputs"]].append(op_name)

    def _safe_reshape(self, x):
        """Safe reshape that won't cause errors"""
        if x.numel() == 0:
            return x

        if x.dim() == 0:
            return x.reshape(1)

        # Random reshape that preserves total elements
        total_elements = x.numel()
        if total_elements <= 1:
            return x

        # Try to find some reasonable factors
        factors = []
        for i in range(1, min(4, total_elements + 1)):
            if total_elements % i == 0:
                factors.append(i)

        # If we can't factor nicely, just return original tensor
        if len(factors) <= 1:
            return x

        # Choose a random factor for the first dimension
        first_dim = random.choice(factors)
        second_dim = total_elements // first_dim

        if random.random() < 0.5:
            return x.reshape(first_dim, second_dim)
        else:
            return x.reshape(first_dim, -1)

    def _safe_permute(self, x):
        """Safe permute that won't cause errors"""
        if x.dim() <= 1:
            return x

        # For tensors with more dimensions, randomly permute two dimensions
        dims = list(range(x.dim()))
        i, j = random.sample(dims, 2)

        # Create permutation order
        perm = list(range(x.dim()))
        perm[i], perm[j] = perm[j], perm[i]

        return x.permute(*perm)

    def _check_shape_requirements(self, tensors, op_name):
        """Check if tensors satisfy the shape requirements for an operation"""
        op_info = self.ops[op_name]
        for req in op_info["shape_requirements"]:
            req_type = req[0]
            if req_type == "broadcastable":
                idx1, idx2 = req[1], req[2]
                if not self._are_broadcastable(tensors[idx1], tensors[idx2]):
                    return False
            elif req_type == "matmul_compatible":
                idx1, idx2 = req[1], req[2]
                if not self._are_matmul_compatible(tensors[idx1], tensors[idx2]):
                    return False
            elif req_type == "non_empty":
                idx = req[1]
                if tensors[idx].numel() == 0:
                    return False
            elif req_type == "cat_compatible":
                idx1, idx2 = req[1], req[2]
                if not self._are_cat_compatible(tensors[idx1], tensors[idx2]):
                    return False
            elif req_type == "same_shape":
                idx1, idx2 = req[1], req[2]
                if tensors[idx1].shape != tensors[idx2].shape:
                    return False
        return True

    def _are_broadcastable(self, t1, t2):
        """Check if two tensors are broadcastable"""
        # Empty tensors are not reliably broadcastable
        if t1.numel() == 0 or t2.numel() == 0:
            return False

        s1 = list(t1.shape)
        s2 = list(t2.shape)

        # Pad shorter shape with ones
        if len(s1) < len(s2):
            s1 = [1] * (len(s2) - len(s1)) + s1
        elif len(s2) < len(s1):
            s2 = [1] * (len(s1) - len(s2)) + s2

        # Check if shapes are broadcastable
        for d1, d2 in zip(s1, s2):
            if d1 != d2 and d1 != 1 and d2 != 1:
                return False

        return True

    def _are_matmul_compatible(self, t1, t2):
        """Check if two tensors can be matrix multiplied"""
        # Neither tensor should be empty
        if t1.numel() == 0 or t2.numel() == 0:
            return False

        # For vectors
        if t1.dim() == 1 and t2.dim() == 1:
            return t1.size(0) == t2.size(0)

        # If t1 is a vector (1D), it is treated as a 1×n matrix
        if t1.dim() == 1:
            return t1.size(0) == t2.size(0)

        # If t2 is a vector (1D), it is treated as a n×1 matrix
        if t2.dim() == 1:
            return t1.size(-1) == t2.size(0)

        # Both are 2D+ tensors
        return t1.size(-1) == t2.size(-2)

    def _are_cat_compatible(self, t1, t2):
        """Check if two tensors can be concatenated along the last dimension"""
        # Both tensors must have at least 1 dimension
        if t1.dim() == 0 or t2.dim() == 0:
            return False

        # For concatenation, all dimensions except the concatenation dimension must match
        if t1.dim() != t2.dim():
            return False

        # Check all dimensions except the last one
        for i in range(t1.dim() - 1):
            if t1.size(i) != t2.size(i):
                return False

        return True

    def generate_tensor(self, n: int) -> torch.Tensor:
        """Generate a random tensor with maximum dimension n"""
        # Decide on the number of dimensions (1 to 3)
        ndim = random.randint(1, 3)

        # Generate a shape, with each dimension having a reasonable size
        shape = []
        for _ in range(ndim):
            dim_size = random.randint(1, n)
            shape.append(dim_size)

        # Generate tensor
        tensor_type = random.choice(
            [
                lambda s: torch.randn(s),
                lambda s: torch.rand(s),
                lambda s: torch.randint(0, 10, s, dtype=torch.float32),
            ]
        )

        return tensor_type(shape)

    def _generate_program_step(
        self,
        inputs: List[int],
        available_tensors: List[torch.Tensor],
        depth: int,
        max_depth: int,
        prefix: str = "",
        generated_lines: List[str] = None,
        applied_ops: List[str] = None,
    ) -> List[List[str]]:
        """
        Recursively generate all valid programs of given depth

        Args:
            inputs: Indices of available input tensors
            available_tensors: List of tensors available at this step
            depth: Current depth of generation
            max_depth: Maximum allowed depth
            prefix: Code prefix so far
            generated_lines: Lines of code generated so far
            applied_ops: Operations applied so far

        Returns:
            List of all valid programs
        """
        if generated_lines is None:
            generated_lines = []

        if applied_ops is None:
            applied_ops = []

        # Base case: if we've reached the desired depth, return the current program
        if depth == max_depth:
            # Return the final tensor as the result
            result_lines = generated_lines + [f"    return result_{depth-1}"]
            return [(applied_ops, result_lines)]

        all_programs = []

        # Try each op with each combination of available tensors
        for op_name in self.ops:
            op_info = self.ops[op_name]
            num_inputs_needed = op_info["num_inputs"]

            # Get all combinations of available tensors to use as inputs
            tensor_combinations = []

            # For 1-input ops, we consider each available tensor
            if num_inputs_needed == 1:
                tensor_combinations = [(i,) for i in range(len(available_tensors))]
            # For 2-input ops, we consider each pair of available tensors
            elif num_inputs_needed == 2:
                tensor_combinations = list(
                    product(
                        range(len(available_tensors)), range(len(available_tensors))
                    )
                )

            for tensor_idxs in tensor_combinations:
                # Extract the tensors for this operation
                tensors = [available_tensors[i] for i in tensor_idxs]

                # Check if these tensors satisfy the shape requirements
                if not self._check_shape_requirements(tensors, op_name):
                    continue

                # If we get here, this operation is valid with these tensors
                # Generate the code for this operation
                input_names = [
                    f"result_{i}" if i >= len(inputs) else f"input_{inputs[i]}"
                    for i in tensor_idxs
                ]

                if num_inputs_needed == 1:
                    code_line = f"    result_{depth} = {input_names[0]}"

                    # Add specific code for each operation
                    if op_name == "clone":
                        code_line += ".clone()"
                    elif op_name == "sin":
                        code_line += ".sin()"
                    elif op_name == "cos":
                        code_line += ".cos()"
                    elif op_name == "exp":
                        code_line += ".exp()"
                    elif op_name == "log":
                        code_line += ".abs().add(1e-8).log()"
                    elif op_name == "abs":
                        code_line += ".abs()"
                    elif op_name == "sqrt":
                        code_line += ".abs().add(1e-8).sqrt()"
                    elif op_name == "sum":
                        code_line += ".sum(dim=-1)"
                    elif op_name == "mean":
                        code_line += ".mean(dim=-1)"
                    elif op_name == "max":
                        code_line += ".max(dim=-1)[0]"
                    elif op_name == "transpose":
                        code_line = f"    result_{depth} = {input_names[0]}.transpose(-2, -1) if {input_names[0]}.dim() >= 2 else {input_names[0]}"
                    elif op_name == "reshape":
                        # Safe reshape handled specially
                        reshaped_tensor = self._safe_reshape(tensors[0])
                        if reshaped_tensor.shape != tensors[0].shape:
                            new_shape = list(reshaped_tensor.shape)
                            code_line = f"    result_{depth} = {input_names[0]}.reshape({new_shape})"
                        else:
                            code_line = f"    result_{depth} = {input_names[0]}.clone()"
                    elif op_name == "permute":
                        # Safe permute handled specially
                        if tensors[0].dim() > 1:
                            dims = list(range(tensors[0].dim()))
                            i, j = random.sample(dims, 2)
                            perm = list(range(tensors[0].dim()))
                            perm[i], perm[j] = perm[j], perm[i]
                            code_line = f"    result_{depth} = {input_names[0]}.permute({', '.join(str(x) for x in perm)})"
                        else:
                            code_line = f"    result_{depth} = {input_names[0]}.clone()"
                    elif op_name == "squeeze":
                        code_line = f"    result_{depth} = {input_names[0]}.squeeze(-1) if {input_names[0]}.dim() > 1 and {input_names[0]}.shape[-1] == 1 else {input_names[0]}"
                    elif op_name == "unsqueeze":
                        code_line = (
                            f"    result_{depth} = {input_names[0]}.unsqueeze(-1)"
                        )
                    elif op_name == "normalize":
                        code_line = f"    result_{depth} = torch.nn.functional.normalize({input_names[0]}, p=2, dim=-1)"
                    elif op_name == "softmax":
                        code_line = f"    result_{depth} = torch.nn.functional.softmax({input_names[0]}, dim=-1)"
                    elif op_name == "topk":
                        code_line = f"    result_{depth} = torch.topk({input_names[0]}, k=min(2, {input_names[0]}.shape[-1]), dim=-1)[0]"
                    elif op_name == "zeros_like":
                        code_line = (
                            f"    result_{depth} = torch.zeros_like({input_names[0]})"
                        )
                    elif op_name == "ones_like":
                        code_line = (
                            f"    result_{depth} = torch.ones_like({input_names[0]})"
                        )
                    elif op_name == "randn_like":
                        code_line = (
                            f"    result_{depth} = torch.randn_like({input_names[0]})"
                        )

                elif num_inputs_needed == 2:
                    if op_name == "add":
                        code_line = (
                            f"    result_{depth} = {input_names[0]} + {input_names[1]}"
                        )
                    elif op_name == "sub":
                        code_line = (
                            f"    result_{depth} = {input_names[0]} - {input_names[1]}"
                        )
                    elif op_name == "mul":
                        code_line = (
                            f"    result_{depth} = {input_names[0]} * {input_names[1]}"
                        )
                    elif op_name == "div":
                        code_line = f"    result_{depth} = {input_names[0]} / ({input_names[1]} + 1e-8)  # Avoid division by zero"
                    elif op_name == "matmul":
                        code_line = f"    result_{depth} = torch.matmul({input_names[0]}, {input_names[1]})"
                    elif op_name == "kronecker_product":
                        code_line = f"    result_{depth} = torch.kron({input_names[0]}, {input_names[1]})"
                    elif op_name == "cat":
                        code_line = f"    result_{depth} = torch.cat([{input_names[0]}, {input_names[1]}], dim=-1)"
                    elif op_name == "stack":
                        code_line = f"    result_{depth} = torch.stack([{input_names[0]}, {input_names[1]}], dim=0)"

                # Create a new available_tensors list with the result of this operation
                try:
                    # Apply the operation to get the new tensor
                    new_tensor = op_info["func"](*tensors)
                    new_available_tensors = available_tensors + [new_tensor]

                    # Recursively generate the rest of the program
                    sub_programs = self._generate_program_step(
                        inputs,
                        new_available_tensors,
                        depth + 1,
                        max_depth,
                        prefix + "    " + code_line + "\n",
                        generated_lines + [code_line],
                        applied_ops + [op_name],
                    )

                    all_programs.extend(sub_programs)
                except Exception as e:
                    # Skip this operation if it throws an exception
                    pass

        return all_programs

    def generate_all_programs(self, n: int, d: int) -> List[Tuple[List[str], str]]:
        """
        Generate all valid programs with d operators and input size n

        Args:
            n: Size of the input tensors
            d: Number of operators in each program

        Returns:
            List of tuples containing (applied_ops, program_code)
        """
        assert d <= 4, "D should be at most 4 for reasonable computation"

        all_programs = []

        # Try different numbers of input tensors
        for num_inputs in range(1, 3):  # 1 or 2 inputs
            # Generate actual input tensors
            input_tensors = [self.generate_tensor(n) for _ in range(num_inputs)]

            # Generate all valid programs
            programs = self._generate_program_step(
                list(range(num_inputs)),
                input_tensors,
                0,
                d,
            )

            for applied_ops, code_lines in programs:
                # Create the function definition
                function_code = f"def torch_program({', '.join(f'input_{i}' for i in range(num_inputs))}):\n"
                function_code += "\n".join(code_lines)

                # Create the test handler
                test_handler = self._create_test_handler(num_inputs, n)

                all_programs.append((applied_ops, function_code, test_handler))

        return all_programs

    def _create_test_handler(self, num_inputs: int, n: int) -> str:
        """Create test handler code for the given number of inputs"""
        handler_code = """
def test_handler():
    # Set random seed for reproducibility
    torch.manual_seed(42)
    random.seed(42)
    
"""
        # Generate the input tensors
        for i in range(num_inputs):
            ndim = random.randint(1, 3)
            shape = [random.randint(1, n) for _ in range(ndim)]

            handler_code += f"    # Generate input tensor {i}\n"
            handler_code += f"    input_{i} = torch.randn({shape})\n"

        # Call the function with the inputs
        handler_code += f"\n    # Call the function\n"
        handler_code += f"    result = torch_program({', '.join(f'input_{i}' for i in range(num_inputs))})\n"
        handler_code += f"    print(f\"Input shapes: {{{', '.join(f'input_{i}.shape' for i in range(num_inputs))}}}\")\n"
        handler_code += f'    print(f"Result shape: {{result.shape}}")\n'
        handler_code += (
            f'    print(f"Result first few values: {{result.flatten()[:5]}}")\n'
        )

        # Call the test handler
        handler_code += """
if __name__ == "__main__":
    test_handler()
"""

        return handler_code

    def save_programs_to_files(
        self,
        programs: List[Tuple[List[str], str, str]],
        output_dir: str = "generated_programs",
    ):
        """Save generated programs to Python files"""
        # Create output directory if it doesn't exist
        os.makedirs(output_dir, exist_ok=True)

        # Save each program to a file
        for i, (ops, function_code, test_handler) in enumerate(programs):
            # Create a descriptive filename
            op_names = "_".join(ops)
            if len(op_names) > 50:  # Limit filename length
                op_names = op_names[:50]

            filename = f"{output_dir}/program_{i+1}_{op_names}.py"

            # Write the program to the file
            with open(filename, "w") as f:
                f.write("import torch\nimport random\n\n")
                f.write(function_code)
                f.write("\n\n")
                f.write(test_handler)

            print(f"Saved program {i+1} to {filename}")


# Example usage
if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="Generate random PyTorch programs")
    parser.add_argument("--n", type=int, default=5, help="Size of input tensors")
    parser.add_argument(
        "--d", type=int, default=2, help="Number of operators in each program"
    )
    parser.add_argument(
        "--output", type=str, default="generated_programs", help="Output directory"
    )

    args = parser.parse_args()

    # Check that d is less than or equal to 4
    if args.d > 4:
        print("Warning: D should be at most 4 for reasonable computation. Setting D=4.")
        args.d = 4

    print(f"Generating programs with N={args.n}, D={args.d}")

    generator = TorchProgramGenerator()
    programs = generator.generate_all_programs(args.n, args.d)

    print(f"Generated {len(programs)} valid programs")

    # Save programs to files
    generator.save_programs_to_files(programs, args.output)

    print(f"All programs saved to directory: {args.output}")
