import os
import re

def gen_prompt(dst_folder):
    extracted_content = ""
    pattern = re.compile(r'/\*\s*LLM prompt code start\s*\*/(.*?)/\*\s*LLM prompt code end\s*\*/', re.DOTALL)

    prompt = '''
    Rewrite `slow_performance` into `max_performance`, keeping inputs, outputs, and behavior identical.  
    Only apply performance optimizations (algebraic simplification, cache-friendly memory access, SIMD/AVX-512, loop unrolling, etc.).  
    **Assume the code executes on a single core, DO NOT introduce multithreading or parallelism.**

    **Target system**
    - Intel(R) Xeon(R) Platinum 8336C CPU @ 2.30GHz
    - Caches: 48 KB L1 D + 32 KB L1 I per core, 1.25 MB L2 per core, 54 MB shared L3  
    - GCC 12 on Debian Bookworm; compile with `-O3 -march=native -mavx2 -std=c++11`

    **Hints**
    - Write SIMDe code with <immintrin.h> whenever possible.
    - Do not use libc functions as their performance is not good.

    Return **only** the full, ready-to-compile `max_performance` function—no other text, comments, or explanations.
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

    result = f'''
    ```cpp
    {extracted_content}
    ```
    {prompt}
    '''

    for root, dirs, files in os.walk(dst_folder):
        for file in files:
            if file == "prompt.txt":
                with open(os.path.join(root, file), "w", encoding="utf-8") as f:
                    f.write(result)

    return result

if __name__ == "__main__":
    dst_folder = "./output/run_20250424_212953_804478"
    print(gen_prompt(dst_folder))