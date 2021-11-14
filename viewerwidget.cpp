#include "viewerwidget.h"
#include "ui_viewerwidget.h"
#include <QFile>
#include <QPixmap>
#include <QDebug>
#include <QErrorMessage>

ViewerWidget::ViewerWidget(QWidget *parent) noexcept
    : QWidget(parent)
    , ui(new Ui::ViewerWidget)
{
    ui->setupUi(this);
}

ViewerWidget::~ViewerWidget()
{
    delete ui;
}

bool ViewerWidget::loadFile(const QString& path)
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
        QPixmap pm(path);
        if(pm.isNull())
        {
            showError(QString("cannot load %1").arg(path));
            break;
        }
        bret = true;
    }
    while(false);
    return bret;
}

void ViewerWidget::showError(const QString& msg)
{
    QErrorMessage errorMessage;
    errorMessage.showMessage(msg);
    errorMessage.exec();
}
