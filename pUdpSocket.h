#ifndef PUDPSOCKET_H
#define PUDPSOCKET_H


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

#include <iostream>

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;



class pUdpSocket
{
 public:
  pUdpSocket();
  virtual ~pUdpSocket();

  // Server initialization
  bool create();

  bool connect ( const int port, int timeout );
  int readDataGram (char *datagram, int dsize);
  bool isValid() const { return m_sock != -1; }

 private:
  int retval;
  int m_sock;
  struct timeval tv;
  sockaddr_in m_addr, Sender_addr, Recv_addr;
 

};


#endif
