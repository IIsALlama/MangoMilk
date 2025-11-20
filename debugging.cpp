#include "debugging.h"

namespace MangoMilk {
	namespace Debug {
		vector<LogMessage> debugLog;

		LogMessage::LogMessage(LogType _type, const char* _msg) {
			type = _type;
			msg = _msg;
		}

		void Log(const char msg[]) {
			LogMessage newMsg = LogMessage(LogType::Message, msg);
			debugLog.push_back(newMsg);
		}

		void LogWarning(const char msg[]) {
			LogMessage newMsg = LogMessage(LogType::Warning, msg);
			debugLog.push_back(newMsg);
		}

		void LogError(const char msg[]) {
			LogMessage newMsg = LogMessage(LogType::Error, msg);
			debugLog.push_back(newMsg);
		}

		int GetLogSize() {
			return debugLog.size();
		}

		LogMessage* GetLog(int i) {
			return &debugLog[i];
		}

	}

}

