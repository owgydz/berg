#include "project_manager.h"
#include <QMessageBox>
#include <QThread>

namespace BergGUI {

ProjectManager::ProjectManager(QObject *parent)
    : QObject(parent), buildingInProgress(false), buildWindow(nullptr), targetSelector(nullptr) {
}

ProjectManager::~ProjectManager() {
    delete buildWindow;
    delete targetSelector;
}

void ProjectManager::loadProject(const QString &projectFile) {
    // Load the project file (stub for now)
    // In a real implementation, you'd parse the project file to populate build targets
    // For now, we'll simulate loading targets
    buildTargets = {"compile_source1", "compile_source2", "build_docs", "run_tests"};
}

void ProjectManager::addBuildTarget(const QString &target) {
    if (!buildTargets.contains(target)) {
        buildTargets.append(target);
    }
}

void ProjectManager::removeBuildTarget(const QString &target) {
    buildTargets.removeAll(target);
}

QStringList ProjectManager::getAvailableTargets() const {
    return buildTargets;
}

bool ProjectManager::isBuilding() const {
    return buildingInProgress;
}

void ProjectManager::startBuild(const QString &target) {
    if (buildingInProgress) {
        QMessageBox::warning(nullptr, "Build in Progress", "A build is already in progress.");
        return;
    }

    buildingInProgress = true;

    // Show the build window
    showBuildWindow();

    // Perform the build (stubbed for now)
    QThread::sleep(1);  // Simulating build time

    // Simulate progress update
    for (int i = 0; i <= 100; i++) {
        updateBuildProgress(i);
        QThread::sleep(1); // Simulate build work
    }

    // Build complete
    buildingInProgress = false;
    emit buildCompleted();
    hideBuildWindow();
}

void ProjectManager::cancelBuild() {
    if (buildingInProgress) {
        // Simulate canceling the build
        buildingInProgress = false;
        emit buildCancelled();
        hideBuildWindow();
    }
}

void ProjectManager::showBuildWindow() {
    if (!buildWindow) {
        buildWindow = new BuildWindow();
        buildWindow->show();
    }
    buildWindow->setBuildStatus("Building...");
    buildWindow->updateProgress(0);
}

void ProjectManager::hideBuildWindow() {
    if (buildWindow) {
        buildWindow->close();
    }
}

void ProjectManager::performBuild(const QString &target) {
    // In a real implementation, you would run the build process for the selected target here
    // This would involve calling out to the Berg CLI or system commands
}

void ProjectManager::updateBuildProgress(int value) {
    if (buildWindow) {
        buildWindow->updateProgress(value);
        buildWindow->appendLog(QString("Building... %1%").arg(value));
    }
}

} // namespace BergGUI
