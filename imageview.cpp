#include "imageview.h"
#include <QDebug>

ImageView::ImageView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(QRectF(-200,-200,400,400));
    this->setScene(scene);
    last_position.setX(0);
    last_position.setY(0);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    connect(parent,SIGNAL(addingEllipse(bool)),this,SLOT(addingEllipse(bool)));
    connect(parent,SIGNAL(addingLine(bool)),this,SLOT(addingLine(bool)));
    connect(parent,SIGNAL(addingRectangle(bool)),this,SLOT(addingRectangle(bool)));

}

void ImageView::mousePressEvent(QMouseEvent * e)
{
    if(e->button() == Qt::LeftButton)
    {
        if(current_op == Operation::ellipse )
        {
            qDebug() << "Operation Ellipse";
            drawEllipse(e);
            prev_op = current_op;
        }else if(current_op == Operation::rectangle){
            qDebug() << "Operation Rectangle";
            drawRectangle(e);
            prev_op = current_op;
        }else if(current_op == Operation::line){
            qDebug() << "Operation Line";
            if(prev_op != current_op)
                last_position = original_position;
            drawLine(e);
            prev_op = current_op;
        }
    }else if(e->button() == Qt::RightButton){
        //        // check whether there is an item under the cursor
        //        QGraphicsItem * itemToRemove = NULL;
        //        foreach(auto item, items(e->pos() ) )
        //        {
        //            if(item->type() == QGraphicsItem::UserType+1)
        //            {
        //                itemToRemove = item;
        //                break;
        //            }
        //        }
        //            // remove the item from the graphicsScene
        //            qDebug() << "Attempting to remove";
        //                scene->removeItem(itemToRemove);
        scene->clear();
    }

    this->count++;
}

void ImageView::drawEllipse(QMouseEvent * e)
{
    qDebug() << "Drawing Ellipse";
    auto pos = mapToScene(e->pos());
    scene->addEllipse(pos.x()-(objectSize/2),pos.y()-(objectSize/2),		//x,y position of the upper left hand corner
                      objectSize,objectSize,				// width and height of the rectangle
                      getColorPen(),		// the pen used for the outline
                      getColorBrush()); 	// the brush used for the inside of the ellipse

    last_position = pos;
}

void ImageView::deleteEllipse(QMouseEvent *e)
{
    //    qDebug() << "Drawing Ellipse";
    //    auto pos = mapToScene(e->pos());
    //    scene->removeItem(QGraphicsScene::itemAt(QPointF(pos.x(),pos.y() ) ) );
    //    last_position = pos;
}

void ImageView::drawRectangle(QMouseEvent * e)
{
    qDebug() << "Drawing Rectangle";
    auto pos = mapToScene(e->pos());
    scene->addRect(pos.x()-(objectSize/2),pos.y()-(objectSize/2),		//x,y position of the upper left hand corner
                   objectSize,objectSize,				// width and height of the rectangle
                   getColorPen(),		// the pen used for the outline
                   getColorBrush()); 	// the brush used for the inside of the ellipse
    last_position = pos;
}

void ImageView::drawLine(QMouseEvent * e)
{
    qDebug() << "Drawing Line";
    auto pos = mapToScene(e->pos());

    if(last_position.x() != 0 && last_position.y() != 0)
    {
        scene->addLine(last_position.x(),
                       last_position.y(),
                       pos.x(),
                       pos.y(),
                       getColorPen()
                       );
    }
    last_position = pos;
}

void ImageView::mouseMoveEvent(QMouseEvent *e)
{

}

void ImageView::addingEllipse(bool toggled)
{
    qDebug()  << "ImageView::addingEllipse";
    if(toggled)
    {
        current_op = Operation::ellipse;
    }else{
        current_op = original_op;
    }
}

void ImageView::addingLine(bool toggled)
{
    if(toggled)
    {
        current_op = Operation::line;
    }else{
        current_op = original_op;
    }
}

void ImageView::addingRectangle(bool toggled)
{
    if(toggled)
    {
        current_op = Operation::rectangle;
    }else{
        current_op = original_op;
    }
}

QPen ImageView::getColorPen()
{
    int inc = this->count % 5;

    if(inc == 0)
        return QPen(Qt::black);
    else if(inc == 1)
        return QPen(Qt::blue);
    else if(inc == 2)
        return QPen(Qt::red);
    else if(inc == 3)
        return QPen(Qt::green);
    else if(inc == 4)
        return QPen(Qt::yellow);
    else
        return QPen(Qt::black);
}

QBrush ImageView::getColorBrush()
{
    int inc = this->count % 5;

    if(inc == 0)
        return QBrush(Qt::black);
    else if(inc == 1)
        return QBrush(Qt::blue);
    else if(inc == 2)
        return QBrush(Qt::red);
    else if(inc == 3)
        return QBrush(Qt::green);
    else if(inc == 4)
        return QBrush(Qt::yellow);
    else
        return QBrush(Qt::black);
}
