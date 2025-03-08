#ifndef BERG_TARGET_SELECTOR_H
#define BERG_TARGET_SELECTOR_H

#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include <QPushButton>
#include <QVBoxLayout>

namespace BergGUI {

class TargetSelector : public QWidget {
    Q_OBJECT

public:
    TargetSelector(QWidget *parent = nullptr);
    ~TargetSelector();

    void setTargetList(const QStringList &targets);
    QString getSelectedTarget() const;

private:
    QListView *listView;
    QStringListModel *listModel;
    QPushButton *selectButton;

    void initUI();
};

} // namespace BergGUI

#endif // BERG_TARGET_SELECTOR_H
