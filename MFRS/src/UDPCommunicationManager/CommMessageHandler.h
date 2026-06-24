#pragma once

#include <cstdint>
#include <map>
#include <nFramework/util/util.h>

class CommMessageHandler
{
public:
    CommMessageHandler();
    ~CommMessageHandler();

    tstring getMsgName(std::uint32_t msgID) const;

    void setIDNameTable(
        std::uint32_t msgID,
        const tstring& msgName);

private:
    void initialize();
    void release();

private:
    std::map<std::uint32_t, tstring> idNameTable;
};