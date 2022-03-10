#ifndef IHMCLASSROOM_H
#define IHMCLASSROOM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class IhmClassroom; }
QT_END_NAMESPACE

class IhmClassroom : public QMainWindow
{
    Q_OBJECT

public:
    IhmClassroom(QWidget *parent = nullptr);
    ~IhmClassroom();

private:
    Ui::IhmClassroom *ui;
};
#endif // IHMCLASSROOM_H
