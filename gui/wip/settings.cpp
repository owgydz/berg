#include "settings.h"

namespace BergGUI {

Settings::Settings(QObject *parent)
    : QObject(parent), settings(new QSettings("BergStudio", "BergProject", this)) {
    loadSettings();  // Load settings on initialization
}

Settings::~Settings() {
    saveSettings();  // Save settings on destruction
}

void Settings::loadSettings() {
    buildPath = settings->value("buildPath", "").toString();
    projectPath = settings->value("projectPath", "").toString();
}

void Settings::saveSettings() {
    settings->setValue("buildPath", buildPath);
    settings->setValue("projectPath", projectPath);
}

QString Settings::getBuildPath() const {
    return buildPath;
}

void Settings::setBuildPath(const QString &path) {
    buildPath = path;
    saveSettings();  // Save setting immediately
}

QString Settings::getProjectPath() const {
    return projectPath;
}

void Settings::setProjectPath(const QString &path) {
    projectPath = path;
    saveSettings();  // Save setting immediately
}

} // namespace BergGUI
