#pragma once

#include <filesystem>
#include <utility>
#include <iterator>

namespace Devel::IO {
    namespace fs = std::filesystem;

    class CPath {
    public:
        CPath() = default;

        explicit CPath(fs::path i_oPath) : m_oPath(std::move(i_oPath)) {}

        CPath(const CPath &i_oPath) { this->operator=(i_oPath); }

        CPath(CPath &&i_oPath) noexcept { this->operator=(std::move(i_oPath)); }

    private:
        fs::path m_oPath;
    public:
        void setPath(fs::path i_oPath) {
            this->m_oPath = std::move(i_oPath);
        }

        fs::path replaceFilename(const fs::path &i_oFilename) {
            return this->m_oPath.replace_filename(i_oFilename);
        }

        fs::path replaceExtension(const fs::path &i_oExtension) {
            return this->m_oPath.replace_extension(i_oExtension);
        }

    public:
        [[nodiscard]] fs::path getRootName() const {
            return this->m_oPath.root_name();
        }

        [[nodiscard]] fs::path getRootPath() const {
            return this->m_oPath.root_path();
        }

        [[nodiscard]]  fs::path getRelativePath() const {
            return this->m_oPath.relative_path();
        }

        [[nodiscard]] fs::path getParentPath() const {
            return this->m_oPath.parent_path();
        }

        [[nodiscard]] fs::path getFileNameWithoutExtension() const {
            return this->m_oPath.stem();
        }

        [[nodiscard]] fs::path getFileExtension() const {
            return this->m_oPath.extension();
        }

        [[nodiscard]] fs::path getAbsolutePath() const {
            return fs::canonical(this->m_oPath);
        }

        fs::path removeFilename() {
            return this->m_oPath.remove_filename();
        }

        [[nodiscard]] const fs::path &getPath() const {
            return this->m_oPath;
        }

    public:
        [[nodiscard]] std::string toStdString() const {
            return this->m_oPath.generic_string();
        }

        [[nodiscard]] std::wstring toStdWString() const {
            return this->m_oPath.wstring();
        }

    public:
        [[nodiscard]] bool hasRootName() const {
            return this->m_oPath.has_root_name();
        }

        [[nodiscard]] bool hasRootDirectory() const {
            return this->m_oPath.has_root_directory();
        }

        [[nodiscard]] bool hasRelativePath() const {
            return this->m_oPath.has_relative_path();
        }

        [[nodiscard]] bool hasParentPath() const {
            return this->m_oPath.has_parent_path();
        }

        [[nodiscard]] bool hasFilename() const {
            return this->m_oPath.has_filename();
        }

        [[nodiscard]] bool hasFileNameWithoutExtension() const {
            return this->m_oPath.has_stem();
        }

        [[nodiscard]] bool hasExtension() const {
            return this->m_oPath.has_extension();
        }

        [[nodiscard]] bool isAbsolutePath() const {
            return this->m_oPath.is_absolute();
        }

        [[nodiscard]] bool isRelativePath() const {
            return this->m_oPath.is_relative();
        }

    public:
        auto begin() {
            return this->m_oPath.begin();
        }

        auto end() {
            return this->m_oPath.end();
        }

    public:
        [[nodiscard]] bool exists() const {
            return CPath::exists(this->m_oPath);
        }

    public:
        CPath &operator=(fs::path i_oPath) {
            this->m_oPath = std::move(i_oPath);
            return *this;
        }

        CPath &operator=(const CPath &i_oPath) {
            this->m_oPath.operator=(i_oPath.m_oPath);
            return *this;
        }

        CPath &operator=(CPath &&i_oPath) {
            this->m_oPath = std::move(i_oPath.m_oPath);
            return *this;
        }

        CPath &operator+=(const fs::path &i_oPath) {
            this->m_oPath.operator+=(i_oPath);
            return *this;
        }

        CPath &operator+=(const CPath &i_oPath) {
            return this->operator+=(i_oPath.m_oPath);
        }

    public:
        static bool exists(const fs::path &i_oPath) {
            return fs::exists(i_oPath);
        }
    };

}