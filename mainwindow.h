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

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   BankOperation* editOP;
   DataGenerator dg;
   QList<QPair<QString,QString>> ClientsForGeneration;
   Tree<BankOperation> bankOperations;
   MyClientTableModel* MyModel;
   QMap<QString, uint32_t> clients;

   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private:
   Ui::MainWindow *ui;

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
   };

#endif // MAINWINDOW_H
