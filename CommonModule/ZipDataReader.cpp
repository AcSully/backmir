// ZipDataReader.cpp - Zip file reader (stub implementation)
// The original uses libzip which is not available in the VS2013 build environment.
// This stub provides the interface but returns empty results.
#include "ZipDataReader.h"
#include <cstring>

ZipDataReader::ZipDataReader() : m_pZip(0) {}
ZipDataReader::~ZipDataReader() { Close(); }

bool ZipDataReader::Open(const std::string& /*_zipPath*/)
{
    // Stub: libzip not available
    return false;
}

void ZipDataReader::Close()
{
    m_pZip = 0;
}

bool ZipDataReader::ReadEntry(const std::string& /*_entryName*/, std::vector<char>& /*_out*/) const
{
    return false;
}

bool ZipDataReader::ListEntries(std::vector<std::string>& /*_out*/) const
{
    return false;
}
