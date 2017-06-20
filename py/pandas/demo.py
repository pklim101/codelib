#!/bin/env python
#! coding:utf-8

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

#In [4]: s = pd.Series([1,3,5,np.nan,6,8])

# 读取csv文件.
info = pd.read_csv('data.csv')

# print(type(info))   <class 'pandas.core.frame.DataFrame'>

# head(m)来读取前m条数据，默认5条.

first = info.head()
#print first

# colums属性显示全部的列名
#print info.columns 

# 用tolist()转化为list
#print info.columns.tolist()

'''
# shape属性显示数据的行列总数
dimensions = info.shape
print dimensions    # (10,3)
print dimensions[0] # 10
print dimensions[1] # 3
'''
# 打印数据类型
# print info.dtypes

# 选择行标号为0的数据，即第一行的数据
#print info.loc[0]

# 选择多行数据
#print info.loc[3:6]

# 返回指定列标签的列数据.
#print info['k1']

#返回两列数据
#print info[['k1','k2']]

# 获取该列的最大值
#print info['k1'].max()


# 添加新列
info['new'] = info['k1']/8
#print info

# 对列排序
#print info.sort("k1")


age_null = pd.isnull(info['k2'])
#print age_null

age_null_true = age_null[age_null == True]

age_null_count = len(age_null_true)
#print age_null_count
#print age_null_true

# 计算平均值【因为有空值，所以需要先去掉空值再计算】
avg = sum(info['k2'][age_null == False]) / len(info['k2'][age_null == False])
#print avg

# Pandas的mean()方法可以自动过滤缺失的数据并计算平均值.
avg2 = info['k2'].mean()
#print avg2

# index参数指明了用来分类的列，values标签指明了用来计算的列，aggfunc指明了使用什么函数来计算values指定的列
age = info.pivot_table(index='k1', values='new', aggfunc=np.mean)
print age 
