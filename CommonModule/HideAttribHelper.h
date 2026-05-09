// HideAttribHelper.h - Equipment hide attribute encoding
// Packs 1-4 hidden attributes (type+value) into a uint32 field.
// Layout:
//   bits 0-3   : total count (AllAttribCount)
//   bits 4-7   : active count (ActiveAttribCount)
//   bits 8-15  : slot 0 (type:4, value:4)
//   bits 16-23 : slot 1
//   bits 24-31 : slot 2
#pragma once
#ifndef _INC_HIDEATTRIBHELPER_
#define _INC_HIDEATTRIBHELPER_

enum HideAttribType
{
    HideAttrib_None        = 0,
    HideAttrib_AC          = 1,
    HideAttrib_MAC         = 2,
    HideAttrib_DC          = 3,
    HideAttrib_MC          = 4,
    HideAttrib_SC          = 5,
    HideAttrib_MagicDrop   = 6,
    HideAttrib_MainAttrib  = 7,
    HideAttrib_Lucky       = 8,
    HideAttrib_DcHide      = 9,
    HideAttrib_MagicHide   = 10,
};

class HideAttribHelper
{
public:
    static int  GetAllAttribCount(unsigned int _uCode);
    static int  GetActiveAttribCount(unsigned int _uCode);
    static int  GetActiveAttribType(int _i, unsigned int _uCode);
    static int  GetActiveAttribValue(int _i, unsigned int _uCode);

    static void SetAllAttribCount(unsigned int& _uCode, int _v);
    static void SetActiveAttribCount(unsigned int& _uCode, int _v);
    static void SetActiveAttribType(unsigned int& _uCode, int _i, int _type);
    static void SetActiveAttribValue(unsigned int& _uCode, int _i, int _value);
};

// Get string name for hide attribute type
inline const char* GetHideAttribString(HideAttribType _eType)
{
    switch(_eType)
    {
    case HideAttrib_AC:         return "AC";
    case HideAttrib_MAC:        return "MAC";
    case HideAttrib_DC:         return "DC";
    case HideAttrib_MC:         return "MC";
    case HideAttrib_SC:         return "SC";
    case HideAttrib_MagicDrop:  return "MagicDrop";
    case HideAttrib_MainAttrib: return "MainAttrib";
    case HideAttrib_Lucky:      return "Lucky";
    case HideAttrib_DcHide:     return "DcHide";
    case HideAttrib_MagicHide:  return "MagicHide";
    default:                    return "Unknown";
    }
}

#endif // _INC_HIDEATTRIBHELPER_
