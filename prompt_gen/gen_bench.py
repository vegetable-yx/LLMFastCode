import os
import shutil
from datetime import datetime

def modify_common_file(root, file, desc):
    file_path = os.path.join(root, file)
    with open(file_path, "r", encoding="utf-8") as f:
        content = f.read()

    prototype = 'typedef void (*bench_func)('
    for param in desc["params"]:
        prototype += f"{param[1]} *{param[0]}, "
    prototype = prototype[:-2] + ');\n'
    new_content = content.replace('// [bench_fun]', prototype)

    with open(file_path, "w", encoding="utf-8") as f:
        f.write(new_content)     
    
def modify_main_file(root, file, desc):
    func = desc["code"]
    file_path = os.path.join(root, file)
    with open(file_path, "r", encoding="utf-8") as f:
        content = f.read()

    kernel_base_fun = func.replace("void slow_performance", "void kernel_base")
    new_content = content.replace('// [kernel base function]', kernel_base_fun)

    prototype = 'typedef void (*bench_func)('
    for param in desc["params"]:
        prototype += f"{param[1]} *{param[0]}, "
    prototype = prototype[:-2] + ');\n'
    new_content = new_content.replace('// [prototype of the function]', prototype)

    random_input = ''
    for param in desc["params"]:
        random_input += f"  {param[1]} *{param[0]} = ({param[1]} *)malloc({param[2]} * sizeof({param[1]}));\n"
        random_input += f"  rands(({param[1]} *){param[0]}, {param[2]});\n"
    new_content = new_content.replace('  // [Get random input data]', random_input)

    invoke = 'f('
    for param in desc["params"]:
        invoke += f"{param[0]}, "
    invoke = invoke[:-2] + ');'
    new_content = new_content.replace('// [invoke function]', invoke)

    validity = ''
    for param in desc["params"]:
        validity += f"  {param[1]} *{param[0]} = ({param[1]} *)malloc({param[2]} * sizeof({param[1]}));\n"
        validity += f"  rands(({param[1]} *){param[0]}, {param[2]});\n"
    validity += f'  {desc["params"][-1][1]} *{desc["params"][-1][0]}_base = ({desc["params"][-1][1]} *)malloc({desc["params"][-1][2]} * sizeof({desc["params"][-1][1]}));\n'
    validity += f"  kernel_base("
    for i in range(len(desc["params"]) - 1):
        validity += f"{desc['params'][i][0]}, "
    validity += f"{desc['params'][-1][0]}_base);\n"
    new_content = new_content.replace('  // [Check validity of functions]', validity)

    random_result = f'rands(({desc["params"][-1][1]} *){desc["params"][-1][0]}, {desc["params"][-1][2]});\n'
    new_content = new_content.replace('// [randomize result data]', random_result)

    with open(file_path, "w", encoding="utf-8") as f:
        f.write(new_content)

def modify_implementation_file(root, file, desc):
    func = desc["code"]
    file_path = os.path.join(root, file)

    with open(file_path, "r", encoding="utf-8") as f:
        content = f.read()
    new_content = content.replace('// [Slow performance function]', func)
    max_fun = 'void max_performance('
    for param in desc["params"]:
        max_fun += f"{param[1]} *{param[0]}, "
    max_fun = max_fun[:-2] + ')\n{\n    // Fill your code here.\n}'
    new_content = new_content.replace('// [Max performance function]', max_fun)
    
    with open(file_path, "w", encoding="utf-8") as f:
        f.write(new_content)                        

def gen_bench(desc):
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S_%f")
    dst_folder = os.path.join('./output', f"run_{timestamp}")
    src_folder = '../bench_src'

    os.makedirs(dst_folder, exist_ok=False)

    for item in os.listdir(src_folder):
        s = os.path.join(src_folder, item)
        d = os.path.join(dst_folder, item)
        if os.path.isdir(s):
            shutil.copytree(s, d)
        else:
            shutil.copy2(s, d)

    for root, dirs, files in os.walk(dst_folder):
        for file in files:
            if file == "main.cpp":
                modify_main_file(root, file, desc)
            elif file == "implementation.cpp":
                modify_implementation_file(root, file, desc)
            elif file == "common.h":
                modify_common_file(root, file, desc)

if __name__ == "__main__":
    desc = {"params":[["i_x_128","float",128],["i_y_16","float",16],["result","float",64]],"code":"void slow_performance(float *i_x_128, float *i_y_16, float *result)\n{\n    float *tmp_1 = i_x_128;\n    float tmp_2[32 * 4];\n    for (int i_2 = 0; i_2 < 32; i_2++)\n    {\n        for (int j_2 = 0; j_2 < 4; j_2++)\n        {\n            tmp_2[j_2 * 32 + i_2] = tmp_1[i_2 * 4 + j_2];\n        }\n    }\n    float *tmp_3 = i_y_16;\n    float *tmp_4 = i_x_128;\n    float tmp_5[4 * 32];\n    for (int i_5 = 0; i_5 < 4; i_5++)\n    {\n        for (int k_5 = 0; k_5 < 32; k_5++)\n        {\n            tmp_5[i_5 * 32 + k_5] = 0;\n            for (int j_5 = 0; j_5 < 4; j_5++)\n            {\n                tmp_5[i_5 * 32 + k_5] += tmp_3[i_5 * 4 + j_5] * tmp_4[j_5 * 32 + k_5];\n            }\n        }\n    }\n    float tmp_6[8 * 8];\n    for (int i_6 = 0; i_6 < 8; i_6++)\n    {\n        for (int k_6 = 0; k_6 < 8; k_6++)\n        {\n            tmp_6[i_6 * 8 + k_6] = 0;\n            for (int j_6 = 0; j_6 < 16; j_6++)\n            {\n                tmp_6[i_6 * 8 + k_6] += tmp_2[i_6 * 16 + j_6] * tmp_5[j_6 * 8 + k_6];\n            }\n        }\n    }\n    for (int i_6 = 0; i_6 < 64; i_6++)\n        result[i_6] = tmp_6[i_6];\n}"}

    print(gen_bench(desc))