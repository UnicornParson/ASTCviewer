#include "qmlfileviewer.h"
#include <QFile>
#include <QPixmap>
#include <QDebug>
#include <QErrorMessage>
#include <QQmlEngine>
#include <QQmlContext>
#include <QFileDialog>

namespace
{
const QUrl rootQml("qrc:/qml/root.qml");
}

QmlFileViewer::QmlFileViewer(QWidget *parent) noexcept:
    QQuickWidget(parent),
    m_source(nullptr)
{
    m_source = new FileViewerSource(this);
    FileViewerSourceBGType::RegisterTypes();
    //QQmlContext* ctx = rootContext();
    QQmlEngine *e = engine();

    e->rootContext()->setContextProperty("fvsource", m_source);
    e->addImageProvider("", &m_imgProvider);
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setMinimumWidth(800);
    setMinimumHeight(600);
    connect(m_source, &FileViewerSource::currentPathChanged, [this](const QString& s)
    {
        setWindowTitle(s);
    });
    connect(m_source, &FileViewerSource::fileDialogRequested, this, &QmlFileViewer::onFileDialogRequested);
    connect(e, &QQmlEngine::warnings, this, &QmlFileViewer::onQmlWarnings);
}

void QmlFileViewer::onQmlWarnings(const QList<QQmlError> &warnings)
{
    for(const QQmlError& e: warnings)
    {
        qWarning() << "QML WARNING in " << e.url() << "." <<e.line() << "." << e.column() << e.toString();
    }
}

void QmlFileViewer::onFileDialogRequested()
{
    QFileDialog dialog(this, tr("Open File"));
    dialog.setOption(QFileDialog::Option::ReadOnly, true);
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void QmlFileViewer::exec()
{
    rootContext()->setContextProperty("fvsource", m_source);
    setSource(rootQml);
    showMaximized();
}

bool QmlFileViewer::loadFile(const QString& path)
{
    bool bret = false;
    do
    {
        if(path.isEmpty())
        {
            showError("empty path");
            break;
        }
        if(!QFile::exists(path))
        {
            showError(QString("file %1 is not exists").arg(path));
            break;
        }


        m_source->setCurrentPath(path);
        bret = true;
    }
    while(false);
    return bret;
}

void QmlFileViewer::showError(const QString& msg)
{
    QErrorMessage errorMessage;
    errorMessage.showMessage(msg);
    errorMessage.exec();
}

void QmlFileViewer::keyReleaseEvent(QKeyEvent *e)
{
    if(m_source == nullptr)
    {
        return;
    }
    switch(e->key())
    {
    case Qt::Key_Left:
    case Qt::Key_A:
    {
        m_source->prev();
        break;
    }
    case Qt::Key_Right:
    case Qt::Key_D:
    {
        m_source->next();
        break;
    }

    }
}
