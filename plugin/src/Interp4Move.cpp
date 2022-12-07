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

Interp4Move::Interp4Move() : Interp4Command(""), _Speed_mmS(0), _Distance_m(0)
{
}

void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _ObjName << " " << _Speed_mmS << " " << _Distance_m << endl;
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
  double direction = _Distance_m < 0 ? -1 : 1;

  for (double step = fabs(_Distance_m); step > 0; step -= 0.1)
  {
    Vector3D stepShift;
    obj->LockAccess();
    stepShift[0] = 0.1 * cos(direction * obj->GetAng_Yaw_deg() * M_PI / 180.0f );
    stepShift[1] = 0.1 * sin(direction * obj->GetAng_Yaw_deg() * M_PI / 180.0f );
    obj->UsePosition_m() += stepShift;
    obj->UnlockAccess();

    std::stringstream cmd_str;
    cmd_str << "UpdateObj Name=" << obj->GetName();
    cmd_str << " Trans_m=" << obj->UsePosition_m() << "\n";
    sock->LockAccess();
    sock->Send(cmd_str.str().c_str());
    sock->UnlockAccess();
    usleep(1000000 / _Speed_mmS);
  }

  return true;
}

bool Interp4Move::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _ObjName;
  Strm_CmdsList >> _Speed_mmS;
  Strm_CmdsList >> _Distance_m;

  if (Strm_CmdsList.fail())
    return false;

  return true;
}

Interp4Command *Interp4Move::CreateCmd()
{
  return new Interp4Move();
}

void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[mm/s]  DlugoscDrogi[m]" << endl;
}
