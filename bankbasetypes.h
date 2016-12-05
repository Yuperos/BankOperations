#ifndef BANKBASETYPES_H
#define BANKBASETYPES_H

#include <iostream>

#include <QString>
#include <QPair>

enum OutType{
   OT_Public = true,
   OT_Private = false,
   };

class BankClient {
public:
   QString name;
   union {
      quint8 accountNumberParts[4];
      quint32 accountNumber;
   };

   BankClient(){}
   BankClient(const BankClient &obj);
   BankClient(QString nName, quint32 nAccountNumber);

   BankClient fromQPair(QPair<QString,quint32> pair);
   QString toString(bool fullNumber);

   quint8 operator() (int i);

   friend BankClient operator +(const BankClient &l,const BankClient &r);
   friend BankClient operator -(const BankClient &l,const BankClient &r);
   friend BankClient operator *(const BankClient &l,const BankClient &r);
   friend BankClient operator /(const BankClient &l,const BankClient &r);

   friend BankClient operator |(const BankClient &l,const BankClient &r);
   friend BankClient operator &(const BankClient &l,const BankClient &r);
   friend BankClient operator ^(const BankClient &l,const BankClient &r);

   friend BankClient operator ++(BankClient &right);
   friend BankClient operator --(BankClient &right);
   friend BankClient operator ++(BankClient &right, int);
   friend BankClient operator --(BankClient &right, int);

   friend bool operator &&(const BankClient &l,const BankClient &r);
   friend bool operator ||(const BankClient &l,const BankClient &r);
   friend bool operator !(const BankClient &right);

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

