// This file is part of the Modane Logger Project and can be found at github.com/dyapan33/Modane_Logger/
#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

namespace Logging {

    enum class Level {
        Info,
        Debug,
        Trace,
        Warning,
        Critical,
        Error
    };

    class Logger {
    public:
        // --- Constructor and Destructor ---
        Logger();
        ~Logger();

        // --- Public Member Functions ---
        void Init(bool DebugEnabled, bool TraceEnabled, bool SaveLog);
        void Save(const char* File);
        void ClearLogFile(const char* File);

        template<typename... Args>
        void Info(const char* Message, const Args&... args) {
            PrintAndSave(Level::Info, Message, args...);
        }

        template<typename... Args>
        void Debug(const char* Message, const Args&... args) {
            if (m_IsDebugEnabled) {
                PrintAndSave(Level::Debug, Message, args...);
            }
        }

        template<typename... Args>
        void Trace(const char* Message, const Args&... args) {
            if (m_IsTraceEnabled) {
                PrintAndSave(Level::Trace, Message, args...);
            }
        }

        template<typename... Args>
        void Warning(const char* Message, const Args&... args) {
            PrintAndSave(Level::Warning, Message, args...);
        }

        template<typename... Args>
        void Critical(const char* Message, const Args&... args) {
            PrintAndSave(Level::Critical, Message, args...);
        }

        template<typename... Args>
        void Error(const char* Message, const Args&... args) {
            PrintAndSave(Level::Error, Message, args...);
        }

    private:
        // --- Private Member Variables ---
        bool m_IsInitialized;
        bool m_IsDebugEnabled;
        bool m_IsTraceEnabled;
        bool m_IsSaveLogEnabled;

        std::string m_Directory;
        std::ofstream m_LogFileStream;

        // --- Private Utility Function ---
        template<typename... Args>
        void PrintAndSave(Level Level, const char* Message, const Args&... args);
    };
}


