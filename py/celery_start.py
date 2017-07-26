#!/bin/env python
#!encoding:utf-8
#####
# celery
####
# 使用celery包含三个方面:
#   1.定义任务函数，
#   2.运行celery服务，
#   3.客户应用程序的调用。
# Usage:
#   1.在命令行注册任务：celery -A celery_start worker --loglevel=info
#   2.在命令行进入python交互界面，执行：
#        from tasks import add
#        add.delay(2, 2)
#        则可以看到log的结果，在redis里也可以看到结果.


from celery import Celery

broker = 'redis://127.0.0.1:6379/5'
backend = 'redis://127.0.0.1:6379/6'

#指定了任务名tasks（和文件名一致）
app = Celery('celery_start', broker=broker, backend=backend)

@app.celery_start
def add(x, y):
    return x + y

