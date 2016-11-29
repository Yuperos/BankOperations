#include <QDataStream>
#include <QDebug>

#include "bankoperation.h"
#include "bankbasetypes.h"

uint32_t BankOperation::globalNextID = 0;

void BankOperation::setDateTime(QDateTime value) { dateTime = value; }

void BankOperation::setSender(QString name, const uint32_t accNumber)
   {
   if(name.length() >= 50 || accNumber == 0) return;
   sender.name = name;
   sender.accountNumber = accNumber;
   }
void BankOperation::setReciever(QString name, const uint32_t accNumber)
   {
   if(name.length() >= 50 || accNumber == 0) return;
   reciever.name = name;
   reciever.accountNumber = accNumber;
   }


QString BankOperation::toString(bool show)
   {
   QString out, temp;
   out.append(QString("Номер операции: %1\n").arg(id));
   out.append(QString("Дата: %1 Время: %2\n").arg(dateTime.date().toString()).arg(dateTime.time().toString()));
   temp.clear();
   if(isNegativeAmount())
      temp.append("Произведен перевод");
   else
      temp.append("Выставлен счёт");
   out.append(QString("%1 на сумму: %2\n").arg(temp).arg(amount.sum));

   if(show){
      out.append(QString("От: %1 Счёт %2 %3 %4 %5\n")
                 .arg(sender.name)
                 .arg(QString::number(sender.accountNumberParts[3]),3)
                 .arg(QString::number(sender.accountNumberParts[2]),3)
                 .arg(QString::number(sender.accountNumberParts[1]),3)
                 .arg(QString::number(sender.accountNumberParts[0]),3));
      out.append(QString("Для: %1 Счёт %2 %3 %4 %5\n")
                 .arg(reciever.name)
                 .arg(QString::number(reciever.accountNumberParts[3]),3)
                 .arg(QString::number(reciever.accountNumberParts[2]),3)
                 .arg(QString::number(reciever.accountNumberParts[1]),3)
                 .arg(QString::number(reciever.accountNumberParts[0]),3));
   } else {
      out.append(QString("От: %1 Счёт *** *** *** %2\n")
                 .arg(sender.name)
                 .arg(QString::number(sender.accountNumberParts[0])));
      out.append(QString("Для: %1 Счёт *** *** *** %2\n")
                 .arg(reciever.name)
                 .arg(QString::number(reciever.accountNumberParts[0])));
      }
   
   return out;
   }

QDateTime BankOperation::getDateTime() const { return dateTime; }
BankClient BankOperation::getSender() const { return sender; }
BankClient BankOperation::getReciever() const { return reciever; }

int32_t BankOperation::getSendedAmount() const
   {
   return amount.full;
   }

int32_t BankOperation::getRecievedAmount() const
   {
   return amount.full;
   }

void BankOperation::setAmount(int32_t nAmount)
   {
   amount.full = nAmount;
   }

void BankOperation::setSender(const BankClient &value)
   {
   sender = value;
   }

void BankOperation::setReciever(const BankClient &value)
   {
   reciever = value;
   }

BankOperation::BankOperation()
   {
   amount.full = 0;
   dateTime = QDateTime();
   id = globalNextID;
   }

BankOperation::BankOperation(bool increaseGlobalIDCount) {
   id = globalNextID;
   if (increaseGlobalIDCount) globalNextID++;
   }

BankOperation::BankOperation(QDateTime nDateTime, int32_t nAmount, BankClient nSender, BankClient nReciever,  bool inc)
   {
   this->id = globalNextID;
   if (inc) globalNextID++;

   this->setDateTime(nDateTime);
   this->setAmount(nAmount);
   this->setSender(nSender);
   this->setReciever(nReciever);
   }

BankOperation::BankOperation(const BankOperation &other)
   {
   this->setDateTime(other.getDateTime());
   this->setAmount(other.getSendedAmount());
   this->setSender(other.getSender());
   this->setReciever(other.getReciever());
   }

BankOperation::~BankOperation()
   {
   }


bool operator==(const BankOperation& left, const BankOperation& right) {
   return left.id == right.id && left.amount.full == right.amount.full;
   }

bool operator>(const BankOperation &left, const BankOperation &right)
   {
   return left.id > right.id;
   }

bool operator<(const BankOperation &left, const BankOperation &right)
   {
   return left.id < right.id;
   }

QDataStream &operator <<(QDataStream &stream,  const BankOperation &data)
   {
   stream << data.id;
   stream << data.dateTime;
   stream << data.amount.full;
   stream << data.sender;
   stream << data.reciever;
   return stream;
   }

QDataStream &operator >>(QDataStream &stream, BankOperation &data)
   {
   stream >> data.id;
   stream >> data.dateTime;
   stream >> data.amount.full;
   stream >> data.sender;
   stream >> data.reciever;
   return stream;
   }

QDataStream &operator <<(QDataStream &stream, const BankClient &data)
   {
   stream << data.accountNumber;
   stream << data.name;

   return stream;
   }

QDataStream &operator >>(QDataStream &stream, BankClient &data)
   {
   stream >> data.accountNumber;
   stream >> data.name;

   return stream;
   }








