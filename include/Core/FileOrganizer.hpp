#ifndef FILE_ORGANIZER_HPP
#define FILE_ORGANIZER_HPP

#include <system_error>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

#include "Core/ConfigParser.hpp"

namespace fs = std::filesystem ;

namespace Core {
	struct OrganizingReport {
		int totalProcessed = 0;
		int successfulMoves = 0;
		std::vector<std::error_code> errors;
	};
	enum class CollisionPolicy{
		OVERWRITE,
		SKIP,
		RENAME
	};
	enum class TransferMethod {
		MOVE,
		COPY,
		HARDLINK,
		SOFTLINK
	};
	
	struct OrganizingParams
	{
		const KeywordMap& rules;
		const fs::path sourcePath;
		const fs::path targetPath;
		TransferMethod transferMethod = TransferMethod::MOVE;
		CollisionPolicy collisionPolicy = CollisionPolicy::RENAME ;
	};
	class FileOrganizer {
	public:
		FileOrganizer() = default;
		~FileOrganizer() = default;
		
		OrganizingReport organizeFiles(const OrganizingParams& params );
	private:


		std::error_code transferFile(const OrganizingParams& param);
		
		std::string findFileCategory(const std::string& filename, const KeywordMap& rules);
	};
} // namespace Core
#endif // FILE_ORGANIZER_HPP
