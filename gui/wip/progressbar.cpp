#include "progressbar.h"
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>

namespace BergGUI {

ProgressBar::ProgressBar(QWidget *parent)
    : QWidget(parent), progressBar(new QProgressBar(this)), label(new QLabel(this)) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    
    label->setText("Build Progress");
    layout->addWidget(label);
    
    progressBar->setRange(0, 100);  // 0-100% progress
    layout->addWidget(progressBar);
    
    setLayout(layout);
    setWindowTitle("Build Progress");
    resize(300, 100);
}

ProgressBar::~ProgressBar() {
    delete progressBar;
    delete label;
}

void ProgressBar::setProgress(int value) {
    progressBar->setValue(value);
}

void ProgressBar::setLabelText(const QString &text) {
    label->setText(text);
}

} // namespace BergGUI
