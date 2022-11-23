#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Move"; }
}


Interp4Command *CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


Interp4Move::Interp4Move() : Interp4Command(""), _Speed_mS(0), _Distance_m(0)
{
}


void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _ObjName << " " << _Speed_mS << " " << _Distance_m << endl;
}


const char *Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


// bool Interp4Move::ExecCmd(MobileObj *pMobObj, int Socket) const
// {
//   /*
//    *  Tu trzeba napisać odpowiedni kod.
//    */
//   return true;
// }

bool Interp4Move::ExecCmd(Scene *scene, SocketClient *sock) const
{
  std::shared_ptr<MobileObj> obj = scene->FindMobileObj(_ObjName.c_str());

  obj->UsePosition_m()
  
  
  return true;
}



bool Interp4Move::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _ObjName;
  Strm_CmdsList >> _Speed_mS;
  Strm_CmdsList >> _Distance_m;

  return true;
}


Interp4Command *Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
