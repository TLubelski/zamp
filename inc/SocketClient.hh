#pragma once

#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Port.hh"

using std::cerr;
using std::cout;
using std::endl;

class SocketClient
{
private:
  int rSocket;

public:
  SocketClient() {}

  bool Open(int port = PORT)
  {
    struct sockaddr_in DaneAdSerw;

    bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
    DaneAdSerw.sin_port = htons(PORT);

    rSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (rSocket < 0)
    {
      cerr << "*** Blad otwarcia gniazda." << endl;
      return false;
    }

    if (connect(rSocket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0)
    {
      cerr << "*** Brak mozliwosci polaczenia do portu: " << port << endl;
      return false;
    }
    return true;
  }

  bool Send(const char *sMesg)
  {
    ssize_t IlWyslanych;
    ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);

    while ((IlWyslanych = write(rSocket, sMesg, IlDoWyslania)) > 0)
    {
      IlDoWyslania -= IlWyslanych;
      sMesg += IlWyslanych;
    }
    if (IlWyslanych < 0)
    {
      cerr << "*** Blad przeslania napisu." << endl;
    }
    usleep(100000);
  }

  void Close()
  {
    Send("Close\n");
    close(rSocket);
  }
};