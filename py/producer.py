#!/bin/env python
#!encoding:utf8

import qbus
import signal
import sys
import subprocess
import time

##################123.103.20.150####################
def follow(thefile): 
    thefile.seek(0,2) 
    while True: 
        line = thefile.readline() 
        if not line: 
            time.sleep(0.1) 
            continue
        yield line 
####################################################

def getLine():
	logfile='../sdk.log'
	command='tail -f '+logfile
	popen=subprocess.Popen(command,stdout=subprocess.PIPE,stderr=subprocess.PIPE,shell=True) 
	while True: 
	    line=popen.stdout.readline().strip() 
        print 123
        print line

if (len(sys.argv) > 4):
	cluster = sys.argv[1]
	topic = sys.argv[2]
else:
	print "Invaild parameter!"
	print "Usage: python producer.py <cluster> <topic> isSyncSend[1:sync 0:async] key[\"\" or ]"
	sys.exit(1)

producer = qbus.QbusProducer()
ret = producer.init(cluster, "./producer.log", "./producer.config", topic)
if ret != True:
	print "Failed init"
	sys.exit(1)

if __name__ == '__main__': 
    logfile = open("../sdk.log","r") 
    loglines = follow(logfile) 
    for line in loglines: 
        try:
            #line = raw_input()
            #监测日志文件sdk.log,收集该文件里的日志
            #print line
            ret = producer.produce(line, len(line), sys.argv[4])
            if ret != True:
                print "Failed to produce\n"
            #Retry to produce
        except KeyboardInterrupt:
            producer.uninit()
            run = False

