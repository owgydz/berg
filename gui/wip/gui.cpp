#include "gui.h"
#include "mainwindow.h"
#include "buildwindow.h"
#include "tarsel.h"
#include "logwindow.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Set application-wide settings like font, style, etc.
    QApplication::setStyle("Fusion");
    QApplication::setPalette(QApplication::style()->standardPalette());

    // Main window that will display buttons and interact with other windows
    BergGUI::MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

