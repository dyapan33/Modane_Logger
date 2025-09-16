# Modane Logger (C++)
A Logging library that is a lightweight logger with basic features and easy to understand code. This logger has support for Info, Debug, Trace, Warning, Critical, and Error logging levels. It has three main features, these three main features are:
1) Saving logs to a file
2) Support for timestamps and an easy format
3) Support for coloured text

More features are coming soon!

## Building
You do not have to build this library, just git clone this repository and put the code into your project!

## Documentation
To Initialise the logger, copy and paste the following lines of code into your main.cpp file:
Logging::Logger MyLogger; // Required
MyLogger.Init(true, true, true); 
// For your information on the Init function, the first 'true' is for whether you want Debug logging level to be supported, the second 'true' is for whether you want Trace logging level to be supported, 
// and the final 'true' is for whether you want to have saving the log enabled.
MyLogger.ClearLogFile("Log.txt"); // Only include this into your code if you have saving enabled
MyLogger.Save("Log.txt"); // Only include this into your code if you have saving enabled
MyLogger.Info("Program started...");


