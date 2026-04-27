#include <QApplication>
#include "Program1Window.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Program1Window w;
    w.show();
    return app.exec();
}
