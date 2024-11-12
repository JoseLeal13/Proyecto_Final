#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protagonista.h"  // Asegúrate de incluir la cabecera de la clase Protagonista

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configuración de la escena
    scene = new QGraphicsScene(this); // Crear la escena
    sceneWidth = 800; // Ancho de la escena
    sceneHeight = 600; // Alto de la escena
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight); // Establecer el rectángulo de la escena

    // Establecer el fondo de la escena con una imagen
    QPixmap base("C:\\Users\\Lenovo\\Pictures\\Base simpsons.jpg"); // Imagen para el fondo
    scene->setBackgroundBrush(base.scaled(sceneWidth, sceneHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    // Crear el protagonista (Bart) - Asegúrate de inicializarlo correctamente
    protagonista = new Protagonista(100, 500); // Crear una instancia de Protagonista con la posición (100, 500)

    // Configurar la posición del protagonista (opcional, ya lo hemos hecho con el constructor)
    protagonista->setPos((sceneWidth - 50) / 2, sceneHeight - 50);

    scene->addItem(protagonista); // Agregar el protagonista a la escena

    // Hacer al protagonista enfocable
    protagonista->setFlag(QGraphicsItem::ItemIsFocusable);
    protagonista->setFocus(); // Establecer el foco al protagonista para recibir eventos del teclado
}

MainWindow::~MainWindow()
{
    delete ui;
    delete protagonista; // Eliminar el protagonista cuando la ventana se cierre
}
