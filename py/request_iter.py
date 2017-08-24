#!/bin/env python
import requests
import time
import re
#end_of_field = re.compile(r'\r\n|\r\n|\r\r|\n\n')
end_of_field = re.compile(r'30006')
url = 'http://beta.e.tf.360.cn/b/app?_=xx'
headers = {"User-Agent":"xx"}
ct = requests.get(url,stream=True,headers=headers)
c = ct.iter_content(10)
buf = ''
next_chunk = ''
while 1:
    try:
        next_chunk += next(c)
        if not next_chunk:
            raise EOFError()
        buf += next_chunk
        #print next_chunk
        #print '---------------'
    except(StopIteration) as e:
        head, sep, tail = buf.rpartition('\n')
        print head, sep, tail 
        buf = head+tail
        print "except:", buf
        break
#print buf 
print end_of_field
(event_string, buf) = re.split(end_of_field, buf, maxsplit=1)
print event_string
print '---------'
print buf
