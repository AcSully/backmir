// [reconstructed] ÖØ½¨ÓÚ 2026-05-06
#include "ProtoType.h"

static ProtoType s_eProtoType = ProtoType_ByteBuffer;

ProtoType GetProtoType()
{
    return s_eProtoType;
}

void SetProtoType(ProtoType _eType)
{
    s_eProtoType = _eType;
}
