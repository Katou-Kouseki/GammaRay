#include "connected_info_tag.h"
#include <QPainterPath>

namespace tc {

ConnectedInfoTag::ConnectedInfoTag(QWidget* parent) {
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(48, 48);
}

void ConnectedInfoTag::paintEvent(QPaintEvent* event)
{
    //Q_UNUSED(event);
    //QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing);  // �����

    //// 1. ���������͸����
    //painter.fillRect(rect(), Qt::transparent);

    // 2. ���ư�Բ���ϰ�Բʾ����
    //QRect circleRect = rect();
    //painter.setPen(Qt::NoPen);
    //painter.setBrush(QColor(52, 152, 219));  // ��ɫ���

    //// �Ƕȵ�λ��1/16�ȣ�90�� * 16 = 1440, 180�� * 16 = 2880��
    //painter.drawPie(circleRect, 90 * 16, 180 * 16);  // ��90�㿪ʼ��180�㣨�ϰ�Բ��

    /* ���������Բ��
      �°�Բ��painter.drawPie(rect(), 270 * 16, 180 * 16);
      ���Բ��painter.drawPie(rect(), 180 * 16, 180 * 16);
      �Ұ�Բ��painter.drawPie(rect(), 0 * 16, 180 * 16);
    */

    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::transparent);

    // ������״��ɫ
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(52, 152, 219));

    QPainterPath path;/*
    CreateLeftPath(path);*/

    const int w = width();
    const int h = height();
    const int radius = h / 2;

    // ���0.5����ƫ���Ի�����������
    const qreal offset = 0.5;

    // ��㣺����Բ�����˵�
    path.moveTo(offset, offset);

    // ��������Բ (���ǿ����ƫ��)
    path.arcTo(QRectF(offset, offset,
        2 * radius - 1, h - 1),
        90, 180);

    // �����Ҳ���β���
    path.lineTo(w - offset, h - offset);  // ���½�
    path.lineTo(w - offset, offset);      // ���Ͻ�
    path.lineTo(radius + offset, offset); // �ص���Բ�����˵�

    path.closeSubpath();


    painter.drawPath(path);
}



void ConnectedInfoTag::CreateLeftPath(QPainterPath& path) {
    const int w = width();
    const int h = height();
    const int radius = qMin(w, h) / 2;

    // ���Բ����
    path.moveTo(0, h / 2);
    path.arcTo(QRectF(0, h / 2 - radius, 2 * radius, 2 * radius), 90, 180);

    // ����ľ��β���
    path.lineTo(w, h);
    path.lineTo(w, 0);
    path.closeSubpath();
}
}