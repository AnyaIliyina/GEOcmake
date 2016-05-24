/*!

\file
\brief ������� ComboBox
\author �������� �.�.
\date ��� 2016

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
	�����������
	\param const QList<QString>& list - ������, ��� ��������� ��������� �����-������
	*/
	TestDelegate(const QList<QString>& list, QObject* parent = NULL);
	/*!
	����� ��� ��������� ��������� �����-�����
	*/
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	/*!
	����� ��� ��������� ���������� ���������
	*/
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	/*!
	����� ��� ���������� ��������� ���������, ����� ���������� ������ � ���������
	*/
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
private:
	QList<QString> m_list;
	QList<int> m_listIDs;
	private slots:
	void slotSetListIDs(QList<int>);
};