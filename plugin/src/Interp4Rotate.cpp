#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Rotate"; }
}

Interp4Command *CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}

Interp4Rotate::Interp4Rotate() : Interp4Command(""), _RotSpeed(0), _Angle(0)
{
}

void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() << " " << _ObjName << " " << _RotSpeed << " " << _Angle << endl;
}

const char *Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}

// bool Interp4Rotate::ExecCmd(MobileObj *pMobObj, int Socket) const
// {
//   /*
//    *  Tu trzeba napisać odpowiedni kod.
//    */
//   return true;
// }

bool Interp4Rotate::ExecCmd(Scene *scene, SocketClient *sock) const
{
  std::shared_ptr<MobileObj> obj = scene->FindMobileObj(_ObjName.c_str());
  double direction = _Angle < 0 ? -1 : 1;

  for (double step = _Angle; step > 0; step -= 1)
  {
    obj->LockAccess();
    obj->SetAng_Yaw_deg(obj->GetAng_Yaw_deg()+direction);
    obj->UnlockAccess();

    std::stringstream cmd_str;
    cmd_str << "UpdateObj Name=" << obj->GetName();
    cmd_str << " RotXYZ_deg=(0,0," << obj->GetAng_Yaw_deg() << ")\n";
    sock->LockAccess();
    sock->Send(cmd_str.str().c_str());
    sock->UnlockAccess();
    usleep(1000000 / _RotSpeed);
  }
  return true;
}

bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _ObjName;
  Strm_CmdsList >> _RotSpeed;
  Strm_CmdsList >> _Angle;

  if(Strm_CmdsList.fail())
    return false;

  return true;
}

Interp4Command *Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}

void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate Szybkosc_katowa[rad/s] Kat_skretu[rad]" << endl;
}