#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow m;
    m.showMaximized();
    m.loadEssences();

    return app.exec();
}
