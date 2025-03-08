#include "logwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

namespace BergGUI {

LogWindow::LogWindow(QWidget *parent)
    : QWidget(parent) {

    setWindowTitle("Build Log");
    setFixedSize(600, 400);  // Set a fixed size for the window

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create a scrollable QTextEdit for logs
    logTextEdit = new QTextEdit(this);
    logTextEdit->setReadOnly(true);  // Make it read-only so the user cannot edit the log
    layout->addWidget(logTextEdit);

    // Create a Clear button
    clearButton = new QPushButton("Clear Log", this);
    connect(clearButton, &QPushButton::clicked, this, &LogWindow::clearLog);
    layout->addWidget(clearButton);

    setLayout(layout);
}

LogWindow::~LogWindow() {
    // Destructor cleanup (if needed)
}

void LogWindow::addLogMessage(const QString &message) {
    // Append the log message with a timestamp
    logTextEdit->append(message);
}

void LogWindow::clearLog() {
    logTextEdit->clear();  // Clears the text in the log window
}

} // namespace BergGUI
