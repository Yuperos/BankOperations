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
   BankClient fromQPair(QPair<QString,quint32> pair);
   QString toString(bool fullNumber);
};

QDataStream &operator <<(QDataStream &stream, const BankClient &data);
QDataStream &operator >>(QDataStream &stream, BankClient &data);


//структура только ради точного совпадения с условием расход/доход
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

