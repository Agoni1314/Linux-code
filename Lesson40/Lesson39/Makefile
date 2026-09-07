.PHONY:all
all:Tcpclient Tcpserver

udpclient:TcpClient.cc
	g++ -o $@ $^ -std=c++17
udpserver:TcpServer.cc
	g++ -o $@ $^ -std=c++17 -lpthread

.PHONY:clean
clean:
	rm -f Tcpclient Tcpserver