#ifndef BERG_LOGWINDOW_H
#define BERG_LOGWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

namespace BergGUI {

class LogWindow : public QWidget {
    Q_OBJECT

public:
    explicit LogWindow(QWidget *parent = nullptr);
    ~LogWindow();

    // Adds a log message to the window.
    void addLogMessage(const QString &message);

    // Clears the log window.
    void clearLog();

private:
    QTextEdit *logTextEdit;
    QPushButton *clearButton;
};

} // namespace BergGUI

#endif // BERG_LOGWINDOW_H
