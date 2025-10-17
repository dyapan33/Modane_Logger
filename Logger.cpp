// This file is part of the Modane Logger Project and can be found at github.com/dyapan33/Modane_Logger/
#include "Logger.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
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
}


