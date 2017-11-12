#ifndef EULER_H
#define EULER_H

#include <QMainWindow>

namespace Ui {
class Euler;
}

class Euler : public QMainWindow
{
    Q_OBJECT

public:
    explicit Euler(QWidget *parent = 0);
    ~Euler();
    double ecuacion(double x);//se declaran la funcion y su derivada
                              //the function and its derivative are declared
    double ecuacion2(double x);
private:
    Ui::Euler *ui;
private slots:
    void calcular();//se definen las funciones que se utilizaran en el programa
                    //define the functions that will be used in the program
    void borrar();
    void Salir();
};

#endif // EULER_H
