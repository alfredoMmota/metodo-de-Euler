//Metodo de Euler version 1.0
#include "euler.h"
#include "ui_euler.h"
#include "cmath"//se agregan librerias de matematica
                //Math libraries are added
#include "math.h"

Euler::Euler(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Euler)
{
    ui->setupUi(this);//se conectan los botones de la interfaz con el programa principal
                      //the buttons of the interface are connected to the main program
    connect(ui->metodo,SIGNAL(clicked()),this,SLOT(calcular()));
    connect(ui->limpiar,SIGNAL(clicked()),this,SLOT(borrar()));
    connect(ui->cerrar,SIGNAL(clicked()),this,SLOT(Salir()));
}

Euler::~Euler()
{
    delete ui;
}
double Euler::ecuacion(double x){//se definen las funciones que se ocuparan en el programa
                                 //the functions that will be occupied in the program are defined
    return ((-0.5*(pow(x,4)))+(4*(pow(x,3)))-(10*(pow(x,2)))+(8.5*x)+1);
}
double Euler::ecuacion2(double x){
    return ((-2*(pow(x,3)))+(12*(pow(x,2)))-(20*x)+8.5);
}
void Euler::calcular(){//se define lo que ara la funcion calcular
                       //you define what the function calculates
    QString val,val1;//se definen variables tipo cadena para la visualizacion
                     //string type variables are defined for visualization
    double H,LIMITE1,LIMITE2,derivada,y;//se declaran variables de tipo double
                                        //variables of type double are declared
    H=ui->h->value();//se obtinen los valores de los spinbox de la interfaz
                     //the values ​​of the interface spinboxes are obtained
    LIMITE1=ui->liminf->value();
    LIMITE2=ui->limexf->value();
    int N=(LIMITE2-LIMITE1)/H;//se calcula el numero de intervalos
                              //the number of intervals is calculated
    double valores[N+1][3];//se declara una matriz donde se almacenaran los resultados obtenidos
                           //a matrix is ​​declared where the obtained results will be stored
    double paso=0;//se define la variable paso
                  //the step variable is defined
    for(int i=0;i<=N;i++){//se calculan todos los puntos que se evaluaran en el metodo
                          //all the points that will be evaluated in the method are calculated
        valores[i][0]=paso;
        paso=paso+H;
    }
    for(int j=0;j<=N;j++){//se evaluan los puntos
                          //the points are evaluated
        valores[j][1]=ecuacion(valores[j][0]);
    }
    double euler=valores[0][1];//se guarda un valor de la matriz en la variable euler
                               //a value of the matrix is ​​saved in the euler variable
    double x=valores[0][0];//se crea y define la variable x
                           //the variable x is created and defined
    valores[0][2]=valores[0][1];
    for(int k=1;k<=N;k++){//se calcula el metodo de euler y se guarda en la matriz
                          //the euler method is calculated and stored in the matrix
        derivada=ecuacion2(x);
        y=euler+(derivada*H);
        euler=y;
        x=x+H;
        valores[k][2]=y;
    }
    double error[N+1];//se crea un vector llamado error
                      //a vector called error is created
    error[0]=0;
    for(int i=1;i<=N;i++){//se calculan los errores y se guardan en el vector error
                          //the errors are calculated and saved in the error vector
    error[i]=100*std::abs((valores[i][1]-valores[i][2]))/valores[i][1];
}
    ui->tabla->setRowCount(N+1);//se definen el numero de columnas y filas de la QTableWidget
                                //the number of columns and rows of the QTableWidget are defined
    ui->tabla->setColumnCount(4);
    for(int i=0;i<4;i++){
        for(int j=0;j<=N;j++){//se crean las los espacios que tendra la tabla
                              //the spaces that the table will have are created
             ui->tabla->setItem(j,i,new QTableWidgetItem);
        }
    }
   for(int i=0;i<3;i++){//se rellenan los espacios de la tabla con los valores obtenidos en el metodo
                        //fill the spaces in the table with the values ​​obtained in the method
       for(int j=0;j<=N;j++){
           ui->tabla->item(j,i)->setText(val.setNum(valores[j][i]));
       }
   }
   for(int i=0;i<=N;i++){//se agregan a la tabla los valores de los errores
                         //the values ​​of the errors are added to the table
       ui->tabla->item(i,3)->setText(val1.setNum(error[i]));
   }
}
void Euler::borrar(){//se define la funcion borrar
                     //the erase function is defined

    ui->h->setValue(0.0);//se regresan a 0 los valores de las spinbox
                         //the values ​​of the spinbox are returned to 0
    ui->liminf->setValue(0.0);
    ui->limexf->setValue(0.0);
    ui->tabla->clear();//se limpian los valores de la QTableWidget
                       //the values ​​of the QTableWidget are cleaned
}
void Euler::Salir(){//se define la funcion Salir
                    //the Exit function is defined
    close();//se cierra la interfaz y se borran los valores existentes
            //the interface is closed and the existing values ​​are deleted
    borrar();
}
//Programa elaborado por Jose Alfredo Mendoza Mota, Gibran Omar Estrada Gomez, Antonio de Jesus Herrera Diaz y Ana Karen Razo Francisco
