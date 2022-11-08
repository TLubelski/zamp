#pragma once

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "Interp4Command.hh"

class Interp4Rotate : public Interp4Command
{
private:
  std::string _ObjName;
  int _RotSpeed;
  int _Angle;

public:
  Interp4Rotate();

  virtual void PrintCmd() const;

  virtual void PrintSyntax() const;

  virtual const char *GetCmdName() const;

  virtual bool ExecCmd(MobileObj *pMobObj, int Socket) const;

  virtual bool ReadParams(std::istream &Strm_CmdsList);

  virtual void PrintParams() {}

  static Interp4Command *CreateCmd();
};
