#ifndef BERG_PROGRESS_BAR_H
#define BERG_PROGRESS_BAR_H

#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>

namespace BergGUI {

class ProgressBar : public QWidget {
    Q_OBJECT

public:
    ProgressBar(QWidget *parent = nullptr);
    ~ProgressBar();

    void setProgress(int value);
    void setLabelText(const QString &text);

private:
    QProgressBar *progressBar;
    QLabel *label;
};

} // namespace BergGUI

#endif // BERG_PROGRESS_BAR_H
