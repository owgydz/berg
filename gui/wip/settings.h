#ifndef BERG_SETTINGS_H
#define BERG_SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QString>

namespace BergGUI {

class Settings : public QObject {
    Q_OBJECT

public:
    explicit Settings(QObject *parent = nullptr);
    ~Settings();

    void loadSettings();
    void saveSettings();

    QString getBuildPath() const;
    void setBuildPath(const QString &path);

    QString getProjectPath() const;
    void setProjectPath(const QString &path);

private:
    QSettings *settings;
    QString buildPath;
    QString projectPath;
};

} // namespace BergGUI

#endif // BERG_SETTINGS_H
