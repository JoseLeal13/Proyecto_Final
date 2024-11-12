#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QList>

class Protagonista : public QGraphicsPixmapItem {
    Q_OBJECT  // Esto es necesario para trabajar con señales y slots

public:
    Protagonista(int startX, int startY, QGraphicsPixmapItem* parent = nullptr);
    ~Protagonista();

    int getX() const;
    int getY() const;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void update();
    void recibirDano(int dano);

private:
    void mover(int dx, int dy);
    void iniciarAnimaciones();
    void setCaminarDerecha();
    void hacerGesto();
    void morir();

    int x, y;
    int speed_x, speed_y;
    int health;
    int lives;
    bool isDead;
    int currentFrame;
    int currentGestoFrame;

    QPixmap spriteSheet;
    QPixmap normalImage;
    QList<QPixmap> framesCaminarDerecha;
    QList<QPixmap> framesSaltar;
    QList<QPixmap> gestureFrames;

    QGraphicsRectItem* healthBar;

    QTimer* timerAnimacion;
    QTimer* timerGesto;

public slots:  // Aquí agregamos los slots
    void actualizarCaminar();
    void actualizarGesto();
};

#endif // PROTAGONISTA_H
