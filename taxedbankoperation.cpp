#include "taxedbankoperation.h"
#include <QDataStream>

void TaxedBankOperation::setTaxeRate(double value)
   {
   taxeRate = (value>0) ? value : taxeRate;
   }

double TaxedBankOperation::getTaxeRate() const
   {
   return taxeRate;
   }

QDataStream &operator <<(QDataStream &stream,  const TaxedBankOperation &data)
   {
   stream << data.id;
   stream << data.dateTime;
   stream << data.amount.full;
   stream << data.sender;
   stream << data.reciever;
   return stream;
   }

QDataStream &operator >>(QDataStream &stream, TaxedBankOperation &data)
   {
   stream >> data.id;
   stream >> data.dateTime;
   stream >> data.amount.full;
   stream >> data.sender;
   stream >> data.reciever;
   return stream;
   }


TaxedBankOperation TaxedBankOperation::operator =(const TaxedBankOperation &right)
   {
   if (this == &right)
      return *this;

   BankOperation::operator =(right);
   this->setTaxeRate(right.getTaxeRate());
   return *this;
   }

TaxedBankOperation::TaxedBankOperation():BankOperation()
   {
   taxeRate = 0.15;
   }

int32_t TaxedBankOperation::getSendedAmount() const
   {
   return BankOperation::getSendedAmount();
   }

int32_t TaxedBankOperation::getRecievedAmount() const
   {
   return amount.full + amount.sum * taxeRate;
   }

QString TaxedBankOperation::toString(bool show)
   {
   QString out, temp;
   out.append(this->BankOperation::toString(show));
   out.append(QString("Получатель заплатит %1  с учётом налога %2\n")
              .arg(QString::number(fabs(getRecievedAmount())))
              .arg(QString::number(taxeRate,3,3)));

   return out;
   }
