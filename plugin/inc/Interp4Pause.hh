#pragma once

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "Interp4Command.hh"

class Interp4Pause : public Interp4Command
{
private:
  int _Timeout;

public:
  Interp4Pause();

  virtual void PrintCmd() const;

  virtual void PrintSyntax() const;

  virtual const char *GetCmdName() const;

  // virtual bool ExecCmd(MobileObj *pMobObj, int Socket) const;

  virtual bool ExecCmd(Scene *scene, SocketClient *sock) const;

  virtual bool ReadParams(std::istream &Strm_CmdsList);

  virtual void PrintParams() {}

  static Interp4Command *CreateCmd();
};
