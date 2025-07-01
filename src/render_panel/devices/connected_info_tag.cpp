#include "connected_info_tag.h"
#include <QPainterPath>

namespace tc {

ConnectedInfoTag::ConnectedInfoTag(QWidget* parent) {
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(28, 32);
}

void ConnectedInfoTag::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::transparent);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0x29, 0x79, 0xff));

    QPainterPath path;

    int width = this->width();
    int height = this->height();
    const int radius = height / 2;

    // ���0.5����ƫ���Ի�����������
    const qreal offset = 0.5;

    // ��㣺����Բ�����˵�
    path.moveTo(offset, offset);

    // ��������Բ (���ǿ����ƫ��)
    path.arcTo(QRectF(offset, offset,2 * radius - 1, height - 1), 90, 180);

    // �����Ҳ���β���
    path.lineTo(width - offset, height - offset);  // ���½�
    path.lineTo(width - offset, offset);      // ���Ͻ�
    path.lineTo(radius + offset, offset); // �ص���Բ�����˵�

    path.closeSubpath();
    painter.drawPath(path);

    QPen pen(Qt::white, 2);  
    painter.setPen(pen);
    QPolygonF shape;
    if (expanded) {
        // ������ںŵ�����
        QPointF point1(width * 0.5, height * 0.3);  // ���ϵ�
        QPointF point2(width * 0.7, height * 0.5);  // ���ĵ�
        QPointF point3(width * 0.5, height * 0.7);  // ���µ�
        shape << point1 << point2 << point3;
    }
    else {
        // ����С�ںŵ�����
        QPointF point1(width * 0.7, height * 0.3);  // ���ϵ�
        QPointF point2(width * 0.5, height * 0.5);  // ���ĵ�
        QPointF point3(width * 0.7, height * 0.7);  // ���µ�
        shape << point1 << point2 << point3;
    }
    painter.drawPolyline(shape);
}

void ConnectedInfoTag::mousePressEvent(QMouseEvent* event) {

    QWidget::mousePressEvent(event);
}

}