#include "main_form.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TMainForm w;
    w.show();
    return a.exec();
}
