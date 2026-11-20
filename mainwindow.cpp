#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server= new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this,&MainWindow::NuevaConexion);
    connect(ui->IniciarServidor, &QPushButton::clicked, this, &MainWindow::IniciarServidor);
    X.currentDateTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::IniciarServidor(){
    if(server->listen(QHostAddress::Any, 502)) {
        ui->debug->append("🟢 Servidor iniciado. Escuchando en el puerto 502...");
    }
}

void MainWindow::NuevaConexion(){
    QTcpSocket *cliente = server->nextPendingConnection();
    ui->debug->append(" Nuevo cliente conectado desde: " + cliente->peerAddress().toString());

    connect(cliente, &QTcpSocket::readyRead, this, &MainWindow::Lectura);
    connect(cliente, &QTcpSocket::disconnected, this, &MainWindow::Desconexion);
}

void MainWindow::Desconexion(){
    QTcpSocket *cliente = qobject_cast<QTcpSocket*>(sender());
    if (cliente) {
        ui->debug->append("Cliente desconectado.");
        cliente->deleteLater();
    }
}

void MainWindow::Lectura(){
    QTcpSocket *cliente = (QTcpSocket*)QObject::sender();
    text = cliente->readAll().trimmed();
    QString client_ip = cliente->peerAddress().toString();
    qDebug() << "[" << client_ip << "]" << text;
    ui->debug->append("[" + client_ip + "]: " + text);
    if(text == "year"){
        int dato= X.currentDateTime().date().year();
            QString texto = QString::number(dato,10);
        ui->debug->append(texto);
            cliente->write((texto + "\r\n").toUtf8());
    }
    if(text == "month"){
        int dato= X.currentDateTime().date().month();
        QString texto = QString::number(dato,10);
        ui->debug->append(texto);
        cliente->write((texto + "\r\n").toUtf8());
    }
    if(text == "day"){
        int dato= X.currentDateTime().date().day();
        QString texto = QString::number(dato,10);
        ui->debug->append(texto);
        cliente->write((texto + "\r\n").toUtf8());
    }
    if(text == "date"){
        QString texto =X.currentDateTime().date().toString();
        ui->debug->append(texto);
        cliente->write((texto + "\r\n").toUtf8());
    }
    if(text == "hour"){
            int dato= X.currentDateTime().time().hour();
            QString texto = QString::number(dato,10);
            ui->debug->append(texto);
            cliente->write((texto + "\r\n").toUtf8());
    }
    if(text == "min"){
        int dato= X.currentDateTime().time().minute();
        QString texto = QString::number(dato,10);
        ui->debug->append(texto);
        cliente->write((texto + "\r\n").toUtf8());
    }
    if(text == "sec"){
        int dato= X.currentDateTime().time().second();
        QString texto = QString::number(dato,10);
        ui->debug->append(texto);
        cliente->write((texto + "\r\n").toUtf8());
    }
    if(text == "time"){
        QString texto = X.currentDateTime().time().toString();
        ui->debug->append(texto);
        cliente->write((texto + "\r\n").toUtf8());
    }
    if(text == "datetime"){
        QString texto = X.currentDateTime().toString();
        ui->debug->append(texto);
        cliente->write((texto + "\r\n").toUtf8());
    }



}


