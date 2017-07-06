#!/bin/env python
#!encoding:utf-8
#################
# 用yield实现斐波拉契数列
################

# 普通方式
def fab(m):
    num = []
    a,b,n = 0,1,0
    while m>n:
        r = b
        num.append(r)
        a,b = b,a+b
        n = n+1
    return num 
#print type(fab(10))  #<type 'list'>'

# yield实现
# 使用方式：1.命令行打开python交互界面;
#           2.import fab;  p=fab2(10); 多次输入next(p)可迭代输出fab数列。
#           注意：p.next()等同于next(p)
def fab2(m):
    a,b,n = 0,1,0
    while m>n:
        yield b
        a,b = b,a+b
        n = n+1
#print type(fab2(10)) # <type 'generator'>'

# 创建支持iterabled类.
'''
用法一：
f = Fab(10)
for i in f:
    print i
用法二：
1.打开python交互界面;
2.import fab; p=fab.Fab(10);多次输入next(p)可迭代输出fab数列.
'''
class Fab(object):
    def __init__(self,m):
       self.a = 0
       self.b = 1
       self.n = 0 
       self.m = m

    # 如果不重写__iter__()方法则报错：TypeError: 'Fab' object is not iterable'
    def __iter__(self):
        return self

    # python3里next()应该为__next__()
    ###
    # 疑惑:将next()改为nexta()，去掉raise StopIteration(),都可以通过p.nexta()迭代.
    ##
    def next(self):
        if self.n < self.m:
            r = self.b
            self.a,self.b = self.b,self.a+self.b
            self.n = self.n+1
            return r
        raise StopIteration() 
f = Fab(10)
print type(f) # <type 'instance'>'   如果继承objec，则输出<class '__main__.Fab'>
