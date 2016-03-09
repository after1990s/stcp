CPPFLAGS=-std=c++11 -pthread -DDEBUG -O0 -g
CC=g++
all: a.out
a.out: main.o queue_socket.o queue_packet.o stcp_api.o stcp_cache.o stcp_socket.o stcp_socket_tcp.o stcp_socket_accept.o stcp_socket_connect.o stcp_socket_accept.o
	$(CC) $(CPPFLAGS) -o a.out main.o queue_socket.o queue_packet.o stcp_api.o stcp_cache.o stcp_socket_base.o stcp_socket_tcp.o stcp_socket_accept.o stcp_socket_connect.o stcp_socket_accept.o
main.o: main.cpp stcp_cache.h
	$(CC) $(CPPFLAGS) -c main.cpp

queue_socket.o: queue_socket.h queue_socket.cpp
	$(CC) $(CPPFLAGS) -c queue_socket.cpp

queue_packet.o: queue_packet.h queue_packet.cpp
	$(CC) $(CPPFLAGS) -c queue_packet.cpp
	
stcp_cache.o: stcp_cache.h stcp.h stcp_cache.cpp
	$(CC) $(CPPFLAGS) -c stcp_cache.cpp

stcp_socket.o: stcp_socket_base.h stcp_socket_base.cpp
	$(CC) $(CPPFLAGS) -c stcp_socket_base.cpp	

stcp_socket_listen.o: stcp_socket_listen.h stcp_socket_listen.cpp queue_socket.h 
	$(cc) $(CPPFLAGS) -c stcp_socket_listen

stcp_socket_tcp.o: stcp_socket_tcp.h stcp_socket_base.h stcp_socket_tcp.cpp
	$(CC) $(CPPFLAGS) -c stcp_socket_tcp.cpp

stcp_socket_accept.o: stcp_socket_tcp.h stcp_socket_base.h stcp_socket_accept.h stcp_socket_accept.cpp
	$(CC) $(CPPFLAGS) -c stcp_socket_accept.cpp

stcp_socket_connect.o: stcp_socket_tcp.h stcp_socket_base.h stcp_socket_connect.h stcp_socket_connect.cpp
	$(CC) $(CPPFLAGS) -c stcp_socket_connect.cpp

stcp_log.o: stcp_log.h stcp_log.cpp
	$(CC) $(CPPFLAGS) -c stcp_log.cpp

stcp_api.o: stcp_api.h queue_socket.h stcp_api.cpp queue_socket.o
	$(CC) $(CPPFLAGS) -c stcp_api.cpp
	
clean:
	rm *.o
