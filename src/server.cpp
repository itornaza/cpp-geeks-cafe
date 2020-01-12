#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int port = 1234;
  int fd;            // Server socket file descriptor
  int clfd;          // Client connection file descriptor
  int rx_bytes;      // Number of received bytes from the client
  char buffer[1024]; // Buffer to hold the received bytes from the client
  int listener_queue_len = 1;
  struct sockaddr_in addr;
  struct sockaddr_in peeraddr;
  socklen_t peeraddr_len;
  struct linger linger_opt = {1, 0}; // Linger active, timeout 0

  //-------------------
  // Parse input
  //-------------------

  if (argc > 1 && *(argv[1]) == '-') {
    std::cout << "Usage:" << std::endl
              << "$ server [port_to_listen]" << std::endl
              << "Default port is 1234" << std::endl;
    exit(1);
  }

  if (argc > 1) {
    port = atoi(argv[1]);
  }

  //-------------------
  // Set up listener
  //-------------------

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(1);
  }

  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(1);
  }

  // Close socket immediately after program termination
  setsockopt(fd, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

  // Listen for a connection, 1 is the max length of the queue
  if (listen(fd, listener_queue_len) < 0) {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(1);
  }

  //-------------------
  // Handle connection
  //-------------------

  // Accept a connection with no timeout limit
  if ((clfd = accept(fd, (struct sockaddr *)&peeraddr, &peeraddr_len)) < 0) {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(1);
  }

  // Display client connection details
  std::cout << "Connection from IP: "
            << ((ntohl(peeraddr.sin_addr.s_addr) >> 24) & 0xff)
            << "." // High byte of address
            << ((ntohl(peeraddr.sin_addr.s_addr) >> 16) & 0xff) << "."
            << ((ntohl(peeraddr.sin_addr.s_addr) >> 8) & 0xff) << "."
            << (ntohl(peeraddr.sin_addr.s_addr) & 0xff)
            << ", port: " // Low byte of addr
            << ntohs(peeraddr.sin_port) << std::endl;

  //-------------------
  // Handle comms
  //-------------------

  write(clfd, "Hello!\r\n", 8);

  if ((rx_bytes = read(clfd, buffer, 1023)) < 0) {
    std::cerr << "Error: " << strerror(errno) << std::endl;
    exit(1);
  }
  buffer[rx_bytes] = 0;
  std::cout << "Received " << rx_bytes << " bytes:" << std::endl << buffer;

  close(clfd);
  close(fd);

  return 0;
}
