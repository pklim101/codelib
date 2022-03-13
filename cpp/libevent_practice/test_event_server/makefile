test_event_server:test_event_server.cpp
	g++ $^ -o $@ -levent -std=c++11 -L/usr/local/lib -Wl,-rpath=/usr/local/lib
	./$@

clean:
	rm -rf test_event_server
	rm -rf *.o
