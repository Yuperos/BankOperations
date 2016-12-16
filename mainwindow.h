#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QMap>

#include "bankoperation.h"
#include "tree.h"
#include "myclienttablemodel.h"
#include "datagenerator.h"

class MyClientTableModel;

namespace Ui {
   class MainWindow;
   }

typedef QPair<QList<QString>, QList<QString>> FullNameParts;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   BankOperation* editOP;
   DataGenerator dg;
   FullNameParts ClientsForGeneration;
   Tree<BankOperation*>  bankOperations;
   MyClientTableModel* MyModel;
   QMap<QString, uint32_t> clients;

   volatile bool threads[3];

   void threadAppend();
   void threadDelete();
   void threadShow();

   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private:
   Ui::MainWindow *ui;
   BankOperation* buildOperation(bool isCounted = true);


private slots:
   void clientApplied();
   void appendBankOperation();

   void generateClient();
   void generateOperation();

   void showTree();
   void findNode();
   void applyChanges();

   void openFile();
   void saveFile();
   void on_TV_Clients_doubleClicked(const QModelIndex &index);


   void startThreadAppend() { threads[0]=true;  }
   void startThreadDelete() { threads[1]=true;  }
   void startThreadShow()   { threads[2]=true;   }
   void stopThreadAppend()  { threads[0]=false;  }
   void stopThreadDelete()  { threads[1]=false; }
   void stopThreadShow()    { threads[2]=false; }
   void stopAllThreads() {for(int i=0;i<3; i++) threads[i] = false; }

   };

#endif // MAINWINDOW_H
