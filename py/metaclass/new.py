#!/bin/env python
#!encoding:utf8

# __new__ 是在__init__之前被调用的特殊方法
# __new__是用来创建对象并返回之的方法
# 而__init__只是用来将传入的参数初始化给对象
# 你很少用到__new__，除非你希望能够控制对象的创建
# 这里，创建的对象是类，我们希望能够自定义它，所以我们这里改写__new__
# 如果你希望的话，你也可以在__init__中做些事情
# 还有一些高级的用法会涉及到改写__call__特殊方法，但是我们这里不用
class UpperAttrMetaclass(type):
    def __new__(cls, name, bases, dct):
        attrs = ((name, value) for name, value in dct.items() if not name.startswith('__'))
        uppercase_attr = dict((name.upper(), value) for name, value in attrs)
        return super(UpperAttrMetaclass, cls).__new__(cls, name, bases, uppercase_attr)

