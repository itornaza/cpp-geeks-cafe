#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd; // Socket file descriptor
  char *host_name = "localhost";
  short port = 1234;
  char buffer[1024];
  struct sockaddr_in server;

  //----------------
  // Parse input
  //----------------

  if (argc > 1 && *(argv[1]) == '-') {
    std::cout << "Usage:" << std::endl
              << "$ client [IP_address_of_server [port_of_server]]" << std::endl
              << "Default IP is localhost" << std::endl
              << "Default port is 1234" << std::endl;
    exit(1);
  }

  if (argc > 1) {
    host_name = argv[1];
  }

  if (argc >= 3) {
    port = (short)atoi(argv[2]);
  }

  //-------------------
  // Set up connection
  //-------------------

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(1);
  }

  // Resolve server address (convert from symbolic name to IP number)
  struct hostent *host = gethostbyname(host_name);
  if (host == NULL) {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(1);
  }

  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  // Display server details
  std::cout << "server address: " << (host->h_addr_list[0][0] & 0xff) << "."
            << (host->h_addr_list[0][1] & 0xff) << "."
            << (host->h_addr_list[0][2] & 0xff) << "."
            << (host->h_addr_list[0][3] & 0xff) << ", port: "
            << static_cast<int>(port) << std::endl;

  // Write resolved IP address of a server to the address structure
  memmove(&(server.sin_addr.s_addr), host->h_addr_list[0], 4);
  
  if ((connect(fd, (struct sockaddr *)&server, sizeof(server))) < 0) {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(1);
  }

  //-------------------
  // Handle comms
  //-------------------

  std::cout << "Connected. Reading a server message" << std::endl;
  if ((read(fd, buffer, 1024)) < 0) {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(1);
  }
  std::cout << "Received: " << buffer << std::endl;
  
  write(fd, "Thanks! Bye-bye...\r\n", 20);
  close(fd);

  return 0;
}
