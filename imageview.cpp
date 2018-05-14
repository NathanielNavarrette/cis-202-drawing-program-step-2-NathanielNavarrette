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
        prev_items.push_back(e->pos());
    }else if(e->button() == Qt::RightButton){

        scene->clear();
        //        QGraphicsItem * rm_item = scene->itemAt(prev_items.at((prev_items.size()-1)), QTransform());
        //        scene->removeItem(rm_item);
        //        prev_items.pop_back();
        //        delete rm_item;
        //scene->removeItem(point_temp), QTransform());

    }

    this->m_count++;
}

void ImageView::drawEllipse(QMouseEvent * e)
{
    qDebug() << "Drawing Ellipse";
    auto pos = mapToScene(e->pos());
    scene->addEllipse(pos.x()-(m_objectWidth/2),pos.y()-(m_objectHeight/2),		//x,y position of the upper left hand corner
                      m_objectWidth, m_objectHeight,				// width and height of the rectangle
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
    scene->addRect(pos.x()-(m_objectWidth/2),pos.y()-(m_objectHeight/2),		//x,y position of the upper left hand corner
                   m_objectWidth, m_objectHeight,				// width and height of the rectangle
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
    int prev_width = this->m_objectWidth;
    int prev_height = this->m_objectHeight;

    qDebug() << "Display box Image";

    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Size of Object:"));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;

    for(int i = 0; i < 2; ++i) {
        QLineEdit *lineEdit = NULL;
        QString label;
        if(i==0)
        {
            label = QString("Height:").arg(i + 1);
            lineEdit = new QLineEdit(QString::number(prev_height), &dialog);
        }else if(i == 1){
            label = QString("Width:").arg(i + 1);
            lineEdit = new QLineEdit(QString::number(prev_width), &dialog);
        }

        form.addRow(label, lineEdit);

        fields << lineEdit;
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        foreach(QLineEdit * lineEdit, fields) {
            qDebug() << lineEdit->text().toInt();
        }
    }

    if(fields.constFirst()->text().toInt() == 0 || fields.constLast()->text().toInt() == 0 )
    {
        QMessageBox::critical(this, tr("Invalid Data"), tr("You entered invalid data"));
    }else{
        this->m_objectHeight = fields.constFirst()->text().toInt();
        this->m_objectWidth = fields.constLast()->text().toInt();
    }

    //this->m_objectHeight

    //    bool ok;
    //    int size_change = QInputDialog::getInt(this, tr("Change Shape Size"),
    //                                           tr("Size:"), 100, 10, 300, 1, &ok);
    //    if(size_change > 0)
    //        this->m_objectSize = size_change;
}

void ImageView::changingColor(bool triggered)
{
    qDebug() << "Display Color Image";
    QColor change_color = QColorDialog::getColor(Qt::black, this, "Color Changer", 0);

    m_color = change_color;
}
