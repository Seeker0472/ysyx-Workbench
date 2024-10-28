import re
pattern = re.compile(
    r"-?\d+\.\d+"
)

path_in = "../../../yosys-sta/result/ypc-500MHz/ypc.rpt"
path_out ="../../../ysyxSoC/src/amba/DelayerParams.scala"

def read_fifth_line():
    with open(path_in, 'r') as file:
        lines = file.readlines()
        if len(lines) >= 5:
            return lines[4].strip()  # 索引4是第五行
        else:
            return None  # 文件行数不足5行
def replace(result):
    with open(path_out,"w") as file:
        file.write(
f"package ysyx\n\
object DelayerParams{{\n\
    val FREQ={result}\n\
}}")
    pass

fifth_line = read_fifth_line()
if fifth_line:
    result = pattern.findall(fifth_line)[-1]
    print(f"Updating Delayer's Param FREQ={int(float(result))}")
    replace(int(float(result)))
else:
    print("文件不足五行")
