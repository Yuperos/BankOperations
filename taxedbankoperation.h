#ifndef TAXEDBANKOPERATION_H
#define TAXEDBANKOPERATION_H

#include "bankoperation.h"

class TaxedBankOperation : public BankOperation
{
    double  taxeRate;
public:
    TaxedBankOperation();
    TaxedBankOperation(bool increaseGlobalIDCount):BankOperation(increaseGlobalIDCount){}

    void setTaxeRate(double value);
    int32_t getSendedAmount() const override;
    int32_t getRecievedAmount() const override;
    double getTaxeRate() const;

    QString toString(bool show = false) override;

    friend QDataStream &operator <<(QDataStream &stream, const TaxedBankOperation &data);
    friend QDataStream &operator >>(QDataStream &stream, TaxedBankOperation &data);

    TaxedBankOperation operator =(const TaxedBankOperation &right);



   };

#endif // TAXEDBANKOPERATION_H
