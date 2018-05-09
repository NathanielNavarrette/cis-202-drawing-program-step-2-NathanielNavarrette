#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <vector>

enum Operation {noop,ellipse,rectangle,line};
class ImageView : public QGraphicsView
{
    Q_OBJECT
public:
    // http://en.cppreference.com/w/cpp/language/explicit
    explicit ImageView(QWidget *parent = 0);

signals:

public slots:
    void mousePressEvent(QMouseEvent * e);
    // void mouseReleaseEvent(QMouseEvent * e);
    // void mouseDoubleClickEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void addingEllipse(bool);
    void addingLine(bool);
    void addingRectangle(bool);
private:
    QGraphicsScene * scene;
    QPointF original_position;
    QPointF last_position;
    Operation current_op;
    Operation original_op;
    Operation prev_op;
    int count = 0;

    int objectSize = 100;

    void drawEllipse(QMouseEvent * e);
    void drawRectangle(QMouseEvent * e);
    void drawLine(QMouseEvent * e);

    void deleteEllipse(QMouseEvent * e);

    std::vector<QGraphicsItem> prev_items; // a vector to store for "undo"

    QPen getColorPen();
    QBrush getColorBrush();
};
#endif // IMAGEVIEW_H
