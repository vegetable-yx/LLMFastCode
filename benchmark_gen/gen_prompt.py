import os
import re

def gen_prompt(dst_folder):
    extracted_content = ""
    pattern = re.compile(r'/\*\s*LLM prompt code start\s*\*/(.*?)/\*\s*LLM prompt code end\s*\*/', re.DOTALL)

    prompt = '''
    I have the following C++ code structure that includes a function called "slow_performance".
    Please rewrite the given "slow_performance" function into the "max_performance" function, fully preserving the functionality, inputs, outputs, memory layouts, and side-effects exactly as in the original implementation.
    The only acceptable difference must be performance-related optimizations that significantly improve computational efficiency (such as loop unrolling, cache-friendly memory accesses, SIMD vectorization, reducing unnecessary instructions, etc.) and minimize the total execution cycles.
    Your answer MUST strictly **ONLY** contain the complete and optimized implementation of the "max_performance" function at **THE END OF YOUR OUTPUT**. No other text, comments, or explanations should be included!
    Ensure the provided function implementation is immediately ready for compilation and use as-is, preserving identical behavior relative to "slow_performance".
    '''

    for root, dirs, files in os.walk(dst_folder):
        for file in files:
            if file == "implementation.cpp":
                with open(os.path.join(root, file), "r", encoding="utf-8") as f:
                    content = f.read()
                    match = pattern.search(content)
                    if match:
                        extracted_content = match.group(1).strip()
                        # print(extracted_content)

    return f'''
    ```cpp
    {extracted_content}
    ```
    {prompt}
    '''

if __name__ == "__main__":
    dst_folder = "./output/run_20250422_205743_249252"
    print(gen_prompt(dst_folder))