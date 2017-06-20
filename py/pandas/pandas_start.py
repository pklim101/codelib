#!/bin/env python
#!coding:utf-8
import pandas as pd
import numpy as np
import seaborn
import matplotlib.pyplot as plt

#传递list对象来创建Series
s = pd.Series([1,3,5,np.nan,6,8])
#print s

dates = pd.date_range('20130101', periods=6)
#print dates

df = pd.DataFrame(np.random.randn(6,4),index=dates,columns=list('ABCD'))
#print df

#print np.random.randn(6,4)

###【很有用】对数据进行快速统计汇总
#print df.describe()

#print df.T

ts = pd.Series(np.random.randn(1000), index=pd.date_range('1/1/2000',periods=1000))
ts = ts.cumsum()
print ts
#ts.plot()
