server:
	g++ src/util.cc client.cpp -o client && \
	g++ src/util.cc server.cpp src/Epoll.cpp src/InetAddress.cpp src/Socket.cpp src/Channel.cpp src/EventLoop.cpp src/Server.cpp -o server
clean:
	rm server && rm client