/*!

	\file
	\brief Р”РµР»РµРіР°С‚ ComboBox
	\author РљРѕР·С‹СЂРµРІР° Рћ.Рђ.
	\date РњР°Р№ 2016

*/

#pragma once

#include "Multilist.h"
#include <QItemDelegate>
#include <QList>


class ComboDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	~ComboDelegate();
	/*!
	РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ
	\param const QList<QString>& list - СЃРїРёСЃРѕРє, РґР»СЏ СѓСЃС‚Р°РЅРѕРІРєРё СЌР»РµРјРµРЅС‚РѕРІ РєРѕРјР±Рѕ-Р±РѕРєСЃРѕРІ
	*/
	ComboDelegate(const QList<QString>& list, QObject* parent = NULL);
	/*!
	РњРµС‚РѕРґ РґР»СЏ СѓСЃС‚Р°РЅРѕРІРєРё СЌР»РµРјРµРЅС‚РѕРІ РєРѕРјР±Рѕ-Р±РѕРєСЃР°
	*/
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	/*!
	РњРµС‚РѕРґ РґР»СЏ СѓСЃС‚Р°РЅРѕРІРєРё РІС‹РґРµР»РµРЅРЅС‹С… СЌР»РµРјРµРЅС‚РѕРІ
	*/
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	/*!
	РњРµС‚РѕРґ РґР»СЏ СЃРѕС…СЂР°РЅРµРЅРёСЏ РІС‹Р±СЂР°РЅРЅС‹С… СЌР»РµРјРµРЅС‚РѕРІ, РїРѕСЃР»Рµ Р·Р°РІРµСЂС€РµРЅРёСЏ СЂР°Р±РѕС‚С‹ СЃ РґРµР»РµРіР°С‚РѕРј
	*/
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
private:
	QList<QString> m_list;
	QList<int> m_listIDs;
private slots:
	void slotSetListIDs(QList<int>);
};