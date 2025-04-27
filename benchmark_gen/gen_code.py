from openai import OpenAI
import os
import re
import shutil
from datetime import datetime
from gen_prompt import gen_prompt

def extract_function(text):
    start_pattern = r'void max_performance'
    start_match = re.search(start_pattern, text)
    
    if not start_match:
        return None
    
    start_pos = start_match.start()
    pos = start_match.end()
    brace_count = 0
    found_first_brace = False
    
    while pos < len(text):
        char = text[pos]
        
        if char == '{':
            found_first_brace = True
            brace_count += 1
        elif char == '}':
            brace_count -= 1
            
        pos += 1
        
        if found_first_brace and brace_count == 0:
            return text[start_pos:pos]
    
    return None


def generate_execute_code(src_folder):
    with open("../api_key.txt", "r") as f:
        claude_api_key = f.read().strip()

    client = OpenAI(
        api_key=claude_api_key,  # Your Anthropic API key
        base_url="https://api.anthropic.com/v1/"  # Anthropic's API endpoint
    )

    prompt = gen_prompt(src_folder)

    response = client.chat.completions.create(
        model="claude-3-7-sonnet-20250219", # Anthropic model name
        messages=[
            {"role": "system", "content": "You are a helpful assistant."},
            {"role": "user", "content": f"{prompt}"}
        ],
    )

    result = response.choices[0].message.content

    if result:
        print("Success")
        print(result)

        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S_%f")
        dst_folder = os.path.join('./output', f"result_{timestamp}")
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
                if file == "implementation.cpp":
                    pattern = re.compile(r'/\*\s*Max performance function start\s*\*/(.*?)/\*\s*Max performance function end\s*\*/', re.DOTALL)
                    with open(os.path.join(root, file), "r", encoding="utf-8") as f:
                        content = f.read()
                    match = pattern.search(content)
                    if match:
                        new_content = pattern.sub(result, content)
                        with open(os.path.join(root, file), "w", encoding="utf-8") as fw:
                            fw.write(new_content)
                    break
    return dst_folder
if __name__ == "__main__":
    src_folder = "./output/run_20250425_221250_483741"
    generate_execute_code(src_folder)