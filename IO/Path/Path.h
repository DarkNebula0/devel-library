#pragma once

#include <filesystem>
#include <utility>
#include <iterator>

namespace Devel::IO
{
#ifdef _WIN32
    namespace fs = std::experimental::filesystem;
#else
    namespace fs = std::filesystem;
#endif

    class CPath
    {
    public:
        CPath() = default;
        CPath(fs::path i_oPath) : m_oPath(std::move(i_oPath)) {}
        CPath(const CPath &i_oPath) { this->operator=(i_oPath); }
        CPath(CPath &&i_oPath) { this->operator=(std::move(i_oPath)); }
    private:
        fs::path m_oPath;
    public:
        void setPath(fs::path i_oPath)
        {
            this->m_oPath = std::move(i_oPath);
        }

        fs::path replaceFilename(const fs::path &i_oFilename)
        {
            return this->m_oPath.replace_filename(i_oFilename);
        }

        fs::path replaceExtension(const fs::path &i_oExtension)
        {
            return this->m_oPath.replace_extension(i_oExtension);
        }
    public:
        fs::path getRootName() const
        {
            return this->m_oPath.root_name();
        }

        fs::path getRootPath() const
        {
            return this->m_oPath.root_path();
        }

        fs::path getRelativePath() const
        {
            return this->m_oPath.relative_path();
        }

        fs::path getParentPath() const
        {
            return this->m_oPath.parent_path();
        }

        fs::path getFileNameWithoutExtension() const
        {
            return this->m_oPath.stem();
        }

        fs::path getFileExtension() const
        {
            return this->m_oPath.extension();
        }

        fs::path getAbsolutePath() const
        {
            return fs::canonical(this->m_oPath);
        }

        fs::path removeFilename()
        {
            return this->m_oPath.remove_filename();
        }

        const fs::path &getPath() const  {
            return this->m_oPath;
        }
    public:
        std::string toStdString() const
        {
            return this->m_oPath.generic_string();
        }

        std::wstring toStdWString() const
        {
            return this->m_oPath.wstring();
        }

    public:
        bool hasRootName() const
        {
            return this->m_oPath.has_root_name();
        }

        bool hasRootDirectory() const
        {
            return this->m_oPath.has_root_directory();
        }

        bool hasRelativePath() const
        {
            return this->m_oPath.has_relative_path();
        }

        bool hasParentPath() const
        {
            return this->m_oPath.has_parent_path();
        }

        bool hasFilename() const
        {
            return this->m_oPath.has_filename();
        }

        bool hasFileNameWithoutExtension() const
        {
            return this->m_oPath.has_stem();
        }

        bool hasExtension() const
        {
            return this->m_oPath.has_extension();
        }

        bool isAbsolutePath() const
        {
            return this->m_oPath.is_absolute();
        }

        bool isRelativePath() const
        {
            return this->m_oPath.is_relative();
        }

    public:
        auto begin()
        {
            return this->m_oPath.begin();
        }
        auto end()
        {
            return this->m_oPath.end();
        }

    public:
        bool exists() const
        {
            return CPath::exists(this->m_oPath);
        }

    public:
        CPath &operator=(fs::path i_oPath)
        {
            this->m_oPath = std::move(i_oPath);
            return *this;
        }

        CPath &operator=(const CPath &i_oPath)
        {
            this->m_oPath.operator=(i_oPath.m_oPath);
            return *this;
        }

        CPath &operator=(CPath &&i_oPath)
        {
            this->m_oPath = std::move(i_oPath.m_oPath);
            return *this;
        }

        CPath &operator+=(const fs::path &i_oPath)
        {
            this->m_oPath.operator+=(i_oPath);
            return *this;
        }

        CPath &operator+=(const CPath &i_oPath)
        {
            return this->operator+=(i_oPath.m_oPath);
        }

    public:
        static bool exists(const fs::path &i_oPath)
        {
            return fs::exists(i_oPath);
        }
    };

}