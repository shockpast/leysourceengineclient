#include "../../valve/buf.h"

#include "../../leychan.h"
#include "../../vector.h"
#include "../../helpers.h"
#include "svc_bspdecal.h"

bool svc_bspdecal::Register(leychan* chan)
{
	void* voidedfn = static_cast<void*>(&svc_bspdecal::ParseMessage);

	leychan::netcallbackfn fn = static_cast<leychan::netcallbackfn>(voidedfn);

	return chan->RegisterMessageHandler(this->GetMsgType(), this, fn);
}

bool svc_bspdecal::ParseMessage(leychan* chan, svc_bspdecal* thisptr, bf_read& msg)
{
	Vector vec;
	msg.ReadBitVec3Coord(vec);

	int texture = msg.ReadUBitLong(9);
	int useentity = msg.ReadOneBit();

	int ent_index = 0;
	int modulation = 0;

	if (useentity == 1)
	{
		ent_index = msg.ReadUBitLong(MAX_EDICT_BITS);
		modulation = msg.ReadUBitLong(13);
	}

	int lowpriority = msg.ReadOneBit();

	DebugLog("Received svc_BSPDecal: pos: %f:%f:%f | tex: %i | useent: %i\n", vec.x, vec.y, vec.z, texture, useentity);

	return true;
}