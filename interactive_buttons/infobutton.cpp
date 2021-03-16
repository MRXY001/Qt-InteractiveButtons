#include "infobutton.h"

InfoButton::InfoButton(QWidget *parent) : InteractiveButtonBase(parent)
{
    setUnifyGeomerey(true);
}

void InfoButton::paintEvent(QPaintEvent *event)
{
    InteractiveButtonBase::paintEvent(event);

    if (!show_foreground) return ; // 不显示前景

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(icon_color);
    QPainterPath path;

    double l = _l, t = _t, w = _w, h = _h;

    double cu = 2; // 点的粗细
    if (!hover_progress) // 显示感叹号
    {
        // 画点
        path.addEllipse(QRectF(l+w/2-cu, t+h/4, cu*2, cu*2));

        // 画线
        path.addRoundedRect(QRectF(l+w/2-cu/2, t+h*3/8+cu, cu, h/2 - cu - cu/2), cu/2, cu/2);
    }
    else if (hover_progress < 100) // 转换动画
    {
        double prop = hover_progress / 100.0;

        // 眼睛出现
        double ra = cu * prop;
        path.addEllipse(l+w/4-ra, t+h/4-ra, ra*2, ra*2);
        path.addEllipse(l+w*3/4-ra, t+h/4-ra, ra*2, ra*2);

        // 鼻子下降
        double top = t+h/4 + (h/4-cu/2) * prop;
        path.addEllipse(QRectF(l+w/2-cu, top, cu*2, cu*2));

        double h_mv = w / 4 * prop;

        // 左胡子移动
        QPainterPath pathl;
        pathl.moveTo(l+w/2, top);
        pathl.cubicTo(QPointF(l+w*8/16, t+h*7/8), QPointF(l+w*5/16, t+h*6/8), QPointF(l+w/2-h_mv, t+h*11/16));
        painter.drawPath(pathl);

        // 右胡子移动
        QPainterPath pathr;
        pathr.moveTo(l+w/2, top);
        pathr.cubicTo(QPointF(l+w*8/16, t+h*7/8), QPointF(l+w*11/16, t+h*6/8), QPointF(l+w/2+h_mv, t+h*11/16));
        painter.drawPath(pathr);
    }
    else // 显示笑脸
    {
        // 眼睛
        if (pressing) // 横线
        {
            if (offset_pos.x() * offset_pos.x() + offset_pos.y() + offset_pos.y() > this->width() * this->height() / 4) // 显示 x_x
            {
                painter.drawLine(QPointF(l+w/4-cu, t+h/4-cu), QPointF(l+w/4+cu, t+h/4+cu));
                painter.drawLine(QPointF(l+w/4-cu, t+h/4+cu+0.5), QPointF(l+w/4+cu, t+h/4-cu));
                painter.drawLine(QPointF(l+w*3/4-cu, t+h/4-cu), QPointF(l+w*3/4+cu, t+h/4+cu));
                painter.drawLine(QPointF(l+w*3/4-cu, t+h/4+cu+0.5), QPointF(l+w*3/4+cu, t+h/4-cu));
            }
            else // 显示 -_-
            {
                painter.drawLine(QPointF(l+w/4-cu*2, t+h/4), QPointF(l+w/4+cu*2, t+h/4));
                painter.drawLine(QPointF(l+w*3/4-cu*2, t+h/4), QPointF(l+w*3/4+cu*2, t+h/4));
            }
        }
        else // 点
        {
            path.addEllipse(l+w/4-cu, t+h/4-cu, cu*2, cu*2);
            path.addEllipse(l+w*3/4-cu, t+h/4-cu, cu*2, cu*2);
        }

        // 鼻子
        path.addEllipse(l+w/2-cu, t+h/2-cu/2, cu*2, cu*2);

        // 左胡子
        QPainterPath pathl;
        pathl.moveTo(l+w/2, t+h*4/8);
        pathl.cubicTo(QPointF(l+w*8/16, t+h*7/8), QPointF(l+w*5/16, t+h*6/8), QPointF(l+w/4, t+h*11/16));
        painter.drawPath(pathl);

        // 右胡子
        QPainterPath pathr;
        pathr.moveTo(l+w/2, t+h*4/8);
        pathr.cubicTo(QPointF(l+w*8/16, t+h*7/8), QPointF(l+w*11/16, t+h*6/8), QPointF(l+w*3/4, t+h*11/16));
        painter.drawPath(pathr);
    }
    painter.fillPath(path, icon_color);
}
