#ifndef BERG_GUI_H
#define BERG_GUI_H

#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

namespace BergGUI {

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    QPushButton *buildButton;
    QLabel *statusLabel;
};

} // namespace BergGUI

#endif // BERG_GUI_H
