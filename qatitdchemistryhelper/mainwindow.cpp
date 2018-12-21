#include "mainwindow.hpp"

#include "essencetab.hpp"

#include "libchemistryhelper/wikiessencesdatagatherer.hpp"

#include <QStatusBar>
#include <QTabBar>
#include <QTabWidget>
#include <QtConcurrent/qtconcurrentrun.h>

MainWindow::MainWindow()
    : QMainWindow()
{
    m_tab_widget = new QTabWidget;
    setCentralWidget(m_tab_widget);
    // m_tab_widget->setTabsClosable()
    connect(&m_essence_watcher, &QFutureWatcher<EssenceContainer_t>::finished, [this]() {
        m_essence_tab = new EssenceTab(std::move(m_essence_watcher.result()));
        m_tab_widget->addTab(m_essence_tab, tr("Essences"));
        m_tab_widget->tabBar()->setTabButton(0, QTabBar::RightSide, nullptr);
        statusBar()->clearMessage();
    });
}

void MainWindow::loadEssences()
{
    statusBar()->showMessage(tr("loading essences data..."));
    m_essence_watcher.setFuture(QtConcurrent::run([]() { return WikiIEssencesDataGatherer().gatherData(); }));
}