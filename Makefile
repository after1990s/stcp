CPPFLAGS=-std=c++11 -pthread -DDEBUG -O0 -g
CC=clang++
a.out: main.o stcp_cache.o stcp_socket.o stcp_socket_tcp.o stcp_socket_accept.o stcp_socket_connect.o stcp_socket_accept.o
	$(CC) $(CPPFLAGS) -o a.out main.o stcp_cache.o stcp_socket.o stcp_socket_tcp.o stcp_socket_accept.o stcp_socket_connect.o stcp_socket_accept.o
main.o: main.cpp stcp_cache.h
	$(CC) $(CPPFLAGS) -c main.cpp

stcp_cache.o: stcp_cache.h stcp.h stcp_cache.cpp
	$(CC) $(CPPFLAGS) -c stcp_cache.cpp

stcp_socket.o: stcp_socket.h stcp_socket.cpp
	$(CC) $(CPPFLAGS) -c stcp_socket.cpp	

stcp_socket_tcp.o: stcp_socket_tcp.h stcp_socket.h stcp_socket_tcp.cpp
	$(CC) $(CPPFLAGS) -c stcp_socket_tcp.cpp

stcp_socket_accept.o: stcp_socket_tcp.h stcp_socket.h stcp_socket_accept.h stcp_socket_accept.cpp
	$(CC) $(CPPFLAGS) -c stcp_socket_accept.cpp

stcp_socket_connect.o: stcp_socket_tcp.h stcp_socket.h stcp_socket_connect.h stcp_socket_connect.cpp
	$(CC) $(CPPFLAGS) -c stcp_socket_connect.cpp

stcp_log.o: stcp_log.h stcp_log.cpp
	$(CC) $(CPPFLAGS) -c stcp_log.cpp

clean:
	rm *.o
