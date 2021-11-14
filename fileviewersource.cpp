#include "fileviewersource.h"
namespace
{
const QStringList dirFilter =
{
    "*.astc", "*.jpeg", "*.png", "*.jpg", "*.gif"
};
}

FileViewerSource::FileViewerSource(QObject *parent) :
    QObject(parent),
    m_backgroundType(FileViewerSourceBGType::e::BGType_transparent)
{

}

QString FileViewerSource::currentPath() const
{
    return  m_currentPath;
}

void FileViewerSource::setCurrentPath(const QString& s)
{
    if(m_currentPath != s)
    {
        m_currentPath = s;
        emit currentPathChanged(m_currentPath);
    }
}

QStringList FileViewerSource::folderContent()
{
    QStringList l;
    QFileInfo i(m_currentPath);
    QDir d = i.absoluteDir();
    d.setNameFilters(dirFilter);
    d.setFilter(QDir::Files);
    return d.entryList();
}

QString FileViewerSource::folderPath()
{
    return QFileInfo(m_currentPath).absoluteDir().path();
}

void FileViewerSource::next()
{
    QStringList l = folderContent();
    QString fname = QFileInfo(m_currentPath).fileName();
    int index = l.indexOf(fname);
    if(index < 0)
    {
        qWarning() << "cannot find" << fname << "in" << l;
        return;
    }
    int newIndex = index + 1;
    if(newIndex == l.size())
    {
        newIndex = 0;
    }
    setCurrentPath(folderPath() + "/" + l.at(newIndex));
}

void FileViewerSource::prev()
{
    QStringList l = folderContent();
    QString fname = QFileInfo(m_currentPath).fileName();
    int index = l.indexOf(fname);
    if(index < 0)
    {
        qWarning() << "cannot find" << fname << "in" << l;
        return;
    }
    int newIndex = index - 1;
    if(newIndex < 0)
    {
        newIndex = l.size() - 1;
    }
    setCurrentPath(folderPath() + "/" + l.at(newIndex));
}

bool FileViewerSource::backgroundTypeSolid() const
{
    return (m_backgroundType == FileViewerSourceBGType::e::BGType_black) || (m_backgroundType == FileViewerSourceBGType::e::BGType_white);
}

bool FileViewerSource::backgroundTypeImage() const
{
    return (m_backgroundType == FileViewerSourceBGType::e::BGType_transparent) || (m_backgroundType == FileViewerSourceBGType::e::BGType_gradient);
}

uint FileViewerSource::backgroundType() const
{
    return m_backgroundType;
}

void FileViewerSource::setBackgroundType(uint v)
{
    if(m_backgroundType != v)
    {
        m_backgroundType = v;
        emit backgroundTypeChanged(v);
        emit backgroundTypeImageChanged(backgroundTypeImage());
        emit backgroundTypeSolidChanged(backgroundTypeSolid());
    }
}
