// Implementation of the Socket class.


#include "pUdpSocket.h"
#include "string.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>



pUdpSocket::pUdpSocket() :
  m_sock ( -1 )
{

  memset ( &m_addr, 0, sizeof ( m_addr ) );
  create();
  
}

pUdpSocket::~pUdpSocket()
{
  if ( isValid() )
    ::close ( m_sock );
}


bool pUdpSocket::create()
{
  int status = -1;
  
  m_sock = socket(AF_INET,SOCK_DGRAM,0);
  
  if ( ! isValid() )
    return false;

  int on = 1;
  status = setsockopt(m_sock,IPPROTO_IP,IP_MULTICAST_TTL,( const char* )&on,sizeof(on));

  // TIME_WAIT - argh
  if ( status == -1 )
    return false;

  return true;

}

bool pUdpSocket::connect ( const int port, int timeout )
{

  if ( ! isValid() )
    {
      return false;
    }

  m_addr.sin_family = AF_INET;
  m_addr.sin_addr.s_addr = INADDR_ANY;
  m_addr.sin_port = htons ( port );

  int bind_return = ::bind ( m_sock,
			     ( struct sockaddr * ) &m_addr,
			     sizeof ( m_addr ) );


  if ( bind_return == -1 )
    {
      return false;
    }
  
  time_t to = (int)(timeout/1000.);
  tv.tv_sec = to; 
  setsockopt(m_sock, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
  return true;
}

int pUdpSocket::readDataGram (char *datagram, int dsize)
{
  
  int SenderAddrSize = sizeof ( Sender_addr );
  int status = recvfrom( m_sock, datagram, dsize, 0, (struct sockaddr*)&Sender_addr, (socklen_t*)&SenderAddrSize );
  //std::cout << "Receiving data from "<< inet_ntoa(Sender_addr.sin_addr)<< std::endl; 
  //std::cout << status  << std::endl;
  if ( status == -1 )
    {
      if(errno == EWOULDBLOCK){
	//std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
	std::cout << "Timeout! Connection closed!!" << std::endl; 
	return -1;
      }
    }
  if ( status == 0 )
    {
      std::cout << "Receiver error! Connection closed!!" << std::endl; 
      return 0;
    }
  else
    {
      //std::cout << "Received " << status << " bytes" << std::endl;
      return status;
    }
}

