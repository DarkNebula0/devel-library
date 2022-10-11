#pragma once

#include "IO/Path/Path.h"

#include <Core/Exceptions.h>
#include <utility>
#include <vector>
#include <optional>

namespace Devel::IO
{
    CreateFastException(CDirectoryAccessException, "Could not open directory.");

    namespace fs = std::filesystem;

    class CDir
    {
    public:
        CDir() = default;
        explicit CDir(CPath i_oPath) : m_oPath(std::move(i_oPath)) {};
    private:
        CPath m_oPath;
    public:
        std::vector<CPath> getDirectoryFiles(bool i_bIsRecursive = false, std::optional<std::vector<std::string>> i_astExtensionFilters = std::nullopt);
    public:
        static bool createDirectories(const CPath &i_oPath)
        {
            return fs::create_directories(i_oPath.getPath());
        }

        static void createDirectorySymlink(const CPath &i_oTargetPath, const CPath &i_oLinkPath)
        {
            return fs::create_directory_symlink(i_oTargetPath.getPath(), i_oLinkPath.getPath());
        }

        static bool isDirectory(const CPath& i_oPath)
        {
            return fs::is_directory(i_oPath.getPath());
        }

        static CPath getTempDirectoryPath()
        {
            return CPath(std::move(fs::temp_directory_path()));
        }
    };
}