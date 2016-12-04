#ifndef TAXEDBANKOPERATION_H
#define TAXEDBANKOPERATION_H

#include "bankoperation.h"

class TaxedBankOperation : public BankOperation
{
    double  taxeRate;
public:
    TaxedBankOperation();
    TaxedBankOperation(bool increaseGlobalIDCount):BankOperation(increaseGlobalIDCount){}

    int32_t getSendedAmount() const override;
    int32_t getRecievedAmount() const override;
    QString toString(bool show = false) override;
    void setTaxeRate(double value) override;
    double getTaxeRate()const override;


    friend QDataStream &operator <<(QDataStream &stream, const TaxedBankOperation &data);
    friend QDataStream &operator >>(QDataStream &stream, TaxedBankOperation &data);

    TaxedBankOperation operator =(const TaxedBankOperation &right);
};

#endif // TAXEDBANKOPERATION_H
