#!/bin/env python
#!coding:utf-8
#
# 成员属性可以通过实例的__dict__属性获取.


class Demo:
    def __init__(self,name,age):
        self.name = name
        self.age = age

    def say():
        print 'hhhh'



p = Demo('jom',16)


print p.__dict__
