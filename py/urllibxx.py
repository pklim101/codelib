#!/bin/ent python
'''
urlib 实现文件下载到指定路径.  且可实现下载进度展示(reporthook参数).
'''
import urllib
url="http://a.com/dictdir/x.txt"
urllib.urlretrieve(url,'1.txt')

'''
urllib2 添加headers头实现文件下载.
'''
import urllib2
url="http://a.com/dictdir/x.txt"
#urllib.urlretrieve(url,'1.txt')

headers = {'User-Agent':'Mozilla/5.0 (Windows NT 6.2; rv:16.0) Gecko/20100101 Firefox/16.0'}

req = urllib2.Request(url,headers=headers)
f = urllib2.urlopen(req)
data = f.read()
with open("x.txt", "wb") as code:
    code.write(data)

