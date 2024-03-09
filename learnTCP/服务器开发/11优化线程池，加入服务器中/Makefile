th:
	g++ -pthread \
	src/threadpool.cpp \
	threadtest.cpp -o threadTest

test:
	g++ src/util.cpp src/Buffer.cpp src/Socket.cpp src/InetAddress.cpp src/threadpool.cpp \
	-pthread \
	test.cpp -o test

clean:

	rm threadTest && rm test