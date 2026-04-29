#pragma once

#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;


namespace MangoMilk {
	namespace ProjectManager {

		class ProjectSettings {};

		class Project
		{
		private:

		public:
			std::string name;
			ProjectSettings* settings = new ProjectSettings();

			fs::path getDir() { return fs::current_path() / "Projects" / name; }
		};

		int CreateFolder(fs::path path);
		void NewProject(std::string name);
		void LoadProjects();
		std::vector<fs::path> GetProjects();
		void OpenProject(fs::path path);
		void Initialize();

	}
}