#include "Dir.h"

#include <algorithm>
#include <variant>

namespace Devel::IO {
    template<typename T>
    std::vector<Devel::IO::CPath>
    GetDirectoryFiles(const fs::path &i_oPath, const std::optional<std::vector<std::string>> &i_astExtensionFilters) {
        std::vector<CPath> aoFiles;
        const std::vector<std::string> &astFilter = i_astExtensionFilters.value_or(std::vector<std::string>());

        for (const fs::directory_entry &oPath: T(i_oPath)) {
            if (oPath.is_regular_file()) {
                if (!astFilter.empty() &&
                    std::find(astFilter.begin(), astFilter.end(), oPath.path().extension().string()) ==
                    astFilter.end()) {
                    continue;
                }
                aoFiles.emplace_back(oPath);
            }
        }

        return aoFiles;
    }
}

std::vector<Devel::IO::CPath>
Devel::IO::CDir::getDirectoryFiles(bool i_bIsRecursive, std::optional<std::vector<std::string>> i_astExtensionFilters) {
    return i_bIsRecursive
           ? GetDirectoryFiles<fs::recursive_directory_iterator>(this->m_oPath.getPath(), i_astExtensionFilters)
           : GetDirectoryFiles<fs::directory_iterator>(this->m_oPath.getPath(), i_astExtensionFilters);
}
