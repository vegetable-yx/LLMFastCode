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

    compute_loss = f'{desc["params"][-1][1]} error = nrm_sqr_diff(({desc["params"][-1][1]} *){desc["params"][-1][0]}, ({desc["params"][-1][1]} *){desc["params"][-1][0]}_base, {desc["params"][-1][2]});'
    new_content = new_content.replace('// [compute loss]', compute_loss)

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
    desc = {"params":[["i_z_128","float",128],["i_y_32","float",32],["i_y_16","float",16],["i_z_64","float",64],["result","float",16]],"code":"void slow_performance(float *i_z_128, float *i_y_32, float *i_y_16, float *i_z_64, float *result)\n{\n    float *tmp_1 = i_z_128;\n    float *tmp_2 = i_y_32;\n    float tmp_3[16 * 4];\n    for (int i_3 = 0; i_3 < 16; i_3++)\n    {\n        for (int k_3 = 0; k_3 < 4; k_3++)\n        {\n            tmp_3[i_3 * 4 + k_3] = 0;\n            for (int j_3 = 0; j_3 < 8; j_3++)\n            {\n                tmp_3[i_3 * 4 + k_3] += tmp_1[i_3 * 8 + j_3] * tmp_2[j_3 * 4 + k_3];\n            }\n        }\n    }\n    float *tmp_4 = i_y_16;\n    float *tmp_5 = i_z_64;\n    float tmp_6[2 * 8];\n    for (int i_6 = 0; i_6 < 2; i_6++)\n    {\n        for (int k_6 = 0; k_6 < 8; k_6++)\n        {\n            tmp_6[i_6 * 8 + k_6] = 0;\n            for (int j_6 = 0; j_6 < 8; j_6++)\n            {\n                tmp_6[i_6 * 8 + k_6] += tmp_4[i_6 * 8 + j_6] * tmp_5[j_6 * 8 + k_6];\n            }\n        }\n    }\n    float tmp_7[8 * 2];\n    for (int i_7 = 0; i_7 < 8; i_7++)\n    {\n        for (int k_7 = 0; k_7 < 2; k_7++)\n        {\n            tmp_7[i_7 * 2 + k_7] = 0;\n            for (int j_7 = 0; j_7 < 8; j_7++)\n            {\n                tmp_7[i_7 * 2 + k_7] += tmp_3[i_7 * 8 + j_7] * tmp_6[j_7 * 2 + k_7];\n            }\n        }\n    }\n    for (int i_7 = 0; i_7 < 16; i_7++)\n        result[i_7] = tmp_7[i_7];\n}"}

    print(gen_bench(desc))