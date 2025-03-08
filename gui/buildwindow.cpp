#include "buildwindow.h"
#include <QProgressBar>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>

namespace BergGUI {

BuildWindow::BuildWindow(QWidget *parent) 
    : QWidget(parent) {
    initUI();
}

BuildWindow::~BuildWindow() {}

void BuildWindow::initUI() {
    // Create a vertical layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create a progress bar and log output area
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    logOutput = new QTextEdit(this);
    logOutput->setReadOnly(true);

    statusLabel = new QLabel("Build Status: Idle", this);

    // Add the components to the layout
    layout->addWidget(progressBar);
    layout->addWidget(statusLabel);
    layout->addWidget(logOutput);

    setLayout(layout);
    setWindowTitle("Build Progress");
    resize(400, 300);
}

void BuildWindow::updateProgress(int value) {
    progressBar->setValue(value);
}

void BuildWindow::appendLog(const QString &logMessage) {
    logOutput->append(logMessage);
}

void BuildWindow::setBuildStatus(const QString &status) {
    statusLabel->setText("Build Status: " + status);
}

} // namespace BergGUI
