#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QDir>
#include "viewerwidget.h"
#include "qmlfileviewer.h"

bool isFile(const QString& path) noexcept
{
    return QFile::exists(path);
}

bool isFolder(const QString& path) noexcept
{
    return QDir(path).exists();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString initial = ""; //":/examples/res/exampleJPG.jpg";
    if(a.arguments().size() > 1)
    {
        QString s = a.arguments().at(1).trimmed();
        if(!s.isEmpty())
        {
            initial = s;
        }
    }
    qDebug() << initial;
    QmlFileViewer* fileWidget = new QmlFileViewer();
    if(isFile(initial))
    {
        fileWidget->loadFile(initial);

    }
    fileWidget->exec();
    return a.exec();
}
