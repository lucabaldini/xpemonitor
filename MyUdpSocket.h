#ifndef PUDPSOCKET_H
#define PUDPSOCKET_H
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
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
  
  bool connect(const int port, int to); 
  int readDataGram (char *datagram, int dsize);
  int writeDataGram (char *datagram, int dsize);
  bool isValid() const {return m_sock != -1;}
   
 private:
  WSADATA wsaData;
  SOCKET m_sock;
  sockaddr_in m_addr, Sender_addr, Recv_addr;
  int retval;
 };


#endif
