#pragma once

#include "IO/Path/Path.h"

#include <Core/Exceptions.h>
#include <utility>
#include <vector>
#include <optional>

/// @namespace Devel::IO
/// @brief The namespace encapsulating I/O related classes and functions in the Devel framework.
namespace Devel::IO {
    namespace fs = std::filesystem;

    /// @class Devel::IO::CDir
    /// @brief A class for directory operations.
    ///
    /// This class encapsulates operations related to directories like getting directory files, creating directories, creating directory symlink, and more.
    ///
    /// <b>Example</b>
    ///
    /// The following example demonstrates how to use various functionalities of the `CDir` class.
    ///
    /// @code{.cpp}
    ///     // Creating an instance of CDir for a specific path
    ///     Devel::IO::CDir dir = Devel::IO::CDir::CDir(CPath("/path/to/directory"));
    ///
    ///     // Get all files in the directory (not recursively)
    ///     std::vector<CPath> files = dir.getDirectoryFiles();
    ///
    ///     // Get all ".txt" files in the directory and its subdirectories
    ///     std::vector<CPath> txtFiles = dir.getDirectoryFiles(true, std::vector<std::string>{".txt"});
    ///
    ///     // Create a new directory
    ///     bool success = Devel::IO::CDir::createDirectories(CPath("/path/to/new/directory"));
    ///
    ///     // Create a symlink for a directory
    ///     Devel::IO::CDir::createDirectorySymlink(CPath("/path/to/original/directory"), CPath("/path/to/symlink"));
    ///
    ///     // Check if a path is a directory
    ///     bool isDir = Devel::IO::CDir::isDirectory(CPath("/path/to/check"));
    ///
    ///     // Get the path of the temporary directory
    ///     CPath tempDir = Devel::IO::CDir::getTempDirectoryPath();
    /// @endcode
    class CDir {
    public:
        /// @brief Default constructor for CDir.
        CDir() = default;

        /// @brief Construct a CDir object using the provided path.
        /// @param i_oPath - The path for the directory.
        explicit CDir(CPath i_oPath) : m_oPath(std::move(i_oPath)) {};
    private:
        /// @var CPath Devel::IO::CDir::m_oPath
        /// @brief The path of the directory.
        CPath m_oPath;
    public:
        /// @brief Get the files in the directory.
        /// @param i_bIsRecursive - Whether to recursively look in subdirectories.
        /// @param i_astExtensionFilters - Optional list of file extensions to filter.
        /// @return A vector containing the paths of the files.
        std::vector<CPath> getDirectoryFiles(bool i_bIsRecursive = false,
                                             std::optional<std::vector<std::string>> i_astExtensionFilters = std::nullopt);

    public:
        /// @brief Static function to create directories.
        /// @param i_oPath - The path where the directories should be created.
        /// @return true if the directories were successfully created, false otherwise.
        static bool createDirectories(const CPath &i_oPath) {
            return fs::create_directories(i_oPath.getPath());
        }

        /// @brief Static function to create a symlink for a directory.
        /// @param i_oTargetPath - The original directory.
        /// @param i_oLinkPath - The symlink path.
        static void createDirectorySymlink(const CPath &i_oTargetPath, const CPath &i_oLinkPath) {
            return fs::create_directory_symlink(i_oTargetPath.getPath(), i_oLinkPath.getPath());
        }

        /// @brief Static function to check if a path is a directory.
        /// @param i_oPath - The path to check.
        /// @return true if the path is a directory, false otherwise.
        static bool isDirectory(const CPath &i_oPath) {
            return fs::is_directory(i_oPath.getPath());
        }

        /// @brief Static function to get the path of the temporary directory.
        /// @return The path of the temporary directory.
        static CPath getTempDirectoryPath() {
            return CPath(std::move(fs::temp_directory_path()));
        }
    };
}