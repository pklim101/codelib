#!/bin/env python

import os
import sys
import posixpath
class A:
    def __init__(self, t):
        print t
    

p = A("hello")

l = [5,3,1,7,2]
def rev(x,y):
    return x-y
print l.sort(cmp=rev)
print l
