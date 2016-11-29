#ifndef BANKBASETYPES_H
#define BANKBASETYPES_H

#include <iostream>

#include <QString>
#include <QPair>

enum OutType{
   OT_Public = true,
   OT_Private = false,
   };

struct BankClient {
   QString name;
   union {
      quint8 accountNumberParts[4];
      quint32 accountNumber;
   };
   BankClient fromQPair(QPair<QString,quint32> pair){
      name = pair.first;
      accountNumber = pair.second;
      return *this;
      }
   QString toString(){
      return QString("%1: %2 %3 %4 %5")
            .arg(name)
            .arg(QString::number(accountNumberParts[0]))
            .arg(QString::number(accountNumberParts[1]))
            .arg(QString::number(accountNumberParts[2]))
            .arg(QString::number(accountNumberParts[3])); }
};

QDataStream &operator <<(QDataStream &stream, const BankClient &data);
QDataStream &operator >>(QDataStream &stream, BankClient &data);


//только ради точного совпадения с условием расход/доход (всм расход это или доход)
struct Amount{
   union {
      qint32 full;
      struct{
         quint32 sum :31;
         bool isNegative :1;
      };
   };
};



#endif // BANKBASETYPES_H


