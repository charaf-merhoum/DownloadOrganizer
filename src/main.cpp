#include <iostream>
#include <filesystem>

#include "Core/ConfigParser.hpp"
#include <Core/FileOrganizer.hpp>

std::string configPath = std::string(PROJECT_ROOT_DIR) + "/config/rules.txt";
std::string sourcePath = std::string(PROJECT_ROOT_DIR) + "/test_data/source";
std::string targetPath = std::string(PROJECT_ROOT_DIR) + "/test_data/target";

int main() {
	Core::ConfigParser parser;
	Core::FileOrganizer organizer;
	parser.loadConfig(configPath);
	Core::OrganizingReport report;
	report = organizer.organizeFiles({
		parser.getCategoryKeywords(),
		sourcePath,
		targetPath,
		Core::TransferMethod::COPY,
		Core::CollisionPolicy::RENAME
		});
	std::cout << "Total Processed: " << report.totalProcessed << "\n";
	std::cout << "Successful Moves: " << report.successfulMoves << "\n";
	std::cout << "Errors: " << report.errors.size() << "\n";
	
	for(const auto& err : report.errors) {
		std::cout << "Error code: " << err.value() << " Message: " << err.message() << "\n";
	}
	
	
	
	
	//std::cout << std::filesystem::current_path();
	/*if (parser.loadConfig(configPath)) {
		Core::KeywordMap keywords = parser.getCategoryKeywords();
		for (const auto& [category, words] : keywords) {
			std::cout << "Category: " << category << "\nKeywords: ";
			for (const auto& word : words) {
				std::cout << word << " ";
			}
			std::cout << "\n";
		}
	} else {
		std::cerr << "Failed to load configuration file.\n";
	}*/
	return 0;
}