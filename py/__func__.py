#!/bin/env python
#!coding:utf-8
#
# python里用户可以直接定义__next__()这样双下划线的函数，但是最好别这样做，
# 因为默认是系统函数这样使用。
#
# 

class A(object):
    def __init__(self):
        print "this is A.__init__"

    def __next__(self):
        print "next"

p = A()

p.__next__()

print dir(p)
