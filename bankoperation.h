#ifndef BANKOPERATION_H
#define BANKOPERATION_H

#include <QDateTime>

#include "bankbasetypes.h"


class BankOperation
{
protected:
   static quint32 globalNextID;
   quint32 id;
   QDateTime dateTime;
   Amount amount;
   BankClient sender;
   BankClient reciever;

public:
   BankOperation();
   BankOperation(bool increaseGlobalIDCount);
   BankOperation(QDateTime nDateTime, int32_t nAmount, BankClient nSender, BankClient nReciever, bool inc = false);
   BankOperation(const BankOperation &other);

   ~BankOperation();


   QDateTime getDateTime() const;
   BankClient getSender() const;
   BankClient getReciever() const;

   virtual void setTaxeRate(double value) {Q_UNUSED(value);}
   virtual double getTaxeRate() const {return 0;}
   virtual int32_t getSendedAmount() const;
   virtual int32_t getRecievedAmount() const;
   virtual QString toString(bool show = false);

   bool isNegativeAmount() {return amount.isNegative;}

   void setAmount(int32_t nAmount);
   void setDateTime(QDateTime value);
   void setSender(const BankClient &value);
   void setSender(QString name, const uint32_t accNumber);
   void setReciever(const BankClient &value);
   void setReciever(QString name, const uint32_t accNumber);
   bool isEmpty(){return dateTime == QDateTime() || amount.full == 0;}

   BankOperation operator=(const BankOperation& right);

   friend bool operator==(const BankOperation& left, const BankOperation& right);
   friend bool operator>(const BankOperation& left, const BankOperation& right);
   friend bool operator<(const BankOperation& left, const BankOperation& right);
   friend QDataStream &operator <<(QDataStream &stream,  const BankOperation &data);
   friend QDataStream &operator >>(QDataStream &stream, BankOperation &data);
   quint32 getId() const;
   void setId(const quint32 &value);
   };



#endif // BANKOPERATION_H
