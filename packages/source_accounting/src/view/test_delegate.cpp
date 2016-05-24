#include "test_delegate.h"
#include "Multilist.h"
#include "ViewSites.h"

#include <QComboBox>

TestDelegate::~TestDelegate() {
};

TestDelegate::TestDelegate(const QList<QString>& list, QObject* parent) {
	m_list = list;

};

QWidget* TestDelegate::createEditor(
	QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {

	QComboBox *cBox = new QComboBox(parent);
	//QObject::connect(cBox, SIGNAL(signalCheckedIDs(QList<int>)), this, SLOT(slotSetListIDs(QList<int>)));

	QStandardItemModel* model = new QStandardItemModel();
	for (int i = 0; i < m_list.count(); i++) {
		QStandardItem* item = new QStandardItem();
		item->setText(m_list[i]);
		item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
		item->setData(Qt::Unchecked, Qt::CheckStateRole);
		model->appendRow(item);

		//cBox->addItem(m_list[i]);
	}
	cBox->setModel(model);
	return cBox;
}
void TestDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
	QString value = index.model()->data(index).toString();
	QStringList listCheckedItems = value.split(", ");

	

	QComboBox *listWidget = static_cast<QComboBox*>(editor);
	QStandardItemModel *sModel = qobject_cast<QStandardItemModel*>(listWidget->model());
	
	for (int i = 0; i < sModel->rowCount(); i++) {
		
		if (listCheckedItems.contains(sModel->item(i)->text()))
			sModel->item(i)->setData(Qt::Checked, Qt::CheckStateRole);
	}
	

	//listWidget->setCheckedItems(listCheckedItems);

}
void TestDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
	QComboBox *listWidget = static_cast<QComboBox*>(editor);
	QStandardItemModel *sModel = qobject_cast<QStandardItemModel*>(listWidget->model());

	QStringList list;
	for (int i = 0; i < sModel->rowCount(); i++) {
		if (sModel->item(i)->checkState() == Qt::Checked) {
			list << sModel->item(i)->text();
		}
	}
	model->setData(index, list.join(", "));
	/*if (!listWidget->checkedItems().isEmpty())
	{
		model->setData(index, listWidget->checkedItems().join(", "));
	}*/

}

void TestDelegate::slotSetListIDs(QList <int> listIDs)
{
	m_listIDs = listIDs;
}
