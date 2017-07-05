#!/bin/env python
#!encoding:utf-8
'''
1.yield是生成的意思，但是在Python中则是作为生成器理解，生成器的用处主要可以迭代，这样简化了很多运算模型，提升了性能，降低了内存占用率。
2.yield是一个表达式,是有返回值的.
3.当一个函数中含有yield时,它不再是一个普通的函数,而是一个生成器.当该函数被调用时不会自动执行,而是暂停,

* 使用方法：
1.打开python交互界面；
2.import yield_demo.py; p=yield_demo.test(); p.next() etc.
'''

def test():
    print 'before yield.'
    yield 5
    print 'before second yield.'
    yield 10
test()
