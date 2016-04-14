// Implementation of the Socket class.

#include "MyUdpSocket.h"
#include <fcntl.h>

pUdpSocket::pUdpSocket() :
  m_sock (-1)
{
  memset(&m_addr, 0, sizeof m_addr);
  create();
 }

pUdpSocket::~pUdpSocket()
{
  if (isValid())closesocket (m_sock);
  std::cout << "Connection closed!" << std::endl;
  return;
}


bool pUdpSocket::create()
{
  // Initialize Winsock -- added by GS
  if((retval = WSAStartup(MAKEWORD(2,2), &wsaData))!=NO_ERROR){
    std::cout<< "WSAStartup failed with ERROR = " << retval << std::endl;
    WSACleanup();
    return false;
  }
 
  m_sock = socket(AF_INET,SOCK_DGRAM,0);
  if (m_sock == INVALID_SOCKET){
    printf("Error at socket(): %ld\n", WSAGetLastError());
    WSACleanup();
    return false;
  }
  int on = 1;
  retval = setsockopt(m_sock,IPPROTO_IP,IP_MULTICAST_TTL,( const char* )&on,sizeof(on));
  if (retval == SOCKET_ERROR){
    printf("Error at socketoption: %ld\n", WSAGetLastError());
    WSACleanup();
    return false;
  }
  return true;
}

bool pUdpSocket::connect(const int port, int timeout)
{
  m_addr.sin_family = AF_INET;
  m_addr.sin_addr.s_addr = INADDR_ANY;
  m_addr.sin_port = htons (port);
  // bind() associates a local address and port with the socket just created. 
  retval = bind (m_sock, (SOCKADDR*)&m_addr, sizeof(m_addr));
  if (retval == SOCKET_ERROR){
    printf("Bind Error: %ld\n", WSAGetLastError());
    WSACleanup();
    return false;
  }
  //int t = 10000; //10 sec
  setsockopt(m_sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
  return true;
}

int pUdpSocket::readDataGram (char *datagram, int dsize)
{
 
  int nbyte = 0;
  int SenderAddrSize = sizeof(Sender_addr);
  nbyte = recvfrom(m_sock, datagram, dsize, 0, (struct sockaddr*)&Sender_addr, (int*)&SenderAddrSize);

  if (nbyte == SOCKET_ERROR) {
    if (WSAETIMEDOUT == WSAGetLastError()){
      //recvfrom has timed out
      std::cout << "Timeout! Connection closed!!" << std::endl; 
      closesocket(m_sock);
      WSACleanup();
      return -1;
    }
    else{
      printf("Receiver failed: ERROR: %ld\n", WSAGetLastError());
      closesocket(m_sock);
      std::cout << "Connection closed! " << std::endl;
      WSACleanup();
      return 0;
    }
  }
  else {
    //std::cout << "Receive " << nbyte << " bytes from" << inet_ntoa(Sender_addr.sin_addr) << std::endl;
    return nbyte;
  }
}

int pUdpSocket::writeDataGram (char *datagram, int dsize)
{
  int RecvAddrSize = sizeof(Recv_addr);
  int nbyte = sendto(m_sock, datagram, dsize, 0, (struct sockaddr*)&Recv_addr, RecvAddrSize);
  std::cout << "Sending data to "<< inet_ntoa(Recv_addr.sin_addr)<< std::endl; 
  if (nbyte == SOCKET_ERROR ){
    printf("Sender failed: ERROR: %ld\n", WSAGetLastError());
    closesocket(m_sock);
    return nbyte;
  }
  else {
    std::cout << "Sent " << nbyte << " bytes" << std::endl;
    return nbyte;
  }
}
