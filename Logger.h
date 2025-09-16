// This file is part of the Modane_Logger Project and is licensed under BSD3, to find out more head to https://github.com/dyapan33/Modane_Logger/
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

        void Info(const char* Message, ...);
        void Debug(const char* Message, ...);
        void Trace(const char* Message, ...);
        void Warning(const char* Message, ...);
        void Critical(const char* Message, ...);
        void Error(const char* Message, ...);

    private:
        // --- Private Member Variables ---
        bool m_IsInitialized;
        bool m_IsDebugEnabled;
        bool m_IsTraceEnabled;
        bool m_IsSaveLogEnabled;

        std::string m_Directory;
        std::ofstream m_LogFileStream;

        // --- Private Utility Function ---
        void PrintAndSave(Level Level, const char* Message, ...);
    };
}


