#include <QHostAddress>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <thread>
#include <windows.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bankoperation.h"
#include "taxedbankoperation.h"
#include "limits.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
   ui(new Ui::MainWindow)
   {
   ui->setupUi(this);

   MyModel = new MyClientTableModel(&clients);
   ui->TV_Clients->setModel(MyModel);

   connect(ui->PB_ClientApply, &QPushButton::clicked, this, &MainWindow::clientApplied);
   connect(ui->PB_BankOperationAppend, &QPushButton::clicked, this, &MainWindow::appendBankOperation);
   connect(ui->CB_isTaxeOperation,&QCheckBox::toggled,ui->LE_Taxe,&QLineEdit::setEnabled);
   connect(ui->A_Exit, &QAction::triggered, this, &MainWindow::close);
   connect(ui->A_OpenFile, &QAction::triggered, this, &MainWindow::openFile);
   connect(ui->A_SaveFileAs, &QAction::triggered, this,&MainWindow::saveFile);
   connect(ui->TB_Clear, &QToolButton::clicked, ui->LE_Reciever, &QLineEdit::clear);
   connect(ui->TB_Clear, &QToolButton::clicked, ui->LE_Sender, &QLineEdit::clear);
   connect(ui->PB_GenerateCL, &QPushButton::clicked, this, &MainWindow::generateClient);
   connect(ui->PB_GenerateOP, &QPushButton::clicked, this, &MainWindow::generateOperation);
   connect(ui->PB_TreeShow, &QPushButton::clicked, this, &MainWindow::showTree);
   connect(ui->PB_TreeFind, &QPushButton::clicked, this, &MainWindow::findNode);
   connect(ui->PB_ApplyChanges, &QPushButton::clicked, this, &MainWindow::applyChanges);

   connect(ui->PB_ThreadAppendStart, &QPushButton::clicked, this,&MainWindow::startThreadAppend);
   connect(ui->PB_ThreadDeleteStart, &QPushButton::clicked, this,&MainWindow::startThreadDelete);
   connect(ui->PB_ThreadShowStart, &QPushButton::clicked, this,&MainWindow::startThreadShow);

   connect(ui->PB_ThreadAppendStop, &QPushButton::clicked, this,&MainWindow::stopThreadAppend);
   connect(ui->PB_ThreadDeleteStop, &QPushButton::clicked, this,&MainWindow::stopThreadDelete);
   connect(ui->PB_ThreadShowStop, &QPushButton::clicked, this,&MainWindow::stopThreadShow);

   connect(ui->PB_ThreadStopAll, &QPushButton::clicked, this, &MainWindow::stopAllThreads);

   ui->LE_Account->setInputMask(QString("999 999 999 999;_"));
   ui->LE_Amount->setValidator( new QIntValidator(INT32_MIN, INT32_MAX, this) );

   for(int i=0; i<3;i++)
      {threads[i]=false;}

   BankOperation *bo = new BankOperation(false);
   BankOperation *tempBo = new BankOperation(false);
   TaxedBankOperation *tbo = new TaxedBankOperation(false);
   *bo = dg.genOperation(false);
   *tempBo = dg.genOperation(false);
   tbo = (TaxedBankOperation*)tempBo;
   tbo->setTaxeRate(0.13);

   *bo = sum(*bo,*tbo);
   *tbo = sum(*tbo,*tbo);
   *tbo = sum(*tbo,*bo);
   *bo = sum(*bo,*bo);


   std::thread t1(&MainWindow::threadAppend, this);
      std::thread t2(&MainWindow::threadDelete, this);
      std::thread t3(&MainWindow::threadShow, this);
   t1.detach();
      t2.detach();
      t3.detach();

   }

MainWindow::~MainWindow()
   {
   delete ui;
   }

BankOperation *MainWindow::buildOperation(bool isCounted)
   {
   BankOperation* op;
   if (ui->CB_isTaxeOperation->isChecked())
      op = new TaxedBankOperation(isCounted);
   else
      op = new BankOperation(isCounted);
   op->setTaxeRate(ui->LE_Taxe->text().toDouble()/100.);
   op->setAmount(ui->LE_Amount->text().toInt());
   op->setDateTime(ui->DTE_DateTime->dateTime());
   op->setReciever(ui->LE_Reciever->text(),clients.value(ui->LE_Reciever->text()));
   op->setSender(ui->LE_Sender->text(),clients.value(ui->LE_Sender->text()));
   return op;
   }

void MainWindow::threadAppend()
   {
   static int i =0;
   while(true){
      if (threads[0]){
         qDebug() << "thread append works" << i;
         generateOperation();
         }
      else
         qDebug() << "thread append not Works" << i++;
      Sleep(100);
      }
   Sleep(100);
   }

void MainWindow::threadDelete()
   {
   static int i =0;
   while(true){

      if (threads[1]){
         qDebug() << "thread delete works" << i++;
         bankOperations.clear();
         }
      else
         qDebug() << "thread delete not Works" << i++;
      Sleep(1000);
      }
   Sleep(1000);
   }

void MainWindow::threadShow()
   {
   static int i =0;
   while(true){
      if (threads[1]){
         qDebug() << "thread show works" << i++;
         showTree();
         }
      else
         qDebug() << "thread show not Works" << i++;
      Sleep(500);
      }
   Sleep(500);
   }

void MainWindow::clientApplied()
   {
   QString a = ui->LE_Account->text();
   a.replace(QString(" "),QString("."));
   QHostAddress tempAccount;
   int MBoxAnswer = QMessageBox::Yes;
   if (!tempAccount.setAddress(a)){
      QMessageBox::critical(nullptr,
                            tr("Некорректный номер счёта"),
                            tr("Номер счёта должен быть не более чем \"255 255 255 255\"\n"),
                            QMessageBox::Ok);
      return;
      }

   if (clients.value(ui->LE_Name->text()) != 0)
      MBoxAnswer = QMessageBox::warning(nullptr,
                                        tr("Клиент с таким именем уже существует"),
                                        tr("Заменить запись в сипске?\n"),
                                        QMessageBox::Yes | QMessageBox::No);
   if (MBoxAnswer != QMessageBox::Yes) //все кроме "Yes"
      return;

   //хитрость с тем, что QHostAddress полностью реализует нашу логику с номером счёта
   clients.insert(ui->LE_Name->text(),tempAccount.toIPv4Address());
   MyModel->updateKeys(clients.keys());
   }

void MainWindow::appendBankOperation()
   {
   BankOperation* op = buildOperation();

   bankOperations.append(op);

   ui->textBrowser->insertPlainText(op->toString(ui->CB_ShowAccountNumber->isChecked()));
   }

void MainWindow::generateClient()
   {
   auto gen = dg.genClientPair();
   clients.insert(gen.first,gen.second);
   MyModel->updateKeys(clients.keys());
   ui->TV_Clients->reset();
   ui->TV_Clients->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
   }

void MainWindow::generateOperation()
   {
   BankOperation* op = new BankOperation(dg.genOperation());
   bankOperations.append(op);

   ui->textBrowser->insertPlainText(op->toString(ui->CB_ShowAccountNumber->isChecked()));
   }

void MainWindow::showTree()
   {
   ui->textBrowser->clear();
   ui->textBrowser->setText(bankOperations.showTree(ui->CB_ShowAccountNumber->isChecked()));
   }

void MainWindow::findNode()
   {
   bool ok = false;
   int id = ui->LE_Find->text().toInt(&ok);
   if (! ok){
      ui->textBrowser->insertPlainText(QString("BadID"));
      return;
      }
   BankOperation* tempOP = new BankOperation(false);
   tempOP->setId(id);
   editOP = bankOperations.find(tempOP);
   if (editOP == nullptr){
      return;
      }
   ui->LE_Amount->setText(QString::number(editOP->getSendedAmount()));
   ui->LE_Reciever->setText(editOP->getReciever().name);
   ui->LE_Sender->setText(editOP->getSender().name);
   ui->DTE_DateTime->setDateTime(editOP->getDateTime());
   }

void MainWindow::applyChanges()
   {
   BankOperation *op = buildOperation(false);
   op->setId(editOP->getId());
   *editOP = *op;
   }


void MainWindow::openFile()
   {
   QString path;
   path = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                       tr("BankOperations (*.*, *.bop)"));
   QFile file(path);
   if(file.open(QIODevice::ReadOnly))
      {
      bankOperations.clear();
      QDataStream stream(&file);
      stream.setVersion(QDataStream::Qt_5_6);
      stream >> bankOperations;
      if (stream.status() != QDataStream::Ok)
         {
         qDebug() << "Ошибка чтения";
         }
      }
   file.close();

   showTree();
   }

void MainWindow::saveFile()
   {
   QString path;
   path = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                       tr("BankOperations (*.bop)"));
   QFile file(path);
   if(file.open(QIODevice::WriteOnly))
      {
      QDataStream stream(&file);
      stream.setVersion(QDataStream::Qt_5_6);
      stream << bankOperations;
      if (stream.status() != QDataStream::Ok)
         {
         qDebug() << "Ошибка записи";
         }
      }
   file.close();
   }


void MainWindow::on_TV_Clients_doubleClicked(const QModelIndex &index)
   {
   if (ui->LE_Sender->text().isEmpty() &&
       !ui->TV_Clients->model()->data(ui->TV_Clients->model()->index(index.row(),0)).toString().isEmpty())
      ui->LE_Sender->setText(ui->TV_Clients->model()->data(ui->TV_Clients->model()->index(index.row(),0)).toString());
   else
      if (!ui->TV_Clients->model()->data(ui->TV_Clients->model()->index(index.row(),0)).toString().isEmpty())
         ui->LE_Reciever->setText(ui->TV_Clients->model()->data(ui->TV_Clients->model()->index(index.row(),0)).toString());
   }












