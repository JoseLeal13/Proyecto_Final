#include "protagonista.h"
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QDebug>

Protagonista::Protagonista(int startX, int startY, QGraphicsPixmapItem *parent)
    : QGraphicsPixmapItem(parent), x(startX), y(startY), speed_x(0), speed_y(0),
    health(100), lives(3), isDead(false), currentFrame(0),
    timerAnimacion(nullptr), timerGesto(nullptr), healthBar(nullptr)
{
    setPos(x, y); // Establece la posición inicial
    setFlag(QGraphicsItem::ItemIsFocusable); // Hacer que el objeto sea "focusable"
    setFocus(); // Otorgar el foco al protagonista para recibir eventos de teclado

    // Cargar la imagen predeterminada del protagonista desde la hoja de sprites
    spriteSheet = QPixmap("C:\\Users\\Lenovo\\Pictures\\bart simpson animation 2.jpg");

    // La imagen de Bart está en la fila 1, columna 1 de la hoja de sprites
    normalImage = spriteSheet.copy(0, 0, 39, 87);  // Ajusta el tamaño si es necesario
    setPixmap(normalImage); // Establece la imagen predeterminada de Bart

    // Intentar cargar la imagen para los gestos
    QPixmap gestureSheet("C:\\Users\\Lenovo\\Pictures\\bart baile 2.png");

    // Verificar si la imagen se carga correctamente
    if (gestureSheet.isNull()) {
        qDebug() << "Error al cargar la imagen de gesto.";
        return;
    }

    // Inicializar las imágenes para el gesto
    for (int i = 0; i < 7; ++i) {
        // Asegúrate de que los cuadros estén bien alineados en la imagen
        gestureFrames.append(gestureSheet.copy(i * 39, 0, 39, 87)); // Suponiendo que cada cuadro es de 39x87
    }

    // Crear la barra de salud
    healthBar = new QGraphicsRectItem(this);
    healthBar->setRect(0, -10, health, 5);
    healthBar->setBrush(Qt::green);

    // Inicializar las animaciones
    iniciarAnimaciones();
}

Protagonista::~Protagonista() {
    // Liberar recursos de los punteros
    delete timerAnimacion;
    delete timerGesto;
    delete healthBar;
}

int Protagonista::getX() const {
    return x;
}

int Protagonista::getY() const {
    return y;
}

void Protagonista::keyPressEvent(QKeyEvent* event) {
    if (isDead) return;

    switch (event->key()) {
    case Qt::Key_W:
        speed_y = -5;
        break;
    case Qt::Key_A:
        speed_x = -5;
        // Voltear la imagen cuando se mueve a la izquierda
        setPixmap(normalImage.transformed(QTransform().scale(-1, 1)));
        break;
    case Qt::Key_S:
        speed_y = 5;
        break;
    case Qt::Key_D:
        speed_x = 5;
        // Volver a la imagen original cuando se mueve a la derecha
        setPixmap(normalImage);
        break;
    case Qt::Key_Space:
        hacerGesto();
        break;
    default:
        break;
    }
}

void Protagonista::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_S:
        speed_y = 0;
        break;
    case Qt::Key_A:
    case Qt::Key_D:
        speed_x = 0;
        break;
    default:
        break;
    }
}

void Protagonista::update() {
    if (!isDead) {
        mover(speed_x, speed_y);
    }
}

void Protagonista::mover(int dx, int dy) {
    QPointF nuevaPos = this->pos() + QPointF(dx, dy);
    this->setPos(nuevaPos);

    bool colision = false;
    for (QGraphicsItem* item : scene()->collidingItems(this)) {
        if (item != this) {
            colision = true;
            break;
        }
    }
    if (!colision) {
        x += dx;
        y += dy;
    } else {
        this->setPos(this->pos() - QPointF(dx, dy));
    }
}

void Protagonista::iniciarAnimaciones() {
    // Cargar los cuadros para caminar hacia la derecha
    for (int i = 0; i < 13; ++i) {
        framesCaminarDerecha.append(spriteSheet.copy(i * 39, 1 * 87, 39, 87)); // Los cuadros de caminar son 39x87
    }

    // Cargar los cuadros para saltar
    for (int i = 0; i < 2; ++i) {
        framesSaltar.append(spriteSheet.copy(i * 78, 2 * 87, 78, 87)); // Los cuadros de salto son 78x87
    }

    // Inicializar el temporizador de la animación
    if (!timerAnimacion) {
        timerAnimacion = new QTimer(this);
        connect(timerAnimacion, &QTimer::timeout, this, &Protagonista::actualizarCaminar);
        timerAnimacion->start(100); // Cambiar cada 100 ms
    }
}

void Protagonista::actualizarCaminar() {
    currentFrame = (currentFrame + 1) % framesCaminarDerecha.size();
    setCaminarDerecha();
}

void Protagonista::setCaminarDerecha() {
    setPixmap(framesCaminarDerecha[currentFrame]);
}

void Protagonista::hacerGesto() {
    // Reiniciar la animación del gesto
    currentGestoFrame = 0; // Reiniciar el índice del cuadro actual
    if (!timerGesto) {  // Asegurarse de que no haya una instancia previa de timerGesto
        timerGesto = new QTimer(this);
        connect(timerGesto, &QTimer::timeout, this, &Protagonista::actualizarGesto);
        timerGesto->start(100); // Cambiar la imagen cada 100 ms
    }
}

void Protagonista::actualizarGesto() {
    // Actualizar la imagen con el siguiente cuadro de la animación
    setPixmap(gestureFrames[currentGestoFrame]);

    // Incrementar el índice para el siguiente cuadro
    currentGestoFrame = (currentGestoFrame + 1) % gestureFrames.size();

    // Detener la animación después de un ciclo completo
    if (currentGestoFrame == 0) {
        timerGesto->stop();
        setPixmap(normalImage); // Regresar a la imagen normal después de la animación
    }
}

void Protagonista::recibirDano(int dano) {
    health -= dano;
    if (health <= 0) {
        health = 0;
        morir();
    }
    healthBar->setRect(0, -10, health, 5); // Actualiza el tamaño de la barra de salud
}

void Protagonista::morir() {
    isDead = true;
    setPixmap(QPixmap("C:\\ruta\\imagen_de_muerte.png")); // Imagen de muerte
    // Aquí puedes agregar cualquier otro código necesario cuando el protagonista muere
}
