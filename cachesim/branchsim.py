from collections import OrderedDict

class FIFOCache:
    def __init__(self, capacity: int = 2):
        self.cache = OrderedDict()
        self.capacity = capacity

    def get(self, key: int) -> int:
        return self.cache.get(key, -1)

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self.cache.move_to_end(key)
        self.cache[key] = value
        if len(self.cache) > self.capacity:
            self.cache.popitem(last=False)

fifocache = FIFOCache()
success = 0
fail =0

def calc_next(pc,n_pc,type,imm):
    global success,fail
    if(type=="B_Type"):
        if(int(imm,16) & 0x80000000 != 0):
            # print(imm)
            if(fifocache.get(pc)!=n_pc):
                fail+=1
                fifocache.put(pc,n_pc)
            else:
                success+=1

def read_file():
    with open("b_trace","r") as branch_trace:
        for line in branch_trace:
            result=line.replace("\n","").split(",")
            calc_next(result[0],result[1],result[3],result[2])

def sim():
    global fifocache,success,fail
    for i in range(1,7):
        success=0
        fail=0
        fifocache=FIFOCache(i)
        read_file()
        print(i,end="-")
        print(success/(success+fail))


sim()
