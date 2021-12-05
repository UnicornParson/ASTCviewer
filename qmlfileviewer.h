#ifndef QMLFILEVIEWER_H
#define QMLFILEVIEWER_H

#include <QQuickItem>
#include <QQuickWidget>
#include <QQuickImageProvider>
#include <QSGTextureProvider>
#include "fileviewersource.h"
#include <QQmlError>
class CustomImageProvider : public QQuickImageProvider
{
public:
    CustomImageProvider() : QQuickImageProvider(QQuickImageProvider::Texture){}
    ~CustomImageProvider() {}
};

class QmlFileViewer : public QQuickWidget
{
    Q_OBJECT
public:
    explicit QmlFileViewer(QWidget *parent = nullptr) noexcept;
    bool loadFile(const QString& path);
    void exec();

private slots:
    void onFileDialogRequested();
    void onQmlWarnings(const QList<QQmlError> &warnings);

private:
    void keyReleaseEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
    void showError(const QString& msg);
    FileViewerSource* m_source;
    CustomImageProvider m_imgProvider;
};

#endif // QMLFILEVIEWER_H
