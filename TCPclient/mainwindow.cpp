#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printMessage(QString message)
{
    ui->chatDispaly->append(message);
}



void MainWindow::on_pushButtonSend_clicked()
{
    QString name = ui->nameInput->toPlainText();
    QString message = ui->messageInput->toPlainText();
    socket->write("<font color=\"Blue\">" + name.toUtf8() + "</font>: " + message.toUtf8());
    ui->messageInput->clear();
}


void MainWindow::on_pushButtonConnect_clicked()
{
    if (!connectedToHost){
        socket = new QTcpSocket;
        connect(socket,&QTcpSocket::connected,this,&MainWindow::socketConnected);
        connect(socket,&QTcpSocket::disconnected,this,&MainWindow::socketDisconnected);
        connect(socket,&QTcpSocket::readyRead,this,&MainWindow::socketReadyRead);
        socket->connectToHost("127.0.0.1",8001);
    }else{
        QString name = ui->nameInput->toPlainText();
        socket->write("<font color=\"Orange\">" + name.toUtf8() + "has left the chat room.</font>");
        socket->disconnectFromHost();
    }
}

void MainWindow::socketConnected()
{
    qDebug() << "Connected to server.";
    printMessage("<font color=\"Green\">Connected to server.</font>");
    QString name = ui->nameInput->toPlainText();
    socket->write("<font color=\"Purple\">" + name.toUtf8() + "has joined the chat room.</font>");
    ui->pushButtonConnect->setText("Disconnect");
    connectedToHost = true;
}

void MainWindow::socketDisconnected()
{
    qDebug() << "Disconnected from server.";
    printMessage("<font color=\"Red\">Disconnected fromserver.</font>");
    ui->pushButtonConnect->setText("Connect");
    connectedToHost = false;
}

void MainWindow::socketReadyRead()
{
    printMessage(socket->readAll());
}

