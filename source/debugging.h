#pragma once
#include "common.h"

namespace MangoMilk {
	namespace Debug {
		enum LogType {
			Message,
			Warning,
			Error
		};

		class LogMessage {
		private:

		public:
			LogType type;
			std::string msg;

			LogMessage(LogType type, const std::string& msg);
		};

		void Log(const std::string& msg);
		void LogWarning(const std::string& msg);
		void LogError(const std::string& msg);

		int GetLogSize();
		LogMessage* GetLog(int i);
		void Window();
	}
}