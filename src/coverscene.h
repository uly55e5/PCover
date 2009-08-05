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
#ifndef COVERSCENE_H
#define COVERSCENE_H

#include <QGraphicsScene>

/**
	@author David Rauh <dave@bolivien>
*/
class CoverScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CoverScene(QObject *parent = 0);
    CoverScene ( const QRectF & sceneRect, QObject * parent = 0 );
    CoverScene ( qreal x, qreal y, qreal width, qreal height, QObject * parent = 0 );


    ~CoverScene();
    QGraphicsTextItem * selectedTextItem();
    public slots:
    void addEmptyText();
    void selectionChange();
    protected:
    void focusOutEvent ( QFocusEvent * focusEvent );
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
};

#endif
