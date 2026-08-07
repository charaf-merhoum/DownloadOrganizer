#include <system_error>
#include <iostream>

#include "Core/FileOrganizer.hpp"
#include "Utils/StringUtils.hpp"

namespace Core {
	OrganizingReport FileOrganizer::organizeFiles(const OrganizingParams& params)
	{
		OrganizingReport report; //HANDLE later
		std::error_code ec;
		std::error_code ec_d;
		try {
			for (const auto& entry : fs::directory_iterator(params.sourcePath))
			{
				report.totalProcessed++;
				if (fs::is_regular_file(entry))
				{
					std::u8string u8filename = entry.path().filename().u8string();
					std::string filename(u8filename.begin(), u8filename.end());

					std::string category = FileOrganizer::findFileCategory(filename, params.rules);
					std::u8string u8category(category.begin(), category.end());

					fs::path categorypath = params.targetPath / category;
					
					fs::path sourcefile = entry.path();
					fs::path filedest = categorypath / u8filename;

					fs::create_directories(categorypath, ec_d);
					if (ec_d)
					{
						report.errors.push_back(ec_d);
						continue;
					}
					OrganizingParams fileParam{ params.rules, sourcefile, filedest, params.transferMethod, params.collisionPolicy };
					if (!(ec = FileOrganizer::transferFile(fileParam)))
					{
						report.successfulMoves++;
					}
					else
					{
						report.errors.push_back(ec);
					}
				}
			}
		}catch(const std::exception& e) {
			std::cerr << "Error: " << e.what() << '\n';
		}
		return report;
	}
	
	std::error_code FileOrganizer::transferFile(const OrganizingParams& param) {
		std::error_code ec;
		fs::path source = param.sourcePath;
		fs::path dest = param.targetPath;
		switch (param.transferMethod) {
			case TransferMethod::MOVE:
				fs::rename(source, dest, ec);
				break;
			case TransferMethod::COPY:
				fs::copy(source, dest, fs::copy_options::overwrite_existing, ec);
				break;
			case TransferMethod::HARDLINK:
				fs::create_hard_link(source, dest, ec);
				if (ec) {
					std::error_code hardlinkEc = ec;
					if (hardlinkEc == std::errc::cross_device_link)
					{
						ec.clear();
						fs::copy(source, dest, fs::copy_options::overwrite_existing, ec);
					}
				}
				break;
			case TransferMethod::SOFTLINK:
				fs::create_symlink(source, dest, ec);
				break;
			default:
				return ec;
		}
		return ec;
	}

	std::string FileOrganizer::findFileCategory(const std::string& filename, const KeywordMap& rules) {
		
		std::string lowercaseFilename = Core::Utils::toLower(filename);

		for (const auto& [category, keywords] : rules ) {
			for (const auto& keyword : keywords) {
				if (lowercaseFilename.find(keyword) != std::string::npos) {
					return category;
				}
			}
		}
		return "Uncategorized";
	}
}