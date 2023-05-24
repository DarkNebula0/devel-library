#pragma once

#include <filesystem>
#include <utility>
#include <iterator>

/// @namespace Devel::IO
/// @brief The namespace encapsulating I/O related classes and functions in the Devel framework.
namespace Devel::IO {
    namespace fs = std::filesystem;

    /// @class Devel::IO::CPath
    /// @brief A class that encapsulates the functionality of std::filesystem::path.
    ///
    /// This class provides an interface for manipulating and inspecting file paths.
    ///
    /// <b>Example</b>
    ///
    /// @code{.cpp}
    ///     Devel::IO::CPath myPath("/home/user/myfile.txt");
    ///
    ///     fs::path parentPath = myPath.getParentPath();
    ///     std::cout << "Parent path: " << parentPath << std::endl;
    ///
    ///     fs::path withoutExt = myPath.getFileNameWithoutExtension();
    ///     std::cout << "File name without extension: " << withoutExt << std::endl;
    /// @endcode
    class CPath {
    public:
        /// @brief Default constructor.
        CPath() = default;

        /// @brief Construct from a std::filesystem::path.
        /// @param i_oPath - The path to encapsulate.
        explicit CPath(fs::path i_oPath) : m_oPath(std::move(i_oPath)) {}

        /// @brief Copy constructor.
        /// @param i_oPath - The path to copy.
        CPath(const CPath &i_oPath) { this->operator=(i_oPath); }

        /// @brief Move constructor.
        /// @param i_oPath - The path to move.
        CPath(CPath &&i_oPath) noexcept { this->operator=(std::move(i_oPath)); }

    private:
        /// @var fs::path m_oPath
        /// @brief The encapsulated std::filesystem::path.
        fs::path m_oPath;
    public:
        /// @brief Sets the path.
        /// @param i_oPath - The new path.
        void setPath(fs::path i_oPath) {
            this->m_oPath = std::move(i_oPath);
        }

        /// @brief Replaces the filename in the path.
        /// @param i_oFilename - The new filename.
        /// @return The new path as an fs::path object.
        fs::path replaceFilename(const fs::path &i_oFilename) {
            return this->m_oPath.replace_filename(i_oFilename);
        }

        /// @brief Replaces the extension in the path.
        /// @param i_oExtension - The new extension.
        /// @return The new path as an fs::path object.
        fs::path replaceExtension(const fs::path &i_oExtension) {
            return this->m_oPath.replace_extension(i_oExtension);
        }

    public:
        /// @brief Returns the root name of the path.
        /// @return The root name as an fs::path object.
        [[nodiscard]] fs::path getRootName() const {
            return this->m_oPath.root_name();
        }

        /// @brief Returns the root directory of the path.
        /// @return The root directory as an fs::path object.
        [[nodiscard]] fs::path getRootPath() const {
            return this->m_oPath.root_path();
        }

        /// @brief Returns the relative path.
        /// @return The relative path as an fs::path object.
        [[nodiscard]]  fs::path getRelativePath() const {
            return this->m_oPath.relative_path();
        }

        /// @brief Returns the parent path.
        /// @return The parent path as an fs::path object.
        [[nodiscard]] fs::path getParentPath() const {
            return this->m_oPath.parent_path();
        }

        /// @brief Returns the filename without extension.
        /// @return The filename without extension as an fs::path object.
        [[nodiscard]] fs::path getFileNameWithoutExtension() const {
            return this->m_oPath.stem();
        }

        /// @brief Returns the file extension.
        /// @return The file extension as an fs::path object.
        [[nodiscard]] fs::path getFileExtension() const {
            return this->m_oPath.extension();
        }

        /// @brief Returns the absolute path.
        /// @return The absolute path as an fs::path object.
        [[nodiscard]] fs::path getAbsolutePath() const {
            return fs::canonical(this->m_oPath);
        }

        /// @brief Removes the filename from the path.
        /// @return The path without the filename as an fs::path object.
        fs::path removeFilename() {
            return this->m_oPath.remove_filename();
        }

        /// @brief Returns the encapsulated fs::path object.
        /// @return The encapsulated fs::path object.
        [[nodiscard]] const fs::path &getPath() const {
            return this->m_oPath;
        }

    public:
        /// @brief Converts the path to a standard string.
        /// @return The path as a standard string.
        [[nodiscard]] std::string toStdString() const {
            return this->m_oPath.generic_string();
        }

        /// @brief Converts the path to a standard wide string.
        /// @return The path as a standard wide string.
        [[nodiscard]] std::wstring toStdWString() const {
            return this->m_oPath.wstring();
        }

    public:
        /// @brief Checks if the path has a root name.
        /// @return true if the path has a root name, false otherwise.
        [[nodiscard]] bool hasRootName() const {
            return this->m_oPath.has_root_name();
        }

        /// @brief Checks if the path has a root directory.
        /// @return true if the path has a root directory, false otherwise.
        [[nodiscard]] bool hasRootDirectory() const {
            return this->m_oPath.has_root_directory();
        }

        /// @brief Checks if the path has a relative path.
        /// @return true if the path has a relative path, false otherwise.
        [[nodiscard]] bool hasRelativePath() const {
            return this->m_oPath.has_relative_path();
        }

        /// @brief Checks if the path has a parent path.
        /// @return true if the path has a parent path, false otherwise.
        [[nodiscard]] bool hasParentPath() const {
            return this->m_oPath.has_parent_path();
        }

        /// @brief Checks if the path has a filename.
        /// @return true if the path has a filename, false otherwise.
        [[nodiscard]] bool hasFilename() const {
            return this->m_oPath.has_filename();
        }

        /// @brief Checks if the path has a filename without extension.
        /// @return true if the path has a filename without extension, false otherwise.
        [[nodiscard]] bool hasFileNameWithoutExtension() const {
            return this->m_oPath.has_stem();
        }

        /// @brief Checks if the path has an extension.
        /// @return true if the path has an extension, false otherwise.
        [[nodiscard]] bool hasExtension() const {
            return this->m_oPath.has_extension();
        }

        /// @brief Checks if the path is absolute.
        /// @return true if the path is absolute, false otherwise.
        [[nodiscard]] bool isAbsolutePath() const {
            return this->m_oPath.is_absolute();
        }

        /// @brief Checks if the path is relative.
        /// @return true if the path is relative, false otherwise.
        [[nodiscard]] bool isRelativePath() const {
            return this->m_oPath.is_relative();
        }

    public:
        /// @brief Returns an iterator to the beginning of the path.
        /// @return An iterator to the beginning of the path.
        auto begin() {
            return this->m_oPath.begin();
        }

        /// @brief Returns an iterator to the end of the path.
        /// @return An iterator to the end of the path.
        auto end() {
            return this->m_oPath.end();
        }

    public:
        /// @brief Checks whether the path exists.
        /// @return true if the path exists, false otherwise.
        [[nodiscard]] bool exists() const {
            return CPath::exists(this->m_oPath);
        }

    public:
        /// @brief Assigns a new path to the object.
        /// @param i_oPath - The new path.
        /// @return A reference to the object.
        CPath &operator=(fs::path i_oPath) {
            this->m_oPath = std::move(i_oPath);
            return *this;
        }

        /// @brief Assigns a new path to the object.
        /// @param i_oPath - The new path.
        /// @return A reference to the object.
        CPath &operator=(const CPath &i_oPath) {
            this->m_oPath.operator=(i_oPath.m_oPath);
            return *this;
        }

        /// @brief Assigns a new path to the object.
        /// @param i_oPath - The new path.
        /// @return A reference to the object.
        CPath &operator=(CPath &&i_oPath) {
            this->m_oPath = std::move(i_oPath.m_oPath);
            return *this;
        }

        /// @brief Appends a path to the current path.
        /// @param i_oPath - The path to append.
        /// @return A reference to the object.
        CPath &operator+=(const fs::path &i_oPath) {
            this->m_oPath.operator+=(i_oPath);
            return *this;
        }

        /// @brief Appends a path to the current path.
        /// @param i_oPath - The path to append.
        /// @return A reference to the object.
        CPath &operator+=(const CPath &i_oPath) {
            return this->operator+=(i_oPath.m_oPath);
        }

    public:
        /// @brief Checks whether a path exists.
        /// @param i_oPath - The path to check.
        /// @return true if the path exists, false otherwise.
        static bool exists(const fs::path &i_oPath) {
            return fs::exists(i_oPath);
        }
    };

}