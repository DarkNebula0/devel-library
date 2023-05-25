#pragma once
/// @file
/// @brief Contains logging functions and macros.

#include <string>
#include "Core/Global.h"
#include "Core/Typedef.h"

/// @namespace Devel::Logging
/// @brief The namespace encapsulating logging related classes and functions in the Devel framework.
namespace Devel::Logging {
    enum ESeverity : byte {
        None,
        Fatal,
        Error,
        Warning,
        Info,
        Debug,
        Verbose,
    };

    /// @brief Logs a message with the specified severity.
    /// @param i_sMsg The message to be logged.
    /// @param i_eSeverity The severity level of the message.
    void Initialize();

    /// @brief Inserts a new line in the log.
    void Log(const std::string &i_sMsg, ESeverity i_eSeverity = None);

    /// @brief Inserts a new line in the log.
    void NewLine();

    /// @brief Waits for the user to press the Enter key
    void WaitEnter();

    /// @brief Logs a message with severity "Debug".
    /// @param i_sMsg The message to be logged.
    /// @param i_eSeverity The severity level of the message.
    inline void LogDebug(const std::string &i_sMsg, const ESeverity i_eSeverity = None) {
#ifdef _DEBUG
        return Log("[Dbg]: " + i_sMsg, i_eSeverity);
#endif
    }
}
/// @defgroup LoggingMacros Logging Macros
/// @{

#pragma region Log Always

/// @brief Logs a message with severity "None".
#define LOG_NONE(x) Logging::Log(x, Logging::ESeverity::None)

/// @brief Logs a message with severity "Fatal".
#define LOG_FATAL(x) Logging::Log(x, Logging::ESeverity::Fatal)

/// @brief Logs a message with severity "Error".
#define LOG_ERROR(x) Logging::Log(x, Logging::ESeverity::Error)

/// @brief Logs a message with severity "Warning".
#define LOG_WARNING(x) Logging::Log(x, Logging::ESeverity::Warning)

/// @brief Logs a message with severity "Info".
#define LOG_INFO(x) Logging::Log(x, Logging::ESeverity::Info)

/// @brief Logs a message with severity "Debug".
#define LOG_DEBUG(x) Logging::Log(x, Logging::ESeverity::Debug)

/// @brief Logs a message with severity "Verbose".
#define LOG_VERBOSE(x) Logging::Log(x, Logging::ESeverity::Verbose)

/// @brief Logs a message with severity "None" if the condition is true.
#define LOG_NONE_IF(msg, cond) LOG_IF(msg, Logging::ESeverity::None, cond)

/// @brief Logs a message with severity "Fatal" if the condition is true.
#define LOG_FATAL_IF(msg, cond) LOG_IF(msg, Logging::ESeverity::Fatal, cond)

/// @brief Logs a message with severity "Error" if the condition is true.
#define LOG_ERROR_IF(msg, cond) LOG_IF(msg, Logging::ESeverity::Error, cond)

/// @brief Logs a message with severity "Warning" if the condition is true.
#define LOG_WARNING_IF(msg, cond) LOG_IF(msg, Logging::ESeverity::Warning, cond)

/// @brief Logs a message with severity "Info" if the condition is true.
#define LOG_INFO_IF(msg, cond) LOG_IF(msg, Logging::ESeverity::Info, cond)

/// @brief Logs a message with severity "Debug" if the condition is true.
#define LOG_DEBUG_IF(msg, cond) LOG_IF(msg, Logging::ESeverity::Debug, cond)

/// @brief Logs a message with severity "Verbose" if the condition is true.
#define LOG_VERBOSE_IF(msg, cond) LOG_IF(msg, Logging::ESeverity::Verbose, cond)

/// @brief Alias for LOG_NONE.
#define LOGN(x) LOG_NONE(x)

/// @brief Alias for LOG_FATAL.
#define LOGF(x) LOG_FATAL(x)

/// @brief Alias for LOG_ERROR.
#define LOGE(x) LOG_ERROR(x)

/// @brief Alias for LOG_WARNING.
#define LOGW(x) LOG_WARNING(x)

/// @brief Alias for LOG_INFO.
#define LOGI(x) LOG_INFO(x)

/// @brief Alias for LOG_DEBUG.
#define LOGD(x) LOG_DEBUG(x)

/// @brief Alias for LOG_VERBOSE.
#define LOGV(x) LOG_VERBOSE(x)

/// @brief Alias for LOG_NONE_IF.
#define LOGN_IF(msg, cond) LOG_NONE_IF(msg,cond)

/// @brief Alias for LOG_FATAL_IF.
#define LOGF_IF(msg, cond) LOG_FATAL_IF(msg,cond)

/// @brief Alias for LOG_ERROR_IF.
#define LOGE_IF(msg, cond) LOG_ERROR_IF(msg,cond)

/// @brief Alias for LOG_WARNING_IF.
#define LOGW_IF(msg, cond) LOG_WARNING_IF(msg,cond)

/// @brief Alias for LOG_INFO_IF.
#define LOGI_IF(msg, cond) LOG_INFO_IF(msg,cond)

/// @brief Alias for LOG_DEBUG_IF.
#define LOGD_IF(msg, cond) LOG_DEBUG_IF(msg,cond)

/// @brief Alias for LOG_VERBOSE_IF.
#define LOGV_IF(msg, cond) LOG_VERBOSE_IF(msg,cond)

#pragma endregion

#pragma region Log Debug

/// @brief Logs a message with severity "None" in debug mode.
#define LOG_NONE_DEBUG(x) Logging::LogDebug(x, Logging::ESeverity::None)

/// @brief Logs a message with severity "Fatal" in debug mode.
#define LOG_FATAL_DEBUG(x) Logging::LogDebug(x, Logging::ESeverity::Fatal)

/// @brief Logs a message with severity "Error" in debug mode.
#define LOG_ERROR_DEBUG(x) Logging::LogDebug(x, Logging::ESeverity::Error)

/// @brief Logs a message with severity "Warning" in debug mode.
#define LOG_WARNING_DEBUG(x) Logging::LogDebug(x, Logging::ESeverity::Warning)

/// @brief Logs a message with severity "Info" in debug mode.
#define LOG_INFO_DEBUG(x) Logging::LogDebug(x, Logging::ESeverity::Info)

/// @brief Logs a message with severity "Debug" in debug mode.
#define LOG_DEBUG_DEBUG(x) Logging::LogDebug(x, Logging::ESeverity::Debug)

/// @brief Logs a message with severity "Verbose" in debug mode.
#define LOG_VERBOSE_DEBUG(x) Logging::LogDebug(x, Logging::ESeverity::Verbose)

/// @brief Logs a message with severity "None" in debug mode if the condition is true.
#define LOG_NONE_IF_DEBUG(msg, cond) LOG_IF_DEBUG(msg, Logging::ESeverity::None, cond)

/// @brief Logs a message with severity "Fatal" in debug mode if the condition is true.
#define LOG_FATAL_IF_DEBUG(msg, cond) LOG_IF_DEBUG(msg, Logging::ESeverity::Fatal, cond)

/// @brief Logs a message with severity "Error" in debug mode if the condition is true.
#define LOG_ERROR_IF_DEBUG(msg, cond) LOG_IF_DEBUG(msg, Logging::ESeverity::Error, cond)

/// @brief Logs a message with severity "Warning" in debug mode if the condition is true.
#define LOG_WARNING_IF_DEBUG(msg, cond) LOG_IF_DEBUG(msg, Logging::ESeverity::Warning, cond)

/// @brief Logs a message with severity "Info" in debug mode if the condition is true.
#define LOG_INFO_IF_DEBUG(msg, cond) LOG_IF_DEBUG(msg, Logging::ESeverity::Info, cond)

/// @brief Logs a message with severity "Debug" in debug mode if the condition is true.
#define LOG_DEBUG_IF_DEBUG(msg, cond) LOG_IF_DEBUG(msg, Logging::ESeverity::Debug, cond)

/// @brief Logs a message with severity "Verbose" in debug mode if the condition is true.
#define LOG_VERBOSE_IF_DEBUG(msg, cond) LOG_IF_DEBUG(msg, Logging::ESeverity::Verbose, cond)

/// @brief Alias for LOG_NONE_DEBUG.
#define LOGN_DEBUG(x) LOG_NONE_DEBUG(x)

/// @brief Alias for LOG_FATAL_DEBUG.
#define LOGF_DEBUG(x) LOG_FATAL_DEBUG(x)

/// @brief Alias for LOG_ERROR_DEBUG.
#define LOGE_DEBUG(x) LOG_ERROR_DEBUG(x)

/// @brief Alias for LOG_WARNING_DEBUG.
#define LOGW_DEBUG(x) LOG_WARNING_DEBUG(x)

/// @brief Alias for LOG_INFO_DEBUG.
#define LOGI_DEBUG(x) LOG_INFO_DEBUG(x)

/// @brief Alias for LOG_DEBUG_DEBUG.
#define LOGD_DEBUG(x) LOG_DEBUG_DEBUG(x)

/// @brief Alias for LOG_VERBOSE_DEBUG.
#define LOGV_DEBUG(x) LOG_VERBOSE_DEBUG(x)

/// @brief Alias for LOG_NONE_IF_DEBUG.
#define LOGN_IF_DEBUG(msg, cond) LOG_NONE_IF_DEBUG(msg,cond)

/// @brief Alias for LOG_FATAL_IF_DEBUG.
#define LOGF_IF_DEBUG(msg, cond) LOG_FATAL_IF_DEBUG(msg,cond)

/// @brief Alias for LOG_ERROR_IF_DEBUG.
#define LOGE_IF_DEBUG(msg, cond) LOG_ERROR_IF_DEBUG(msg,cond)

/// @brief Alias for LOG_WARNING_IF_DEBUG.
#define LOGW_IF_DEBUG(msg, cond) LOG_WARNING_IF_DEBUG(msg,cond)

/// @brief Alias for LOG_INFO_IF_DEBUG.
#define LOGI_IF_DEBUG(msg, cond) LOG_INFO_IF_DEBUG(msg,cond)

/// @brief Alias for LOG_DEBUG_IF_DEBUG.
#define LOGD_IF_DEBUG(msg, cond) LOG_DEBUG_IF_DEBUG(msg,cond)

/// @brief Alias for LOG_VERBOSE_IF_DEBUG.
#define LOGV_IF_DEBUG(msg, cond) LOG_VERBOSE_IF_DEBUG(msg,cond)

/// @}
#pragma endregion
