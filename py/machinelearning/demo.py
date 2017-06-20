#!/bin/env python
#!coding:utf-8
#######################
# demo测试
#######################

from numpy import *

t = random.rand(4,4)
#print t
randMat = mat(t)
print randMat
revert = randMat.I
print revert
myeye = randMat*revert
print myeye-eye(4)
