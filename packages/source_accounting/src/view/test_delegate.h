/*!

\file
\brief Делегат ComboBox
\author Козырева О.А.
\date Май 2016

*/

#pragma once

#include <QItemDelegate>
#include <QList>


class TestDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	~TestDelegate();
	/*!
	Конструктор
	\param const QList<QString>& list - список, для установки элементов комбо-боксов
	*/
	TestDelegate(const QList<QString>& list, QObject* parent = NULL);
	/*!
	Метод для установки элементов комбо-бокса
	*/
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	/*!
	Метод для установки выделенных элементов
	*/
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	/*!
	Метод для сохранения выбранных элементов, после завершения работы с делегатом
	*/
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
private:
	QList<QString> m_list;
	QList<int> m_listIDs;
	private slots:
	void slotSetListIDs(QList<int>);
};