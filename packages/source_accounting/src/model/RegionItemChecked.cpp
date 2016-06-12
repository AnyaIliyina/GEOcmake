#include "RegionItem.h"
#include "RegionItemChecked.h"
#include "SiteRegion.h"



#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase> 
#include <QSqlQuery>

QMap<int, RegionItemChecked*> RegionItemChecked::map;


QVariant RegionItemChecked::data(int column, int role) const
{
	if (role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::ToolTipRole)
	{
		/*if (column == 0)
			return QVariant();*/
		if (column == 0)
			return m_name;
		if (column == 1)
			return m_id;
		if (column == 2)
			return m_comment;		
	}

	if (role == Qt::UserRole)
		return m_id;

	if (role == Qt::CheckStateRole)
		if (column == 0)
			return m_checked;

	return QVariant();
};


bool RegionItemChecked::isCheckable() const
{
	return true;
}


int RegionItemChecked::columnCount() const {
	return 3;
};


RegionItemChecked::~RegionItemChecked()
{
}

bool RegionItemChecked::setData(int column, const QVariant& value, int role)
{
	if (value.isNull() || value.toString().isEmpty())
		return false;
	if (role == Qt::CheckStateRole || Qt::EditRole)		//  Qt::CheckStateRole
	{
		m_checked = (Qt::CheckState)value.toInt();
		checkChildren(this, m_checked);
		auto parent = dynamic_cast<RegionItemChecked*>(m_parent);
			while (parent->update()) {
				parent = dynamic_cast<RegionItemChecked*>(parent->m_parent);
					}
		return true;
	}
}


RegionItemChecked::RegionItemChecked() : RegionItem()
{
	m_checked = Qt::Unchecked;
	m_old_checked = Qt::Unchecked;
}

QMap<int, RegionItemChecked*> RegionItemChecked::getMap()
{
	return map;
}

void RegionItemChecked::setChecked(int checked)
{
	m_checked = checked;
	m_old_checked = checked;

}


RegionItemChecked* RegionItemChecked::rootItem() {
	auto parent = dynamic_cast<RegionItemChecked*>(m_parent);
	if (parent->id == -1)
		return parent;
	else
		return parent->rootItem();
};

int RegionItemChecked::checkState()
{
	return m_checked;
}

void RegionItemChecked::uncheckAll()
{
	checkChildren(rootItem(), false);
}

bool RegionItemChecked::update()
{
	if (this->id == -1)						// root item
		return false;
	if (!this->hasChildren())
		return false;
	int old = m_checked;
	m_checked = Qt::Unchecked;
	int counter_checkedChild = 0;
	for (int i = 0; i < this->m_children.count(); i++)
	{
		auto child = dynamic_cast<RegionItemChecked*>(this->m_children.at(i));
		if (child->m_checked == Qt::Checked)
			counter_checkedChild++;
	}
	
	if (counter_checkedChild > 0)
		m_checked = (counter_checkedChild == this->m_children.count()) ? Qt::Checked : Qt::PartiallyChecked;
	qDebug() << "update result: " << (old != m_checked);
	return old != m_checked;
}

//QList<RegionItemChecked*> RegionItemChecked::children()
//{
//	QList<RegionItemChecked*> list;
//	list << this->children();
//	return list;
//}

void RegionItemChecked::checkChildren(RegionItemChecked * parent, int newCheckState)
{
	parent->m_checked = newCheckState;
	if (parent->hasChildren())
	{
		for (int i = 0; i < parent->m_children.count(); i++)
		{
			auto child = dynamic_cast<RegionItemChecked*>(parent->m_children.at(i));
			checkChildren(child, newCheckState);
		}
	}
}


QVariant RegionItemChecked::headerData(int section, int role) const {
	return QVariant();
};

QList<BaseItem*> RegionItemChecked::loadItemsFromDb(QVariant id)
{
	qDebug() << "loadItemsFromDb RegionItemsChecked";
	map.clear();

	QList<BaseItem*> list;
	QSqlDatabase db = Database::database();
	QSqlQuery query(db);
	if (!query.exec(
		"WITH RECURSIVE tree(id, name, comment, parent_id, depth) AS \
		(\
			SELECT id, name, comment, 0 AS parent_id, 1 AS depth \
			 FROM regions \
				WHERE parent_id IS 0 \
			UNION ALL\
			SELECT r.id, r.name, r.comment, r.parent_id, tr.depth+1 AS depth\
			 FROM regions r, tree tr\
				WHERE r.parent_id = tr.id\
		)\
		SELECT * from tree ORDER BY tree.parent_id ASC, tree.name ASC  limit 1000"))
		qDebug() << "RegionItem::loadItemsFromDb() error:" << query.lastError().text();

	while (query.next())
	{
		RegionItemChecked* r_item = new RegionItemChecked();
		r_item->m_id = query.value(0).toInt();			// id   
		r_item->m_name = query.value(1).toString(); 	// name 
		//r_item->m_checked = false;												
		r_item->m_comment = query.value(2).toString(); 	// comment   
		int parent_id = query.value(3).toInt(); 		// parent_id  
		if (parent_id == 0)
			list << r_item;
		else {
			if (map.contains(parent_id)) {
				auto parent = map[parent_id];
				parent->appendChild(r_item);
			}
		}
		map.insert(r_item->m_id, r_item);
	}
	return list;
};


bool RegionItemChecked::save()
{
	return m_checked != m_old_checked;
};