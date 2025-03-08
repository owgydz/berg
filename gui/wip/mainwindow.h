#ifndef BERG_MAIN_WINDOW_H
#define BERG_MAIN_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStringList>
#include "projectmanager.h"

namespace BergGUI {

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadProjectClicked();
    void onBuildClicked();
    void onSelectTargetClicked();

private:
    void initUI();
    ProjectManager *projectManager;
    QPushButton *buildButton;
    QPushButton *selectTargetButton;
    QLabel *statusLabel;
};

} // namespace BergGUI

#endif // BERG_MAIN_WINDOW_H
