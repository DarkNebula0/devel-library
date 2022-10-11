#pragma once
#include <string>
#include "Core/Global.h"
#include "Core/Typedef.h"

namespace Devel::Logging
{
    enum ESeverity : byte
    {
        None,
        Fatal,
        Error,
        Warning,
        Info,
        Debug,
        Verbose,
    };

    void Initialize();
    void Log(const std::string &i_sMsg, ESeverity i_eSeverity = None);

    void NewLine();
    void WaitEnter();

    __inline void LogDebug(const std::string &i_sMsg, const ESeverity i_eSeverity = None)
    {
#ifdef _DEBUG
        return Log("[Dbg]: " + i_sMsg, i_eSeverity);
#endif
    }
}

#pragma region Log Always
#define LOG_IF(msg,severity,cond)	if (cond) Logging::Log(msg, severity)

#define LOG_NONE(x)		Logging::Log(x, Logging::ESeverity::None)
#define LOG_FATAL(x)	Logging::Log(x, Logging::ESeverity::Fatal)
#define LOG_ERROR(x)	Logging::Log(x, Logging::ESeverity::Error)
#define LOG_WARNING(x)	Logging::Log(x, Logging::ESeverity::Warning)
#define LOG_INFO(x)		Logging::Log(x, Logging::ESeverity::Info)
#define LOG_DEBUG(x)	Logging::Log(x, Logging::ESeverity::Debug)
#define LOG_VERBOSE(x)	Logging::Log(x, Logging::ESeverity::Verbose)

#define LOG_NONE_IF(msg,cond)		LOG_IF(msg,Logging::ESeverity::None,cond)
#define LOG_FATAL_IF(msg,cond)		LOG_IF(msg,Logging::ESeverity::Fatal,cond)
#define LOG_ERROR_IF(msg,cond)		LOG_IF(msg,Logging::ESeverity::Error,cond)
#define LOG_WARNING_IF(msg,cond)	LOG_IF(msg,Logging::ESeverity::Warning,cond)
#define LOG_INFO_IF(msg,cond)		LOG_IF(msg,Logging::ESeverity::Info,cond)
#define LOG_DEBUG_IF(msg,cond)		LOG_IF(msg,Logging::ESeverity::Debug,cond)
#define LOG_VERBOSE_IF(msg,cond)	LOG_IF(msg,Logging::ESeverity::Verbose,cond)

#define LOGN(x) LOG_NONE(x)
#define LOGF(x) LOG_FATAL(x)
#define LOGE(x) LOG_ERROR(x)
#define LOGW(x) LOG_WARNING(x)
#define LOGI(x) LOG_INFO(x)
#define LOGD(x) LOG_DEBUG(x)
#define LOGV(x) LOG_VERBOSE(x)

#define LOGN_IF(msg,cond) LOG_NONE_IF(msg,cond)
#define LOGF_IF(msg,cond) LOG_FATAL_IF(msg,cond)
#define LOGE_IF(msg,cond) LOG_ERROR_IF(msg,cond)
#define LOGW_IF(msg,cond) LOG_WARNING_IF(msg,cond)
#define LOGI_IF(msg,cond) LOG_INFO_IF(msg,cond)
#define LOGD_IF(msg,cond) LOG_DEBUG_IF(msg,cond)
#define LOGV_IF(msg,cond) LOG_VERBOSE_IF(msg,cond)
#pragma endregion

#pragma region Log Debug
#define LOG_IF_DEBUG(msg,severity,cond)	if (cond) Logging::LogDebug(msg, severity)

#define LOG_NONE_DEBUG(x)		Logging::LogDebug(x, Logging::ESeverity::None)
#define LOG_FATAL_DEBUG(x)		Logging::LogDebug(x, Logging::ESeverity::Fatal)
#define LOG_ERROR_DEBUG(x)		Logging::LogDebug(x, Logging::ESeverity::Error)
#define LOG_WARNING_DEBUG(x)	Logging::LogDebug(x, Logging::ESeverity::Warning)
#define LOG_INFO_DEBUG(x)		Logging::LogDebug(x, Logging::ESeverity::Info)
#define LOG_DEBUG_DEBUG(x)		Logging::LogDebug(x, Logging::ESeverity::Debug)
#define LOG_VERBOSE_DEBUG(x)	Logging::LogDebug(x, Logging::ESeverity::Verbose)

#define LOG_NONE_IF_DEBUG(msg,cond)			LOG_IF_DEBUG(msg,Logging::ESeverity::None,cond)
#define LOG_FATAL_IF_DEBUG(msg,cond)		LOG_IF_DEBUG(msg,Logging::ESeverity::Fatal,cond)
#define LOG_ERROR_IF_DEBUG(msg,cond)		LOG_IF_DEBUG(msg,Logging::ESeverity::Error,cond)
#define LOG_WARNING_IF_DEBUG(msg,cond)		LOG_IF_DEBUG(msg,Logging::ESeverity::Warning,cond)
#define LOG_INFO_IF_DEBUG(msg,cond)			LOG_IF_DEBUG(msg,Logging::ESeverity::Info,cond)
#define LOG_DEBUG_IF_DEBUG(msg,cond)		LOG_IF_DEBUG(msg,Logging::ESeverity::Debug,cond)
#define LOG_VERBOSE_IF_DEBUG(msg,cond)		LOG_IF_DEBUG(msg,Logging::ESeverity::Verbose,cond)

#define LOGN_DEBUG(x) LOG_NONE_DEBUG(x)
#define LOGF_DEBUG(x) LOG_FATAL_DEBUG(x)
#define LOGE_DEBUG(x) LOG_ERROR_DEBUG(x)
#define LOGW_DEBUG(x) LOG_WARNING_DEBUG(x)
#define LOGI_DEBUG(x) LOG_INFO_DEBUG(x)
#define LOGD_DEBUG(x) LOG_DEBUG_DEBUG(x)
#define LOGV_DEBUG(x) LOG_VERBOSE_DEBUG(x)

#define LOGN_IF_DEBUG(msg,cond) LOG_NONE_IF_DEBUG(msg,cond)
#define LOGF_IF_DEBUG(msg,cond) LOG_FATAL_IF_DEBUG(msg,cond)
#define LOGE_IF_DEBUG(msg,cond) LOG_ERROR_IF_DEBUG(msg,cond)
#define LOGW_IF_DEBUG(msg,cond) LOG_WARNING_IF_DEBUG(msg,cond)
#define LOGI_IF_DEBUG(msg,cond) LOG_INFO_IF_DEBUG(msg,cond)
#define LOGD_IF_DEBUG(msg,cond) LOG_DEBUG_IF_DEBUG(msg,cond)
#define LOGV_IF_DEBUG(msg,cond) LOG_VERBOSE_IF_DEBUG(msg,cond)
#pragma endregion
