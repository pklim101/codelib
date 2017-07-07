#!/bin/evn python
#!coding:utf-8
#
# specification: https://www.w3.org/TR/2009/WD-eventsource-20091029/
#
# 这里messages通过SSEClient类里的__iter__()和__next()__方法生成了一个迭代器对象，所以可以通过for in打印出元素。
#

from sseclient import SSEClient

#url = "http://xxx/sse.php"
url = "http://mesos01.adsys.zzzc.qihoo.net:8080/v2/events"
messages = SSEClient(url,retry=3)

for msg in messages:
    print msg 


