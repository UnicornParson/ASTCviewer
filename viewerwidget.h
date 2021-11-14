#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ViewerWidget; }
QT_END_NAMESPACE

class ViewerWidget : public QWidget
{
    Q_OBJECT

public:
    ViewerWidget(QWidget *parent = nullptr) noexcept;
    ~ViewerWidget();
    bool loadFile(const QString& path);
private:
    Ui::ViewerWidget *ui;
    void showError(const QString& msg);
};
#endif // VIEWERWIDGET_H
