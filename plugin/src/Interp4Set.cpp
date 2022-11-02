#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Set"; }
}

Interp4Command *CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

Interp4Set::Interp4Set() : x(0), y(0)
{
}

void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " << x << " " << y << endl;
}

const char *Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

bool Interp4Set::ExecCmd(MobileObj *pMobObj, int Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

bool Interp4Set::ReadParams(std::istream &Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

Interp4Command *Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

void Interp4Set::PrintSyntax() const
{
  cout << "   Rotate X[m] Y[m]" << endl;
}