#include "Logger.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace Logging {

    // --- Constructor and Destructor ---
    Logger::Logger() {
        // Constructor to initialize member variables
        m_IsInitialized = false;
        m_IsDebugEnabled = false;
        m_IsTraceEnabled = false;
        m_IsSaveLogEnabled = false;
    }

    Logger::~Logger() {
        // Close the log file when the logger object is destroyed
        if (m_LogFileStream.is_open()) {
            m_LogFileStream.close();
        }
    }

    // --- Init Function ---
    void Logger::Init(bool DebugEnabled, bool TraceEnabled, bool SaveLog) {
        m_IsDebugEnabled = DebugEnabled;
        m_IsTraceEnabled = TraceEnabled;
        m_IsSaveLogEnabled = SaveLog;
        m_IsInitialized = true;
    }

    // --- Save Function ---
    void Logger::Save(const char* File) {
        if (m_IsSaveLogEnabled) {
            m_Directory = File;
            m_LogFileStream.open(m_Directory, std::ios::app);
            if (!m_LogFileStream.is_open()) {
                std::cerr << "Error: Could not open log file at " << m_Directory << std::endl;
            }
        }
    }

    // --- Clear Log File ---
    void Logger::ClearLogFile(const char* File) {
        std::ofstream MyFile;
        MyFile.open(File, std::ofstream::out | std::ofstream::trunc);
        MyFile.close();
    }

    // --- Core Logging Logic ---
    void Logger::PrintAndSave(Level Level, const char* Message, ...) {
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
            case Level::Info:       LevelString = "\033[34m[INFO]"; break; // Blue
            case Level::Debug:      LevelString = "\033[36m[DEBUG]"; break; // Cyan
            case Level::Trace:      LevelString = "\033[90m[TRACE]"; break; // Bright Grey
            case Level::Warning:    LevelString = "\033[32m[WARNING]"; break; // Yellow
            case Level::Error:      LevelString = "\033[31m[ERROR]"; break; // Red
            case Level::Critical:   LevelString = "\033[1;31m[CRITICAL]"; break; // Bold Red
            default:                LevelString = "[LOG]"; break; // White
        }
        
        LogMessageStream << " " << LevelString << ": " << Message;
        std::string LogMessage = LogMessageStream.str();

        // Console Output
        std::cout << LogMessage << std::endl;

        // File Output
        if (m_IsSaveLogEnabled && m_LogFileStream.is_open()) {
            m_LogFileStream << LogMessage << std::endl;
            m_LogFileStream.flush(); // Force write to disk
        }
    }

    // --- Individual Logging Functions ---
    void Logger::Info(const char* Message, ...) {
        PrintAndSave(Level::Info, Message);
        std::cout << "\033[0m";
    }

    void Logger::Debug(const char* Message, ...) {
        if (m_IsDebugEnabled) {
            PrintAndSave(Level::Debug, Message);
            std::cout << "\033[0m";
        }
    }

    void Logger::Trace(const char* Message, ...) {
        if (m_IsTraceEnabled) {
            PrintAndSave(Level::Trace, Message);
            std::cout << "\033[0m";
        }
    }

    void Logger::Warning(const char* Message, ...) {
        PrintAndSave(Level::Warning, Message);
        std::cout << "\033[0m";
    }

    void Logger::Critical(const char* Message, ...) {
        PrintAndSave(Level::Critical, Message);
        std::cout << "\033[0m";
    }

    void Logger::Error(const char* Message, ...) {
        PrintAndSave(Level::Error, Message);
        std::cout << "\033[0m";
    }
}
