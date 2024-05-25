#include "../../valve/buf.h"

#include "../../leychan.h"
#include "net_tick.h"
#include "../../helpers.h"

bool net_tick::Register(leychan* chan)
{
	void* voidedfn = static_cast<void*>(&net_tick::ParseMessage);

	leychan::netcallbackfn fn = static_cast<leychan::netcallbackfn>(voidedfn);

	return chan->RegisterMessageHandler(this->GetMsgType(), this, fn);
}

bool net_tick::ParseMessage(leychan* chan, net_tick* thisptr, bf_read& msg)
{
	chan->tickData.net_tick = msg.ReadLong();
	chan->tickData.net_hostframetime = msg.ReadUBitLong(16);
	chan->tickData.net_hostframedeviation = msg.ReadUBitLong(16);

	return true;
}