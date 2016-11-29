#include "taxedbankoperation.h"
#include <QDataStream>

void TaxedBankOperation::setTaxeRate(double value)
{
   taxeRate = (value>0) ? value : taxeRate;
   }

QDataStream &operator <<(QDataStream &stream, const TaxedBankOperation &data)
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

TaxedBankOperation::TaxedBankOperation()
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
    out.append(QString("Номер операции: %1\n").arg(id));
    out.append(QString("Дата: %1 Время: %2\n").arg(dateTime.date().toString()).arg(dateTime.time().toString()));
    temp.clear();
    if(isNegativeAmount())
       temp.append("Произведен перевод");
    else
       temp.append("Выставлен счёт");
    out.append(QString("%1 на сумму: %2\n").arg(temp).arg(amount.sum));
    out.append(QString("От: %1 Счёт *** *** *** %2\n")
               .arg(sender.name)
               .arg(QString::number(sender.accountNumberParts[0])));
    out.append(QString("Для: %1 Счёт *** *** *** %2\n")
               .arg(reciever.name)
               .arg(QString::number(reciever.accountNumberParts[0])));
    out.append(QString("Получатель заплатит %1  с учётом налога %2\n")
               .arg(QString::number(fabs(getRecievedAmount())))
               .arg(QString::number(taxeRate,3,3)));

    return out;
}
