CC=clang++
CPPFLAGS=-std=c++11 -lpthread -O0 -g -DDEBUG
all: log_test.out
log_test.out:
	$(CC) $(CPPFLAGS) log_test.cpp ../stcp_log.cpp -o log_test.out 

clean:
	rm *.out
	rm *.o
