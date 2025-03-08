#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

namespace BergGUI {

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    SettingsDialog(Settings *settings, QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void saveSettings();

private:
    QLineEdit *buildPathEdit;
    QLineEdit *projectPathEdit;
    Settings *settings;
};

} // namespace BergGUI
