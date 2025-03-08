#include "settings_dialog.h"
#include "settings.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>

namespace BergGUI {

SettingsDialog::SettingsDialog(Settings *settings, QWidget *parent)
    : QDialog(parent), settings(settings) {
    setWindowTitle("Settings");
    setModal(true);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *buildPathLabel = new QLabel("Build Path:", this);
    layout->addWidget(buildPathLabel);
    buildPathEdit = new QLineEdit(this);
    buildPathEdit->setText(settings->getBuildPath());
    layout->addWidget(buildPathEdit);

    QLabel *projectPathLabel = new QLabel("Project Path:", this);
    layout->addWidget(projectPathLabel);
    projectPathEdit = new QLineEdit(this);
    projectPathEdit->setText(settings->getProjectPath());
    layout->addWidget(projectPathEdit);

    QPushButton *saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::clicked, this, &SettingsDialog::saveSettings);
    layout->addWidget(saveButton);

    setLayout(layout);
}

SettingsDialog::~SettingsDialog() {
    // Destructor cleanup
}

void SettingsDialog::saveSettings() {
    settings->setBuildPath(buildPathEdit->text());
    settings->setProjectPath(projectPathEdit->text());
    accept();  // Close the dialog
}

} // namespace BergGUI
