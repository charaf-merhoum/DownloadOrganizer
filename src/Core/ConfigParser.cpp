#include <fstream>
#include <sstream>


#include "Core/ConfigParser.hpp"
#include "Utils/StringUtils.hpp"


namespace Core {

    bool ConfigParser::loadConfig(const fs::path &filepath ) {
        if (!fs::exists(filepath)) {
            std::cerr << "Configuration file not found: " << filepath << std::endl;
            return false;
        }
		std::vector<std::string> filelines =Core::Utils::readFileUtf8(filepath);
        setCategoryKeywords(filelines);
		return true;
    }

    KeywordMap &ConfigParser::getCategoryKeywords() {
        return m_categoryKeywords;
    }
	// Parses the configuration file ( reules.txt ) lines to populate the category keywords map
	// Expected format of each line in the configuration file:
	// Category:keyword1,keyword2,keyword3
    KeywordMap ConfigParser::setCategoryKeywords(const std::vector < std::string>filelines) {
        m_categoryKeywords.clear();
        std::string category;
        std::vector<std::string> keywordList;
        for (const auto& line : filelines )
        {
            if (line.empty()) continue;
			size_t colonPos = line.find(':');
            if (colonPos != std::string::npos)
            {
				category = line.substr(0, colonPos);
				std::string keywords = line.substr(colonPos + 1);
				category = Utils::trim(category);
                
                

				keywordList.clear();
				std::istringstream issk(keywords);
				std::string keyword;
                while (std::getline(issk, keyword, ',')) {
                    keyword = Utils::trim(keyword);
                    if (!keyword.empty()) {
                        keywordList.push_back(keyword);
                    }
                }
				
            }
			else // handle lines without a colon ':' as potential keywords for the last category
            {
                if (!category.empty())
                {
                    std::istringstream issk(line);
                    std::string keyword;
                    while (std::getline(issk, keyword, ',')) {
                        keyword = Utils::trim(keyword);
                        if (!keyword.empty()) {
                            keywordList.push_back(keyword);
                        }
                    }
                }
            }
            m_categoryKeywords[category] = keywordList;
        }
		return m_categoryKeywords;
	}

} // namespace Core