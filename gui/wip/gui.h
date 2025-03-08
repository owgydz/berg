#ifndef BERG_GUI_H
#define BERG_GUI_H

#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

namespace BergGUI {

class GUI : public QWidget {
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);

private:
    void initUI();
    QPushButton *buildButton;
    QLabel *statusLabel;
};

} // namespace BergGUI

#endif // BERG_GUI_H
