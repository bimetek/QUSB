#include <QCoreApplication>
#include "controller.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Controller *c = new Controller();
    a.connect(c, SIGNAL(destroyed()), SLOT(quit()));

    return a.exec();
}
