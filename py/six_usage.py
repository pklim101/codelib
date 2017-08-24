#!/bin/env python
#!encoding:utf8
import six

class A():
    def __init__(self, test):
        print 'this is six_usage.'
        self.test = test

    def __next__(self):
        print 'hahahhahaha'
    def next(self):
        print 'hahahhahaha'
    #感觉这里像是新增类方法和属性.
    #实例化的时候，该部分代码被执行，且类方法会被执行.
    if six.PY2:
        next = __next__
        test = 'new change'
        test2 = 'new add'

p = A('init change')
print type(p)
p.next()
# 如果未设置成员变量test，则if six.PY2中的设置会改变test.
print p.test
print p.test2

