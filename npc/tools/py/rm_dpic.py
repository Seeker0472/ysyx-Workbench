import re

in_fileName = "../../build/ypc.sv"
out_fileName = "../../build/ypc_nodpic.sv"
in_file = open(in_fileName)
out_file = open(out_fileName, "w")

dpic_pattern = re.compile(r"\s*import \"DPI-C\" function\s*")
input_start_pattern =re.compile(r"\s*module\s*\(")
input_end_pattern =re.compile(r"\s*\);\s*")
endmodule_pattern = re.compile(r"\s*endmodule\s*")

state =0

for line in in_file:
    # print(line)
    if(dpic_pattern.match(line)):
        print(line)
        state=1
        continue
    if(input_end_pattern.match(line) and state==1):
        print(line)
        state=2
        out_file.write(line)
    if(endmodule_pattern.match(line) and state==2):
        print(line)
        state=0
    if(state==2):
        continue
    out_file.write(line)