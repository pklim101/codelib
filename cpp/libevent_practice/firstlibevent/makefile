firstlibevent:firstlibevent.cpp
#makefile:2: *** 遗漏分隔符 。 停止 ===>原因：下面行的前面要用tab而不能用空格
#$^表示上面的源文件，$@表示上面的目标文件
#undefined reference to `event_base_new', 错误：ld.  表示未连接libevent库
	g++ $^ -o $@ -levent
#下面行执行文件，自动测试
	./$@

clean:
	rm -rf firstlibevent
	rm -rf *.o
