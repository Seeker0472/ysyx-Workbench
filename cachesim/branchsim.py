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
fifocache_pc = FIFOCache()
success = 0
fail =0
# TODO!
def calc_next(pc,n_pc,type,imm):
    global success,fail
    next_pc_predict=pc+4
    if(fifocache.get(pc)!=-1):
        next_pc_predict=fifocache.get(pc)
    if(fifocache_pc.get(pc)!=-1):
        next_pc_predict=fifocache_pc.get(pc)
    if(imm & 0x80000000 != 0 and type=="B_Type"):# imm<0,record
        fifocache.put(pc,n_pc)
    if(type!="B_Type" and type != "ret" ):# imm<0,record
        print(type)
        fifocache_pc.put(pc,n_pc)
    

    if(next_pc_predict==n_pc): #predict
        success+=1
    else:
        fail+=1

def read_file():
    with open("b_trace","r") as branch_trace:
        for line in branch_trace:
            result=line.replace("\n","").split(",")
            calc_next(int(result[0],16),int(result[1],16),result[3],int(result[2],16))

def sim():
    global fifocache,success,fail,fifocache_pc
    for i in range(1,7):
        success=0
        fail=0
        fifocache=FIFOCache(i)
        fifocache_pc=FIFOCache(i)
        read_file()
        print(i,end="-")
        print(success/(success+fail))


sim()
