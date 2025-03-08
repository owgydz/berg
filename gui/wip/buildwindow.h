#ifndef BERG_BUILD_WINDOW_H
#define BERG_BUILD_WINDOW_H

#include <QWidget>
#include <QProgressBar>
#include <QTextEdit>
#include <QVBoxLayout>

namespace BergGUI {

class BuildWindow : public QWidget {
    Q_OBJECT

public:
    BuildWindow(QWidget *parent = nullptr);
    ~BuildWindow();

    void updateProgress(int value);
    void appendLog(const QString &logMessage);
    void setBuildStatus(const QString &status);

private:
    QProgressBar *progressBar;
    QTextEdit *logOutput;
    QLabel *statusLabel;

    void initUI();
};

} // namespace BergGUI

#endif // BERG_BUILD_WINDOW_H
