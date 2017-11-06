#!/bin/env python
#!encoding:utf8

'''
元类：

创建方法：
1.__metaclass__
2.用真正的类+__new__方法

作用：
1)   拦截类的创建
2)   修改类
3)   返回修改之后的类
'''


# 元类会自动将你通常传给‘type’的参数作为自己的参数传入
def upper_attr(future_class_name, future_class_parents, future_class_attr):
    '''返回一个类对象，将属性都转为大写形式'''
    #  选择所有不以'__'开头的属性
    attrs = ((name, value) for name, value in future_class_attr.items() if not name.startswith('__'))

    # 将它们转为大写形式
    uppercase_attr = dict((name.upper(), value) for name, value in attrs)

    # 通过'type'来做类对象的创建
    return type(future_class_name, future_class_parents, uppercase_attr)

#__metaclass__放在这里（即模块级别）调用，竟然不生效.
__metaclass__ = upper_attr  #  这会作用到这个模块中的所有类

class Foo(object):
    __metaclass__ = upper_attr  #  这会作用到这个模块中的所有类
    # 我们也可以只在这里定义__metaclass__，这样就只会作用于这个类中
    bar = 'bip'

print hasattr(Foo, 'bar')
# 输出: False
print hasattr(Foo, 'BAR')
# 输出:True

f = Foo()
print f.BAR
# 输出:'bip'
