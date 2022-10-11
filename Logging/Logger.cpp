#include "Logger.h"
#include "Core/Global.h"
#include "Core/Typedef.h"
#include "Threading/Mutex/Mutex.h"

#include <iostream>
#include <ctime>
#include <rang.hpp>

namespace Devel::Logging
{
    Devel::Threading::CMutex g_oMutex;

    std::string DateTime()
    {
        time_t nNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        char buf[80];
        tm grT{};
#ifdef _WIN32
        localtime_s(&grT, &nNow);
#else
        grT = *std::localtime(&nNow);
#endif
        strftime(buf, sizeof(buf), "%A %d %R", &grT);
        return buf;
    }

    void Output(const std::string &i_sWhat, const rang::fg i_eColor)
    {
        Logging::g_oMutex.lock();
        std::cout << i_eColor << i_sWhat << rang::fg::reset << std::endl ;
        Logging::g_oMutex.unlock();
    }
}

// Initialize logger=======================================
void Devel::Logging::Initialize()
{

    rang::setControlMode(rang::control::Auto);
    rang::setWinTermMode(rang::winTerm::Auto);
}

// Log=====================================================
void Devel::Logging::Log(const std::string &i_sMsg, ESeverity i_eSeverity)
{
    // Set string time
    std::string stOut("[" + DateTime() + "] ");

    rang::fg eColor = rang::fg::reset;

    switch (i_eSeverity)
    {
        case Fatal:
            stOut += "[Fatal]: ";
            eColor = rang::fg::red;
            break;
        case Error:
            stOut += "[Error]: ";
            eColor = rang::fg::red;;
            break;
        case Warning:
            stOut += "[Warning]: ";
            eColor = rang::fg::yellow;
            break;
        case Info:
            stOut += "[Info]: ";
            eColor = rang::fg::cyan;
            break;
        case Debug:
            stOut += "[Debug]: ";
            eColor = rang::fg::magenta;
            break;
        case Verbose:
            stOut += "[Verbose]: ";
            eColor = rang::fg::green;
            break;
        case None:
            break;
    }

    stOut += i_sMsg;

    Output(stOut, eColor);
}

// New Line=====================================================
void Devel::Logging::NewLine()
{
    Output("", rang::fg::reset);
}

// Cin Get===================================================
void Devel::Logging::WaitEnter()
{
    std::cin.get();
}