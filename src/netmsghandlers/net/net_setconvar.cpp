#include "../../valve/buf.h"

#include "../../leychan.h"
#include "../../helpers.h"
#include "net_setconvar.h"

bool net_setconvar::Register(leychan* chan)
{
	void* voidedfn = static_cast<void*>(&net_setconvar::ParseMessage);

	leychan::netcallbackfn fn = static_cast<leychan::netcallbackfn>(voidedfn);

	return chan->RegisterMessageHandler(this->GetMsgType(), this, fn);
}

bool net_setconvar::ParseMessage(leychan* chan, net_setconvar* thisptr, bf_read& msg)
{
	int count = msg.ReadByte();

	char cmdname[255];
	char cmdval[255];

	for (int i = 0; i < count; i++)
	{
		msg.ReadString(cmdname, sizeof(cmdname));
		msg.ReadString(cmdval, sizeof(cmdval));
		
		Log("net_SetConVar: %s -> %s\n", cmdname, cmdval);
	}

	return true;
}