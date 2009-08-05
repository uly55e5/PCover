/***************************************************************************
 *   Copyright (C) 2007 by David Raug   *
 *   d.rauh@freenet.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "coverscene.h"
#include <QGraphicsItem>

CoverScene::CoverScene(QObject *parent)
        : QGraphicsScene(parent)
{}

CoverScene::CoverScene ( const QRectF & sceneRect, QObject * parent)
    : QGraphicsScene ( sceneRect, parent)
{}

CoverScene::CoverScene ( qreal x, qreal y, qreal width, qreal height, QObject * parent )
    : QGraphicsScene(x,y,width,height,parent)
{}


CoverScene::~CoverScene()
{}


QGraphicsTextItem * CoverScene::selectedTextItem()
{
    QGraphicsItem * item;
    foreach(item, selectedItems())
    {
        return qgraphicsitem_cast<QGraphicsTextItem *>(item);
    }
}

void CoverScene::addEmptyText()
{
    QGraphicsTextItem * textItem = addText("Neuer Text");
    //textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    textItem->setFlags(QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIsSelectable );
    textItem->setZValue(1);
    addItem(textItem);
}

void CoverScene::selectionChange()
{
    QGraphicsTextItem * item = selectedTextItem();
    if (item !=0 )
    {
//        item->setFlags(QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIsSelectable );itemSelected(item);
    }
}

void CoverScene::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    QGraphicsTextItem * item = selectedTextItem();
    if (item != 0)
    item->setTextInteractionFlags(Qt::TextEditorInteraction);
    mousePressEvent(mouseEvent);
}

void CoverScene::focusOutEvent ( QFocusEvent * focusEvent )
{
    QGraphicsTextItem * item = selectedTextItem();
    if (item != 0)
    {
    item->setTextInteractionFlags(Qt::NoTextInteraction);
    item->setFlags(QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIsSelectable );
    }
    QGraphicsScene::focusOutEvent(focusEvent);
}
