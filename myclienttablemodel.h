#ifndef MYCLIENTTABLEMODEL_H
#define MYCLIENTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QHostAddress>
#include <QStringList>
#include "mainwindow.h"

class MyClientTableModel : public QAbstractTableModel
{
public:
   QStringList keys;
   QMap<QString, uint32_t>* ptrToMap;

   MyClientTableModel(QMap<QString, uint32_t>* map );

   int rowCount(const QModelIndex &parent) const;
   int columnCount(const QModelIndex &parent) const;
   QVariant data(const QModelIndex &index, int role) const;
   void updateKeys(const QStringList &value);

};

#endif // MYCLIENTTABLEMODEL_H
