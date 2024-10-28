import re
path = "../../../yosys-sta/result/ypc-500MHz/synth_stat.txt"
pattern_normal = re.compile(r"\s*Chip area for module\s*")
pattern_top = re.compile(r"\s*Chip area for top module\s*")
pattern_name = re.compile(r"'(.*?)'")
pattern_area = re.compile(r"\d+\.\d+")

results = {}
total=None
cache_data=None

def get_name_area(line):
    name=pattern_name.findall(str(line))[0]
    area=pattern_area.findall(str(line))[0]
    return name , float(area)

def find_area():
    global total,cache_data
    with open(path,"r") as file:
        lines = file.readlines()
        for l in lines:
            if(pattern_normal.match(l)):
                # print(l,end="")
                name,area=get_name_area(l)
                results[name]=area
                if(str(name)=='\\icache_data'):
                    cache_data=area
            if(pattern_top.match(l)):
                # print(l,end="")
                name,area=get_name_area(l)
                results['total']=area
                total=area


def get_result():
    sorted_dict = dict(sorted(results.items(), key=lambda item: item[1]))
    max_key_length = max(len(key) for key in sorted_dict)
    for item in sorted_dict:
        print(f"{item:<{max_key_length}}\t{sorted_dict[item]:.2f}")
    print(f"(total-icache_data)->{total-cache_data:.2f}")


find_area()
get_result()
