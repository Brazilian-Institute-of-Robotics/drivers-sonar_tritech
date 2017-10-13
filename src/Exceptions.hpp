#ifndef _SEANET_MotorLostSyncException_H_
#define _SEANET_MotorLostSyncException_H_

#include <string>
#include <stdexcept>
#include <exception>

namespace sea_net
{

struct MotorLostSyncException : std::runtime_error
{
    explicit MotorLostSyncException(std::string const& desc)
        : std::runtime_error(desc) {}
};

}

#endif
