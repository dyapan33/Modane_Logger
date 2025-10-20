// This file is part of the Modane Logger Project and can be found at github.com/dyapan33/Modane_Logger/
#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
#include <chrono>



namespace Logging {

    enum class Level {
        Info,
        Debug,
        Trace,
        Warning,
        Error,
        Critical
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

        // --- Logger Functions ---

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
        void Error(const char* Message, const Args&... args) {
            PrintAndSave(Level::Error, Message, args...);
        }

        template<typename... Args>
        void Critical(const char* Message, const Args&... args) {
            PrintAndSave(Level::Critical, Message, args...);
        }

    private:
        // --- Private Member Variables ---
        bool m_IsInitialized;
        bool m_IsDebugEnabled;
        bool m_IsTraceEnabled;
        bool m_IsSaveLogEnabled;

        std::string m_Directory;
        std::ofstream m_LogFileStream;

        void AddPigment(Level L);

        // --- Private Utility Function ---
        template<typename... Args>
        void PrintAndSave(Level Level, const char* Message, const Args&... args) {
            // Check if the logger has been initialized
            if (!m_IsInitialized) {
                std::cout << "Please initialize the logger first!" << std::endl;
                return;
            }
            
            // Get the current timestamp using C++ chrono
            auto Now = std::chrono::system_clock::now();
            auto InTime_t = std::chrono::system_clock::to_time_t(Now);
            std::tm LocalTime = *std::localtime(&InTime_t);
            
            std::ostringstream LogMessageStream;
            LogMessageStream << std::put_time(&LocalTime, "%Y-%m-%d %H:%M:%S");

            const char* LevelString;
            switch (Level) {
                case Level::Info:       LevelString = "[INFO]"; break; // Blue
                case Level::Debug:      LevelString = "[DEBUG]"; break; // Cyan
                case Level::Trace:      LevelString = "[TRACE]"; break; // Bright Grey
                case Level::Warning:    LevelString = "[WARNING]"; break; // Yellow
                case Level::Error:      LevelString = "[ERROR]"; break; // Red
                case Level::Critical:   LevelString = "[CRITICAL]"; break; // Bold Red
                default:                LevelString = "[LOG]"; break; // White
            }

            AddPigment(Level); // Adds the pigment to the console

            LogMessageStream << " " << LevelString << ": " << Message; // Adds the LevelString (e.g. Info and then a colon (format: [TIME] [LEVELSTRING]:))

            // Use a fold expression to unpack and stream each argument
            ((LogMessageStream << " " << args), ...); // Print out the arguments

            std::string LogMessage = LogMessageStream.str(); // Change above to a string

            // Console Output
            std::cout << LogMessage << "\x1b[0m" << std::endl; // Prints out message

            // File Output
            if (m_IsSaveLogEnabled && m_LogFileStream.is_open()) {
                m_LogFileStream << LogMessage << std::endl;
                m_LogFileStream.flush(); // Force write to disk
            }
        }
    };
}


