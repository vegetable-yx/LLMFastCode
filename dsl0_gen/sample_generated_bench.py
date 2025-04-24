import srsly

benchmarks = list(srsly.read_jsonl("benchmark_L_100.jsonl"))
benchmarks.sort(key=lambda x: len(x["code"]))
# srsly.write_jsonl("benchmark_S_10.jsonl", benchmarks[:10])


# res = []
# for i in benchmarks:
#     if len(res) == 10:
#         break
#     if '1024' in i['code']:
#         res.append(i)
# srsly.write_jsonl("benchmark_L_10.jsonl", res)


res = []
for i in benchmarks:
    if len(res) == 10:
        break
    if '4096' in i['code']:
        res.append(i)
srsly.write_jsonl("benchmark_L_10.jsonl", res)
