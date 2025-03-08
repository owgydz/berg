#ifndef BERG_PROJECT_MANAGER_H
#define BERG_PROJECT_MANAGER_H

#include <QString>
#include <QStringList>
#include <QObject>
#include "buildwindow.h"
#include "tarsel.h"

namespace BergGUI {

class ProjectManager : public QObject {
    Q_OBJECT

public:
    ProjectManager(QObject *parent = nullptr);
    ~ProjectManager();

    void loadProject(const QString &projectFile);
    void addBuildTarget(const QString &target);
    void removeBuildTarget(const QString &target);
    void startBuild(const QString &target);
    void cancelBuild();

    QStringList getAvailableTargets() const;
    bool isBuilding() const;

signals:
    void buildStarted();
    void buildCompleted();
    void buildCancelled();

private:
    bool buildingInProgress;
    QStringList buildTargets;
    BuildWindow *buildWindow;
    TargetSelector *targetSelector;
    
    void showBuildWindow();
    void hideBuildWindow();
    void performBuild(const QString &target);
    void updateBuildProgress(int value);
};

} // namespace BergGUI

#endif // BERG_PROJECT_MANAGER_H
