#pragma once

#include "interface/base.hpp"

namespace xrep {
namespace interface {

template<class MessageType>
/**
 * @brief The interface of the logging classes, the functionality of these
 *        classes is limited to logging and the main function to be applied in
 *        the work is the function log.
 */
class LoggerInterface : Interface {
public:
    LoggerInterface() = default;
    ~LoggerInterface() = default;

    /**
     * @brief Function for transmitting a log message. The message will be
     *        transmitted according to the implementation.
     * @param message The message that will be transmitted.
     */
    virtual void log(const MessageType& message) const noexcept = 0;
};

}
}
