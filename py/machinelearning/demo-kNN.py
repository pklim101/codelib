#!/bin/env python
#!coding:utf-8

########################
# k-近邻算法
########################
# step 1. 先求出距离：欧式 差->平方->开方
# step 2. 排序求出距离最近的前k个样本;
# step 3. 排序求出分类出现频率最高的第一个分类.

from numpy import *
import operator

def createDataSet():
    group = array([[1.0,1.1],[1.0,1.0],[0,0],[0,0.1]])
    labels = ['A','A','B','B']
    return group, labels

group,labels = createDataSet()

def classify0(inX, dataSet, labels, k):
    dataSetSize = dataSet.shape[0] #取样本集行数
    diffMat = tile(inX, (dataSetSize,1)) - dataSet #求矩阵差
    sqDiffMat = diffMat ** 2   #平方
    sqDistances = sqDiffMat.sum(axis=1) #对矩阵行求和
    distances = sqDistances**0.5    #开方，得到与每个点(样本)的差值
    sortedDistIndicies = distances.argsort() #排序，便于获得最近前k个样本
    classCount={}
    for i in range(k):
        voteIlabel = labels[sortedDistIndicies[i]]
        classCount[voteIlabel] = classCount.get(voteIlabel,0) + 1
    sortedClassCount = sorted(classCount.iteritems(),key=operator.itemgetter(1), reverse=True)
    return sortedClassCount[0][0] # 排在最前面的就是分类出现频率最高的一个分类

print classify0([0,0],group,labels,3)
