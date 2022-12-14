#include <iostream>
#include "Interp4Pause.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Pause"; }
}

Interp4Command *CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}

Interp4Pause::Interp4Pause() : Interp4Command(""), _Timeout(0)
{
}

void Interp4Pause::PrintCmd() const
{
  cout << GetCmdName() << " " << _Timeout << endl;
}

const char *Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}

// bool Interp4Pause::ExecCmd(MobileObj *pMobObj, int Socket) const
// {
//   /*
//    *  Tu trzeba napisać odpowiedni kod.
//    */
//   return true;
// }

bool Interp4Pause::ExecCmd(Scene *scene, SocketClient *sock) const
{
  usleep(1000*_Timeout);
  return true;
}

bool Interp4Pause::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _Timeout;

  if(Strm_CmdsList.fail())
    return false;

  return true;
}

Interp4Command *Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}

void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause Czas[s]" << endl;
}
