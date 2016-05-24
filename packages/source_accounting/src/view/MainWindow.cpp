#include "MainWindow.h"
#include "Site.h"
#include "ViewSites.h"
#include "ViewDepartments.h"
#include "TreeRegions.h"
#include "SiteRegion.h"
#include "DepartmentRegion.h"
#include "Database.h"
#include "Types.h"
#include <QTextEdit>
#include <QDebug>
#include <QStatusBar>
#include <QDockWidget>


MainWindow::MainWindow(QMainWindow *parent)
{
	ui = new Ui::MainWindow();
	ui->setupUi(this);
	slotConfigure();
	
	QObject::connect(tableSites, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotOpenUrl(QModelIndex)));
}


MainWindow::~MainWindow()
{
}


/*!
"РЎРѕР±РёСЂР°РµС‚" РѕСЃРЅРѕРІРЅРѕРµ РѕРєРЅРѕ РёР· РІРёРґР¶РµС‚РѕРІ
*/
void MainWindow::slotConfigure()
{	
	m_tr = new TreeRegions();
	
	QObject::connect(m_tr, SIGNAL(dataChanged()), SLOT(slotSetupRegionsModel()));
	setSearchResources();
	setResourcesView();
	setDepartamentView();
	ui->tabWidget->addTab(search, "РџРѕРёСЃРє РёСЃС‚РѕС‡РЅРёРєРѕРІ");
	ui->tabWidget->addTab(sites, "Р