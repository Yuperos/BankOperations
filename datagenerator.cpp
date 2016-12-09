#include "datagenerator.h"

DataGenerator::DataGenerator()
   {
   qsrand(QTime::currentTime().msec());
   firstNameFemale << "Маша" << "Саша" << "Оля" << "Нина" << "Варя" << "Лиза" << "Ира" << "Аня" << "Вера";
   surNameFemale << "Сидорова" << "Алексеева" << "Иванова" << "Петрова" << "Попрыгайкина" << "Разгильдяева" << "Лодырецкая";

   firstNameMale << "Саша" << "Паша" << "Коля" << "Вася" << "Дима" << "Петя" << "Дима" << "Иван" << "Ашот";
   surNameMale << "Никаковский" << "Иванов" << "Неумейко" << "Далёкий" << "Мёртвостраус" << "Бананкин" << "Редисочкин";
   }

QPair<QString, quint32> DataGenerator::genClientPair()
   {
   QString rw;
   bool isMale = qrand()%1;
   QStringList *firstName, *surName;
   if(isMale) {
      firstName = &firstNameMale;
      surName = &surNameMale;
      }
   else
      firstName = &firstNameFemale;
   surName = &surNameFemale;
   int first = qrand() % firstName->count();
   int sur = qrand() % surName->count();

   rw.append(firstName->at(first)).append(" ").append(surName->at(sur));

   return QPair<QString, quint32>(rw,(qrand()<<16)+qrand());
   }

BankClient DataGenerator::genClient()
   {
   return BankClient().fromQPair(genClientPair());
   }


BankOperation DataGenerator::genOperation(bool inc)
   {
   return BankOperation(QDateTime::currentDateTime(),qrand() % 500000, genClient(),genClient(),inc);
   }
