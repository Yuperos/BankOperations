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


   virtual void setTaxeRate(double value) {Q_UNUSED(value);}
   virtual double getTaxeRate() const {return 0;}

   virtual quint32 getId() const;
   virtual int32_t getAmount() const;
   virtual int32_t getSendedAmount() const;
   virtual int32_t getRecievedAmount() const;
   virtual QString toString(bool show = false);
   virtual QDateTime getDateTime() const;
   virtual BankClient getSender() const;
   virtual BankClient getReciever() const;

   bool isNegativeAmount() {return amount.isNegative;}

   virtual void setId(const quint32 &value);
   virtual void setAmount(int32_t nAmount);
   virtual void setDateTime(QDateTime value);
   virtual void setSender(const BankClient &value);
   virtual void setSender(QString name, const uint32_t accNumber);
   virtual void setReciever(const BankClient &value);
   virtual void setReciever(QString name, const uint32_t accNumber);

   bool isEmpty(){return dateTime == QDateTime() || amount.full == 0;}

   BankOperation operator=(const BankOperation& right);

   friend bool operator==(const BankOperation& left, const BankOperation& right);
   friend bool operator>(const BankOperation& left, const BankOperation& right);
   friend bool operator<(const BankOperation& left, const BankOperation& right);
   friend QDataStream &operator <<(QDataStream &stream,  const BankOperation &data);
   friend QDataStream &operator >>(QDataStream &stream, BankOperation &data);


   static quint32 getGlobalNextID();
   static void setGlobalNextID(const quint32 &value);
   };

template <class L, class R>
L sum(L left, R right){
   left.setId(left.getId() + right.getId());
   left.setAmount(left.getAmount() + right.getAmount());
   left.setSender(left.getSender() + right.getSender());
   left.setReciever(left.getReciever() + right.getReciever());
   //date time складывать не будем.
   left.setTaxeRate(left.getTaxeRate() + right.getTaxeRate());
   return left;
   }



#endif // BANKOPERATION_H
