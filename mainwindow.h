#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    QTcpSocket cliente;
    QString text;
    QDateTime X;
public slots:
    void NuevaConexion();
    void IniciarServidor();
    void Lectura();
    void Desconexion();


private:
    Ui::MainWindow *ui;
    QTcpServer *server;

};
#endif // MAINWINDOW_H
