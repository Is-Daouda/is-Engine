#ifndef FILEPATH_H_INCLUDED
#define FILEPATH_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// class to manage the path of a file
////////////////////////////////////////////////////////////
class FilePath
{
public:
    FilePath(std::string filePath):
        m_strFilePath(filePath),
        m_fileIsLoaded(false)
    {}

    /// Set file path
    virtual void setFilePath(std::string filePath) {m_strFilePath = filePath;}

    /// Return file path
    virtual const std::string& getFilePath() const noexcept {return m_strFilePath;}

    /// Allows to know if file is loaded
    virtual bool getFileIsLoaded() const {return m_fileIsLoaded;}

protected:
    std::string m_strFilePath;
    bool m_fileIsLoaded;
};
}

#endif // FILEPATH_H_INCLUDED
