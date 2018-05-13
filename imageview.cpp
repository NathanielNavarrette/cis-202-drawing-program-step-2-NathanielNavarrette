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
    connect(parent,SIGNAL(displaySizeBox(bool)),this,SLOT(displaySizeBox(bool)));
    connect(parent,SIGNAL(changingColor(bool)),this,SLOT(changingColor(bool)));

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

    this->m_count++;
}

void ImageView::drawEllipse(QMouseEvent * e)
{
    qDebug() << "Drawing Ellipse";
    auto pos = mapToScene(e->pos());
    scene->addEllipse(pos.x()-(m_objectSize/2),pos.y()-(m_objectSize/2),		//x,y position of the upper left hand corner
                      m_objectSize,m_objectSize,				// width and height of the rectangle
                      QPen(m_color),		// the pen used for the outline
                      QBrush(m_color)); 	// the brush used for the inside of the ellipse

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
    scene->addRect(pos.x()-(m_objectSize/2),pos.y()-(m_objectSize/2),		//x,y position of the upper left hand corner
                   m_objectSize,m_objectSize,				// width and height of the rectangle
                   QPen(m_color),		// the pen used for the outline
                   QBrush(m_color)); 	// the brush used for the inside of the ellipse
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
                       QPen(m_color)
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

void ImageView::displaySizeBox(bool triggered)
{
    qDebug() << "Display box Image";
    bool ok;
    int size_change = QInputDialog::getInt(this, tr("Change Shape Size"),
                                     tr("Size:"), 100, 10, 300, 1, &ok);
    if(size_change > 0)
        this->m_objectSize = size_change;
}

void ImageView::changingColor(bool triggered)
{
    qDebug() << "Display Color Image";
    QColor change_color = QColorDialog::getColor(Qt::black, this, "Color Changer", 0);

    m_color = change_color;
}
