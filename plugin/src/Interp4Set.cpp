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

Interp4Set::Interp4Set() : Interp4Command(""), _X(0), _Y(0), _RotZ(0)
{
}

void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " << _ObjName << " " << _X << " " << _Y << " " << _RotZ << endl;
}

const char *Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

// bool Interp4Set::ExecCmd(MobileObj *pMobObj, int Socket) const
// {
//   /*
//    *  Tu trzeba napisać odpowiedni kod.
//    */
//   return true;
// }

bool Interp4Set::ExecCmd(Scene *scene, SocketClient *sock) const
{
  std::shared_ptr<MobileObj> obj = scene->FindMobileObj(_ObjName.c_str());
  Vector3D targetPos;
  targetPos[0] = _X;
  targetPos[1] = _Y;

  obj->LockAccess();
  obj->UsePosition_m() = targetPos;
  obj->SetAng_Yaw_deg(_RotZ);
  obj->UnlockAccess();

  std::stringstream cmd_str;
  cmd_str << "UpdateObj Name=" << obj->GetName();
  cmd_str << " Trans_m=" << obj->UsePosition_m();
  cmd_str << " RotXYZ_deg=(0,0," << obj->GetAng_Yaw_deg() << ")\n";
  sock->LockAccess();
  sock->Send(cmd_str.str().c_str());
  sock->UnlockAccess();
  usleep(1000);

  return true;
}

bool Interp4Set::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _ObjName;
  Strm_CmdsList >> _X;
  Strm_CmdsList >> _Y;
  Strm_CmdsList >> _RotZ;

  if (Strm_CmdsList.fail())
    return false;

  return true;
}

Interp4Command *Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

void Interp4Set::PrintSyntax() const
{
  cout << "   Set X[mm] Y[mm] RotZ[rad]" << endl;
}