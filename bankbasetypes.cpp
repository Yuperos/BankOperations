#include "bankbasetypes.h"

BankClient BankClient::fromQPair(QPair<QString, quint32> pair){
   name = pair.first;
   accountNumber = pair.second;
   return *this;
   }

QString BankClient::toString(bool fullNumber){
   return (fullNumber)?
            QString("От: %1 Счёт %2 %3 %4 %5\n")
            .arg(name)
            .arg(QString::number(accountNumberParts[3]))
         .arg(QString::number(accountNumberParts[2]))
         .arg(QString::number(accountNumberParts[1]))
         .arg(QString::number(accountNumberParts[0]))
         :
      QString("От: %1 Счёт *** *** *** %2\n")
            .arg(name)
            .arg(QString::number(accountNumberParts[0]));
      }
