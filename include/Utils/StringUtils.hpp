#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace Core::Utils {
	
	std::string trim(const std::string& str);
	std::string toLower(const std::string& str);
	
	std::vector<std::string> readFileUtf8(const fs::path& filepath);

}
#endif // !STRING_UTILS_HPP
