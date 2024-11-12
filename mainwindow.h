#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "protagonista.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Miembros para la escena y la vista
    QGraphicsScene *scene;    // La escena donde se colocan los elementos
    QGraphicsView *view;      // La vista para mostrar la escena

    // Miembros para los elementos de la escena
    QGraphicsPixmapItem *bart; // El item que representa a Bart en la escena
    Protagonista *protagonista;           // El jugador (si lo usas)

    int sceneWidth = 800;      // Ancho de la escena
    int sceneHeight = 600;     // Alto de la escena
    int tileSize = 50;         // Tamaño de los tiles, si es necesario para el jugador
};

#endif // MAINWINDOW_H
