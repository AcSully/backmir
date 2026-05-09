// ZipDataReader.h - Zip file reader
#pragma once
#ifndef _INC_ZIPDATAREADER_
#define _INC_ZIPDATAREADER_

#include <string>
#include <vector>

class ZipDataReader
{
public:
    ZipDataReader();
    ~ZipDataReader();

    bool Open(const std::string& _zipPath);
    void Close();

    bool IsOpen() const { return m_pZip != 0; }

    bool ReadEntry(const std::string& _entryName, std::vector<char>& _out) const;
    bool ListEntries(std::vector<std::string>& _out) const;

private:
    ZipDataReader(const ZipDataReader&);
    ZipDataReader& operator=(const ZipDataReader&);

    void* m_pZip;
};

#endif // _INC_ZIPDATAREADER_
