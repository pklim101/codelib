#!coding:utf-8

import logging
logger = logging.getLogger(__name__)
"""
在这里配置日志生成的格式.
"""
logging.basicConfig(
     level=logging.DEBUG,
     format="%(levelname)s %(asctime)s %(pathname)s %(filename)s %(lineno)s %(name)s.%(funcName)s: %(message)s" 
    )

def test():
    #logger使用方法.
    #括号里的参数是个*args元组，生成的信息都会填充到format里的message字段里。
    logger.debug("%s * 3 = %s", 3, 5)

test()
