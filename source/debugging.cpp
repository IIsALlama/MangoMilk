#include "debugging.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace MangoMilk {
	namespace Debug {
		const ImVec4 COLOUR_ERROR = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		const ImVec4 COLOUR_WARNING = ImVec4(1.0f, 1.0f, 0.8f, 1.0f);
		const ImVec4 COLOUR_MESSAGE = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

		std::vector<LogMessage> debugLog;

		LogMessage::LogMessage(LogType _type, const std::string& _msg) {
			type = _type;
			msg = _msg;
		}

		void Log(const std::string& msg) {
			LogMessage newMsg = LogMessage(LogType::Message, msg);
			debugLog.push_back(newMsg);
		}

		void LogWarning(const std::string& msg) {
			LogMessage newMsg = LogMessage(LogType::Warning, msg);
			debugLog.push_back(newMsg);
		}

		void LogError(const std::string& msg) {
			LogMessage newMsg = LogMessage(LogType::Error, msg);
			debugLog.push_back(newMsg);
		}

		int GetLogSize() {
			return debugLog.size();
		}

		LogMessage* GetLog(int i) {
			return &debugLog[i];
		}

		void Window()
		{
			ImGui::Begin("Console");

			ImGui::BeginChild("Scrolling");
			for (int n = 0; n < Debug::GetLogSize(); n++) {
				Debug::LogMessage* log = Debug::GetLog(n);
				switch (Debug::GetLog(n)->type)
				{
				default:
					break;
				case Debug::LogType::Message:
					ImGui::TextColored(COLOUR_MESSAGE, Debug::GetLog(n)->msg.c_str(), n);
					break;
				case Debug::LogType::Warning:
					ImGui::TextColored(COLOUR_WARNING, Debug::GetLog(n)->msg.c_str(), n);
					break;
				case Debug::LogType::Error:
					ImGui::TextColored(COLOUR_ERROR, Debug::GetLog(n)->msg.c_str(), n);
					break;
				}
			}
			ImGui::EndChild();

			ImGui::End();
		}

	}

}

