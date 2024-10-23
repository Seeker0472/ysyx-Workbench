import re
pattern = re.compile(
    r"\s*set=(\d+),way=(\d+),size=(\d+)\s*hit=(\d+) miss=(\d+) cmiss=(\d+)"
)
results = ["cache_result"]
outfile = "result"
for fileName in results:
    file = open(fileName)
    out = open(outfile)
    for line in file:
        match = pattern.search(line)
        if match:
            print(match.groups())
            rset, rway, rsize, rhit, rmiss, rcmiss = match.groups()
            if(rway!=1):
                continue
            out.write(f"set={rset}size={rsize}penalty={rhit+rmiss*penalty}")
