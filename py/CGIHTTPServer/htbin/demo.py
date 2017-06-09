#!/usr/bin/env python
#!coding:utf-8
"""
该文件运行原理说明：
1.导入cgi包，cgi包用于提取请求中的字段信息；
2.该脚本只负责将所有的结果输出(print)到标准输出中，
  而CGIHTTPRequestHandler会收集这些输出封装成HTTP response，传送给客户端。

该文件demo运行方法：
1.在CGIHTTPServer启动目录新建mkdir htbin 或者Cgi-bin目录；
2.将demo.py文件放入htbin中；
3.curl发请求测试:curl "http://127.0.0.1:8000/htbin/demo.py?d=1" -d "a=aaa"
"""

import cgi
form = cgi.FieldStorage()

print "Content-Type: text/html" # HTML is following
print # blank line, end of headers

print "<TITLE>CGI script output</TITLE>"
print "<H1>This is my first CGI script</H1>"
print "Hello, world!"
print repr(form['a'])
print repr(form['d'])


