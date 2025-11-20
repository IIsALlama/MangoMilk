#pragma once

#include <vector>
using std::vector;

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
			const char* msg;

			LogMessage(LogType type, const char* msg);
		};

		void Log(const char msg[]);
		void LogWarning(const char msg[]);
		void LogError(const char msg[]);

		int GetLogSize();
		LogMessage* GetLog(int i);
	}

}