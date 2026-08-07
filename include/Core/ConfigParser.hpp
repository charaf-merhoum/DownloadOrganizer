#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

namespace Core {
	using KeywordMap = std::map<std::string, std::vector<std::string>>;
	class ConfigParser {
	public:
		ConfigParser() = default;
		~ConfigParser() = default;
		
		bool loadConfig(const fs::path& filepath);
		KeywordMap &getCategoryKeywords() ;
		KeywordMap setCategoryKeywords(const std::vector < std::string>filelines);

	private:
		KeywordMap m_categoryKeywords;
	};
} // namespace Core


#endif // CONFIG_PARSER_HPP