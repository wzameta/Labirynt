#include "myexceptions.h"




MyExceptions::OutOfBounds::OutOfBounds()
    : _message("Index out of bounds")
{
}


MyExceptions::OutOfBounds::OutOfBounds(const std::string& message)
    : _message(message)
{
}


const char* MyExceptions::OutOfBounds::what() const noexcept
{
    return _message.c_str();
}



MyExceptions::InvalidArgument::InvalidArgument()
    : _message("Invalid argument")
{
}


MyExceptions::InvalidArgument::InvalidArgument(const std::string& message)
    : _message(message)
{
}


const char* MyExceptions::InvalidArgument::what() const noexcept
{
    return _message.c_str();
}



MyExceptions::NoPath::NoPath()
    : _message("No path found in maze")
{
}


MyExceptions::NoPath::NoPath(const std::string& message)
    : _message(message)
{
}


const char* MyExceptions::NoPath::what() const noexcept
{
    return _message.c_str();
}
