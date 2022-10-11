#pragma once

#include <exception>

#define CreateFastException(Name, ErrorMessage)     class Name : public std::exception                      \
                                                    {                                                       \
                                                    public:                                                 \
                                                        const char *what() const throw()                    \
                                                        {                                                   \
                                                            return ErrorMessage;                            \
                                                        }                                                   \
                                                    };

namespace Devel {
    CreateFastException(CIndexOutOfRangeException, "Index is out of range!");
}