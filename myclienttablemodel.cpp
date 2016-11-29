#include "myclienttablemodel.h"
#include  <QDebug>

void MyClientTableModel::updateKeys(const QStringList &value)
   {
   keys = value;
   }

MyClientTableModel::MyClientTableModel(QMap<QString, uint32_t> *map): QAbstractTableModel(), ptrToMap(map){}

int MyClientTableModel::rowCount(const QModelIndex &parent) const
   {
   Q_UNUSED(parent)
   return 15;
   }

int MyClientTableModel::columnCount(const QModelIndex &parent) const
   {
   Q_UNUSED(parent)
   return 2;
   }

QVariant MyClientTableModel::data(const QModelIndex &index, int role) const
   {
   QString rw;
   if (role == Qt::DisplayRole && keys.count()>index.row())
      {
      switch(index.column())
         {
         case 0:
            {
            rw.append(keys.at(index.row()));
            } break;
         case 1:
            {
            uint32_t accNumber = ptrToMap->value(keys.at(index.row()));
            rw.append(QHostAddress(accNumber).toString());
            } break;
         default: break;
         }
      }
   return rw;
   }
