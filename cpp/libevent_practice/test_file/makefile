test_file:test_file.cpp
	g++ $^ -o $@ -levent -std=c++11 -L/usr/local/lib -Wl,-rpath=/usr/local/lib
	./$@

clean:
	rm -rf test_file
	rm -rf *.o
