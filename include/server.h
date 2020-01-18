#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

class Server {
public:
  Server();
  Server(int port);
  void listen();
  void accept();
  void write(std::string);
  std::string read(char *, int);
  void print();

private:
  int clfd_;
  struct sockaddr_in peeraddr_;
  socklen_t peeraddr_len;
};