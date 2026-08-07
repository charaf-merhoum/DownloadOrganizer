#include <algorithm>
#include "Utils/StringUtils.hpp"

namespace Core::Utils
{
	std::string trim(const std::string& str) {
		const std::string whitespace = " \t\n\r\f\v";
		size_t start = str.find_first_not_of(whitespace);
		if (start == std::string::npos) return ""; // All whitespace
		size_t end = str.find_last_not_of(whitespace);
		return str.substr(start, end - start + 1);
	}
	std::string toLower(const std::string& str) {
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
			return (c <= 127) ? std::tolower(c) : c;
			});
		return result;
	}
	std::vector<std::string> readFileUtf8(const fs::path& filepath) {
		std::vector<std::string> lines;
		std::ifstream file(filepath,std::ios::binary);
		if (!file.is_open()) {
			std::cerr << "Failed to open file: " << filepath << std::endl;
			return lines;
		}
		
		// handle UTF-8 BOM if present
		unsigned char bom[3];
		if (file.read(reinterpret_cast<char*>(bom), 3)) {
			if( !(bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) )
			{
				file.clear();
				file.seekg(0, std::ios::beg);
			}
		}
		else
		{
			file.clear();
			file.seekg(0, std::ios::beg);
		}

		std::string line;
		while (std::getline(file, line)) {

			//handle Windows line endings '\r'
			if (!line.empty() && line.back() == '\r') {
				line.pop_back();
			}
			lines.push_back(line);
			
		}
		file.close();
		return lines;
	}

}