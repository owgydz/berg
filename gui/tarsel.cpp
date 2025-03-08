#include "target_selector.h"
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

namespace BergGUI {

TargetSelector::TargetSelector(QWidget *parent) 
    : QWidget(parent), listView(nullptr), listModel(nullptr) {
    initUI();
}

TargetSelector::~TargetSelector() {}

void TargetSelector::initUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    listView = new QListView(this);
    listModel = new QStringListModel(this);
    listView->setModel(listModel);

    selectButton = new QPushButton("Select Target", this);
    connect(selectButton, &QPushButton::clicked, this, &TargetSelector::accept);

    layout->addWidget(listView);
    layout->addWidget(selectButton);

    setLayout(layout);
    setWindowTitle("Select Build Target");
    resize(300, 200);
}

void TargetSelector::setTargetList(const QStringList &targets) {
    listModel->setStringList(targets);
}

QString TargetSelector::getSelectedTarget() const {
    QModelIndex index = listView->currentIndex();
    return listModel->data(index, Qt::DisplayRole).toString();
}

} // namespace BergGUI
