#include "../../valve/buf.h"

#include "../../leychan.h"
#include "../../helpers.h"
#include "svc_classinfo.h"

bool svc_classinfo::Register(leychan* chan)
{
	void* voidedfn = static_cast<void*>(&svc_classinfo::ParseMessage);

	leychan::netcallbackfn fn = static_cast<leychan::netcallbackfn>(voidedfn);

	return chan->RegisterMessageHandler(this->GetMsgType(), this, fn);
}

bool svc_classinfo::ParseMessage(leychan* chan, svc_classinfo* thisptr, bf_read& msg)
{
	int classes = msg.ReadShort();
	int useclientclasses = msg.ReadOneBit();

	unsigned int size = (int)(log2(classes) + 1);


	if (useclientclasses == 0)
	{
		DebugLog("Received svc_ClassInfo | classes: %i: \n", classes);

		for (int i = 0; i < classes; i++)
		{
			int classid = msg.ReadUBitLong(size);

			char classname[255];
			char dtname[255];

			msg.ReadString(classname, sizeof(classname));
			msg.ReadString(dtname, sizeof(dtname));

			if (msg.IsOverflowed())
				return false;

			DebugLog("Classname: %s | DTname: %s | ClassID: %i\n", classname, dtname, classid);
		}

		DebugLog("svc_ClassInfo end\n");
	}
	else {
		DebugLog("Received svc_ClassInfo, classes: %i\n", classes);
	}

	return true;
}