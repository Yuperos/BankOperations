#include "bankbasetypes.h"

BankClient::BankClient(const BankClient &obj)
   {
   this->name.clear();
   this->name.append(obj.name);
   }

BankClient::BankClient(QString nName, quint32 nAccountNumber)
   {
   this->name.clear();
   this->name.append(nName);
   this->accountNumber = nAccountNumber;
   }

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

quint8 BankClient::operator()(int i) {
   return accountNumberParts[3-(i%4)];}

BankClient operator +(const BankClient &l, const BankClient &r){
   return BankClient(l.name,l.accountNumber | r.accountNumber);
   }

BankClient operator -(const BankClient &l, const BankClient &r){
   return BankClient(l.name,l.accountNumber | r.accountNumber);
   }

BankClient operator *(const BankClient &l, const BankClient &r){
   return BankClient(l.name,l.accountNumber * r.accountNumber);
   }

BankClient operator /(const BankClient &l, const BankClient &r){
   return BankClient(l.name,l.accountNumber / r.accountNumber);
   }

BankClient operator |(const BankClient &l, const BankClient &r){
   return BankClient(l.name,l.accountNumber | r.accountNumber);
   }

BankClient operator &(const BankClient &l, const BankClient &r){
   return BankClient(l.name,l.accountNumber & r.accountNumber);
   }

BankClient operator ^(const BankClient &l, const BankClient &r){
   return BankClient(l.name,l.accountNumber ^ r.accountNumber);
   }

BankClient operator ++(const BankClient &bc) {
   return bc.accountNumber+=1;
   }

BankClient operator --(const BankClient &bc) {
   return bc.accountNumber-=1;
   }

BankClient operator ++(const BankClient &bc, int){
   BankClient old(bc);
   bc.accountNumber+=1;
   return old;
   }

BankClient operator --(const BankClient &bc, int){
   BankClient old(bc);
   bc.accountNumber-=1;
   return old;
   }
