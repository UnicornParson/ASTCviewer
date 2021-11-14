#ifndef FILEVIEWERSOURCE_H
#define FILEVIEWERSOURCE_H

#include <QObject>
#include <QtQml>

class FileViewerSourceBGType : public QObject
{
    Q_OBJECT
public:
    enum e
    {
        BGType_white,
        BGType_black,
        BGType_transparent,
        BGType_gradient
    };
    Q_ENUM(e)

    static void RegisterTypes()
    {
        qmlRegisterType<FileViewerSourceBGType>("BGType", 1, 0, "BGType");
    }
};

class FileViewerSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentPath READ currentPath WRITE setCurrentPath NOTIFY currentPathChanged)
    Q_PROPERTY(uint backgroundType READ backgroundType WRITE setBackgroundType NOTIFY backgroundTypeChanged)
    Q_PROPERTY(bool backgroundTypeSolid READ backgroundTypeSolid NOTIFY backgroundTypeSolidChanged)
    Q_PROPERTY(bool backgroundTypeImage READ backgroundTypeImage NOTIFY backgroundTypeImageChanged)
public:

    explicit FileViewerSource(QObject *parent = nullptr);

    QString currentPath() const;
    Q_INVOKABLE void setCurrentPath(const QString& s);

    Q_INVOKABLE void next();
    Q_INVOKABLE void prev();

    uint backgroundType() const;
    Q_INVOKABLE void setBackgroundType(uint v);

    bool backgroundTypeSolid() const;
    bool backgroundTypeImage() const;
    Q_INVOKABLE QStringList folderContent();
    Q_INVOKABLE QString folderPath();

signals:
    void currentPathChanged(const QString& s);
    void backgroundTypeChanged(uint v);

    void backgroundTypeImageChanged(bool b);
    void backgroundTypeSolidChanged(bool b);

    void fileDialogRequested();
private:


    QString m_currentPath;
    uint m_backgroundType;
};

#endif // FILEVIEWERSOURCE_H
