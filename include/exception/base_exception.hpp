#pragma once

#include <exception>
#include <cstring>

namespace xrep::exception {

/**
 * @brief The xReplacerException is a base class for all exceptions used in the
 *        application
 */
class xReplacerException : public std::exception {
public:
    xReplacerException() = default;
    virtual ~xReplacerException() = default;

    /**
     * @brief what
     * @return
     */
    virtual const char* what() const noexcept = 0;
};

//------------------------------------------------------------------------------
/**
 * @brief The non_FatalException is a base class for exceptions that do not
 *        require program termination.
 */
class non_FatalException : public xReplacerException {
public:
    non_FatalException() = default;
    virtual ~non_FatalException() = default;

    /**
     * @brief what
     * @return
     */
    virtual const char* what() const noexcept = 0;
};

//------------------------------------------------------------------------------
/**
 * @brief The FatalException is a base class for exceptions that require program
 *        termination.
 */
class FatalException : public xReplacerException {
public:
    FatalException() = default;
    virtual ~FatalException() = default;

    /**
     * @brief what
     * @return
     */
    virtual const char* what() const noexcept = 0;
};

} // namespace xrep::exception
