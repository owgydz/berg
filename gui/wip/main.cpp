#include "gui.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    BergGUI::MainWindow window;
    window.show();

    return app.exec();
}
