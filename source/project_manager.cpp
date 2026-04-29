#include "project_manager.h"

#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;



namespace MangoMilk {
	namespace ProjectManager {

		std::vector<fs::path> projects;
		Project* currentProject;

		int CreateFolder(fs::path path) {
			if (!fs::exists(path)) {
				if (fs::create_directory(path)) {
					std::cout << "Folder created at: " << path << "\n";
				}
				else {
					std::cerr << "Failed to create folder.\n";
					return -1;
				}
			}
			else {
				std::cout << "Folder already exists at: " << path << "\n";
				return -1;
			}

			return 0;
		}

		void SaveProjectSettings() {

		}

		void NewProject(std::string name) {
			fs::path path = fs::current_path();

			CreateFolder(path / "Projects");
			if (CreateFolder(path / "Projects" / name) == -1) {
				return;
			};

			Project* newProject = new Project();
			newProject->name = name;
			currentProject = newProject;
			projects.push_back(path / "Projects" / name);
		}

		void LoadProjects() {
			fs::path path = fs::current_path() / "Projects";
			for (const auto& entry : fs::directory_iterator(path)) {
				projects.push_back(entry.path());
			}
		}

		std::vector<fs::path> GetProjects() {
			return projects;
		}

		void OpenProject(fs::path path) {
			Project* newProject = new Project();
			newProject->name = path.filename().string();
			currentProject = newProject;
		}

		void Initialize() {
			LoadProjects();
		}

	}
}