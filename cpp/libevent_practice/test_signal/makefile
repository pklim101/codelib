test_signal:test_signal.cpp
	g++ $^ -o $@ -levent -L/usr/local/lib -Wl,-rpath=/usr/local/lib
	./$@

clean:
	rm -rf test_signal
	rm -rf *.o
