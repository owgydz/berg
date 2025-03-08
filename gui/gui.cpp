#include "gui.h"
#include "target_selector.h"
#include "build_window.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

namespace BergGUI {

MainWindow::MainWindow(QWidget *parent) 
    : QWidget(parent), buildWindow(nullptr), targetSelector(nullptr) {
    initUI();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    QPushButton *selectTargetButton = new QPushButton("Select Target", this);
    connect(selectTargetButton, &QPushButton::clicked, this, &MainWindow::onSelectTargetClicked);

    buildButton = new QPushButton("Start Build", this);
    connect(buildButton, &QPushButton::clicked, this, &MainWindow::onBuildClicked);

    statusLabel = new QLabel("Status: Idle", this);

    layout->addWidget(selectTargetButton);
    layout->addWidget(buildButton);
    layout->addWidget(statusLabel);

    setLayout(layout);
    setWindowTitle("Berg Build System");
    resize(400, 200);
}

void MainWindow::onSelectTargetClicked() {
    if (!targetSelector) {
        targetSelector = new TargetSelector();
    }

    QStringList targets = {"compile_source1", "compile_source2", "build_docs", "run_tests"};
    targetSelector->setTargetList(targets);

    targetSelector->exec();

    QString selectedTarget = targetSelector->getSelectedTarget();
    statusLabel->setText("Selected target: " + selectedTarget);
}

void MainWindow::onBuildClicked() {
    if (!buildWindow) {
        buildWindow = new BuildWindow();
        buildWindow->show();
    }

    buildWindow->setBuildStatus("Building...");
    buildWindow->updateProgress(0);

    // Simulate the build process for the selected target
    for (int i = 0; i <= 100; i++) {
        buildWindow->updateProgress(i);
        buildWindow->appendLog(QString("Building... %1%").arg(i));
        QThread::sleep(1); 
    }

    buildWindow->setBuildStatus("Build Completed");
}

} // namespace BergGUI
