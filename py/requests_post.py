#!/bin/env python
#!coding:utf-8
# ref : http://blog.csdn.net/shanzhizi/article/details/50903748

import requests
import json

#各种HTTP请求汇总
'''
requests.get(‘https://github.com/timeline.json’) #GET请求
requests.post(“http://httpbin.org/post”) #POST请求
requests.put(“http://httpbin.org/put”) #PUT请求
requests.delete(“http://httpbin.org/delete”) #DELETE请求
requests.head(“http://httpbin.org/get”) #HEAD请求
requests.options(“http://httpbin.org/get”) #OPTIONS请求
'''

#GET请求
rg = requests.get(url='http://dict.baidu.com/s', params={'wd':'python'})
#print rg.text

#POST请求
url = 'http://xxx.com/dictlog/file'
headers = {'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:22.0) Gecko/20100101 Firefox/22.0'}


enginemd5 = {"mobile.txt":"d3dd14d987641a4458f1fa676d04b06a","word.txt":"2eda626a48580359b31610dc56e1ef45"}
e = json.dumps(enginemd5)

data = {'salt':'17a8b8856557853d176ba2adc74b105f','dict':'d','enginemd5':e}


r = requests.post(url, data=data, headers=headers)


print r.status_code #响应状态码
print r.raw #返回原始响应体，也就是 urllib 的 response 对象，使用 r.raw.read() 读取
print r.content #字节方式的响应体，会自动为你解码 gzip 和 deflate 压缩
print r.text #字符串方式的响应体，会自动根据响应头部的字符编码进行解码
print r.headers #以字典对象存储服务器响应头，但是这个字典比较特殊，字典键不区分大小写，若键不存在则返回None
#*特殊方法*#
print r.json() #Requests中内置的JSON解码器
print r.raise_for_status() #失败请求(非200响应)抛出异常
