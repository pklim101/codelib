test_signal_loop:test_signal_loop.cpp
	g++ $^ -o $@ -levent -L/usr/local/lib -Wl,-rpath=/usr/local/lib
	./$@

clean:
	rm -rf test_signal_loop
	rm -rf *.o
