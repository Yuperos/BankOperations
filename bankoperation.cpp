#include <QDataStream>
#include <QDebug>

#include "bankoperation.h"
#include "bankbasetypes.h"

uint32_t BankOperation::globalNextID = 1;

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

BankOperation BankOperation::operator=(const BankOperation &right)
   {
   if (this == &right) {
       return *this;
   }
   this->setId(right.getId());
   this->setDateTime(right.getDateTime());
   this->setAmount(right.getSendedAmount());
   this->setSender(right.getSender());
   this->setReciever(right.getReciever());
   return *this;
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
   out.append(sender.toString(show));
   out.append(reciever.toString(show));

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

quint32 BankOperation::getId() const
   {
   return id;
   }

int32_t BankOperation::getAmount() const
   {
   return amount.full;
   }

void BankOperation::setId(const quint32 &value)
   {
   id = value;
   }

quint32 BankOperation::getGlobalNextID()
   {
   return globalNextID;
   }

void BankOperation::setGlobalNextID(const quint32 &value)
   {
   globalNextID = value;
   }

BankOperation::BankOperation()
   {
   amount.full = 1;
   dateTime = QDateTime();
   id = 0;
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
   this->setId(other.getId());
   this->setDateTime(other.getDateTime());
   this->setAmount(other.getSendedAmount());
   this->setSender(other.getSender());
   this->setReciever(other.getReciever());
   }

BankOperation::~BankOperation()
   {
   }


bool operator==(const BankOperation& left, const BankOperation& right) {
   return left.id == right.id;
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








