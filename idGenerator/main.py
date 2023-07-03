import os
import time
import logging
from fastapi import FastAPI

#global vars
machineId = int(os.environ["MACHINE_ID"])
seqCnt = 0
tsPrev = int(time.time())

app = FastAPI()

def getId():
    global tsPrev
    global seqCnt
    ts = int(time.time())
    if (ts == tsPrev):
        seqCnt += 1
    else:
        seqCnt = 0
    tsPrev = ts
    print("timestamp: {}, machineId: {}, seq. cnt.: {}".format(ts, machineId, seqCnt))
    return (ts << 16) + (machineId << 8) + (seqCnt)

@app.get("/")
async def root():
    val = getId()
    return {"id": val}