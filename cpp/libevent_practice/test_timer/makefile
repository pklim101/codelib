test_timer:test_timer.cpp
	g++ $^ -o $@ -levent -L/usr/local/lib -Wl,-rpath=/usr/local/lib
	./$@

clean:
	rm -rf test_timer
	rm -rf *.o
