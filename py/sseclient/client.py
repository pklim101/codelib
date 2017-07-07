#!/bin/evn python
#!coding:utf-8
#
# 这里messages通过SSEClient类里的__iter__()和__next()__方法生成了一个迭代器对象，所以可以通过for in打印出元素。
#

from sseclient import SSEClient

url = "http://xxx/sse.php"
messages = SSEClient(url,retry=3)

for msg in messages:
    print msg 


