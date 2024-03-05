server:
	g++ util.cc client.cpp -o client && \
	g++ util.cc server.cpp Epoll.cpp InetAddress.cpp Socket.cpp Channel.cpp -o server
clean:
	rm server && rm client