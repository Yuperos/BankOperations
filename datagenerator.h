#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <QStringList>
#include <random>
#include <QTime>

#include "bankoperation.h"

class DataGenerator
   {
public:
   DataGenerator();

   QStringList firstNameMale, surNameMale,firstNameFemale, surNameFemale;

   QPair<QString,quint32> genClientPair();
   BankClient genClient();
   BankOperation genOperation(bool inc = true);
   };

#endif // DATAGENERATOR_H
