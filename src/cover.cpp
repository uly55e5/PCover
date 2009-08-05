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
#include "cover.h"
#include "m3uplaylist.h"
#include "coverscene.h"
#include "math.h"

#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QtDebug>
#include <QTime>
#include <QFontDialog>

Cover::Cover(M3UPlaylist * playlist, QObject *parent)
 : QObject(parent)
{
    _coverScene=0;
    _playlist = playlist;
    readSettings();
    readImageList();
    updateCover();
    _lastDir = playlist->dir();
    connect(this,SIGNAL(layoutChanged()),this,SLOT(updateCover()));

}

Cover::~Cover()
{
}

void Cover::readSettings()
{
    _hAlign= equal;
    _vAlign= equal;
    _manRows = FALSE;
    _autoSingleCoverSize = TRUE;
    _singleCoverSize=QSize(200,200);
    _coverSize=1200;
    _rows=1;
    _preferVertical=FALSE;
    _singleCoverAlpha=70;
    _underfullRow=255;

}

void Cover::readImageList()
{
    _imageList = new QStringList;
    int size = _playlist->size();
    int i = 0;
    QStringList filters;
    filters << "*.jpg" << "*.jpeg"<< "*.gif" << "*.png";
    while (i < size )
    {
        QString file = _playlist->fileNameForTrack(i);
        QFileInfo info(file);
        QStringList images = info.dir().entryList(filters);
        if (images.isEmpty())
            qWarning() << "Kein Bild";
        else
        {
            QString image = info.dir().absolutePath() + "/" +
                images.first();
            if (not _imageList->contains(image))
             _imageList->append(image);
            qDebug() << "Bild: " << image;
        }
        i++;
    }
}

void Cover::addText(QString text)
{
    if (_coverScene == 0)
        return;
    QGraphicsTextItem * item = _coverScene->addText(text);
    //item->setVisible(TRUE);
    item->setFlags(QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIsSelectable );
    item->setZValue(1);
    emit coverChanged();
}

void Cover::updateCover()
{
    int listsize = _imageList->size();
    if (!_manRows)
    {
        _rows = int(sqrt(listsize));
        if ( listsize - _rows*_rows > _rows || (_preferVertical && listsize / _rows > _rows))
            _rows++;
    }
    int  cols = listsize/_rows + qMin(1,listsize%_rows);

    if ( _autoSingleCoverSize )
    {
        int size=_coverSize/qMax(_rows,cols);
        _singleCoverSize = QSize(size,size);
    }

    if (_hAlign != manual)
    {
        _leftMargin = 0;
        _hSpace=0;
    }
    if (_hAlign==center)
        _leftMargin = (_coverSize-(_singleCoverSize.width()*cols))/2;
    else if ( _hAlign == right )
        _leftMargin = _coverSize-(_singleCoverSize.width()*cols);
    else if ( _hAlign== equal )
    {
        _leftMargin = (_coverSize-(_singleCoverSize.width()*cols))/(cols+1);
        _hSpace = _leftMargin;
    }

    if (_vAlign != manual)
    {
        _topMargin=0;
        _vSpace=0;
    }
    if (_vAlign==center)
        _topMargin = (_coverSize-(_singleCoverSize.height()*_rows))/2;
    else if ( _vAlign == bottom )
        _topMargin = _coverSize-(_singleCoverSize.height()*_rows);
    else if ( _vAlign== equal )
    {
        _topMargin = (_coverSize-(_singleCoverSize.height()*_rows))/(_rows+1);
        _vSpace = _topMargin;
    }
    _underfullRow = qMin(_underfullRow,_rows);
    updateScene();
    emit coverChanged();
}

void Cover::updateScene()
{

    if (_coverScene == 0)
    {
        _coverScene = new CoverScene(0,0,_coverSize,_coverSize);
        _coverScene->setBackgroundBrush(_backgroundColor);
        int i = 0;
        while ( i < _imageList->size())
        {
            QPixmap pixmap(_imageList->value(i));
            _pixmapList.append(pixmap);
            setAlpha(pixmap);
            QGraphicsPixmapItem * item = _coverScene->addPixmap(pixmap);
            _pixmapItemList.append(item);
            i++;
            connect(_coverScene,SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
        }
    }
    int colc = 0;
    int rowc = 0;
    int leftOffset = 0;
    int hSpaceOffset = 0;
    int i=0;
    int pixs = _pixmapItemList.size();
    int cols = pixs/_rows + qMin(1,pixs%_rows);
    int posx,posy;
    qsrand(QTime::currentTime().msec());
    while ( i < pixs )
    {
        if(_hAlign==random)
            posx = (qreal)qrand()/RAND_MAX*(_coverSize-_singleCoverSize.width());
        else
            posx = colc*_singleCoverSize.width() +
                    _leftMargin + leftOffset + (colc*(_hSpace+hSpaceOffset));
        if (_vAlign==random)
            posy = (qreal)qrand()/RAND_MAX*(_coverSize-_singleCoverSize.height());
        else
            posy=rowc*_singleCoverSize.height() + _topMargin + (_vSpace*rowc);
        QGraphicsPixmapItem * item = _pixmapItemList.value(i);
        item->setPos(posx,posy);
        item->scale((qreal)_singleCoverSize.width()/item->sceneBoundingRect().width(),
                    (qreal)_singleCoverSize.height()/item->sceneBoundingRect().height());
        colc++;
        if (colc==cols || (rowc == _underfullRow-1 && colc == (pixs % cols)))
        {
            rowc++;
            colc=0;
            if (rowc==_underfullRow-1 && pixs % cols)
            {
                if(_hAlign==center)
                    leftOffset = (cols - pixs % cols) * _singleCoverSize.width()/2;
                if (_hAlign==right)
                    leftOffset = (cols - pixs % cols) * _singleCoverSize.width();
                if (_hAlign == equal )
                {
                    leftOffset = (cols - pixs % cols) *
                            _singleCoverSize.width()/(pixs % cols +1);
                    hSpaceOffset = leftOffset;
                }
            }
            else
            {
                leftOffset = 0;
                hSpaceOffset = 0;
            }
        }
        i++;
    }
}

void Cover::setAlpha(QPixmap & pixmap)
{
    int alpha = _singleCoverAlpha*255/100;
    QColor color(alpha,alpha,alpha,alpha);
    QPixmap alphaMap(pixmap.size());
    alphaMap.fill(color);
    pixmap.setAlphaChannel(alphaMap);
}

bool Cover::saveCover(QString fileName)
{
    QPixmap image(_coverSize,_coverSize);
    QPainter painter(&image);
    _coverScene->render(&painter);
    painter.end();
    image.save(fileName);
    QFileInfo info(fileName);
    _lastDir = info.dir().absolutePath();
    return TRUE;
}

QString Cover::lastDir()
{
    return _lastDir;
}

void Cover::setVAlignment(CoverAlign a)
{
    if ( a == _vAlign && a != random )
        return;
    _vAlign=a;
    emit layoutChanged();
}

Cover::CoverAlign Cover::vAlignment()
{
    return _vAlign;
}

void Cover::setHAlignment(CoverAlign a)
{
    if (a == _hAlign && a != random )
        return;
    _hAlign=a;
    emit layoutChanged();
}

Cover::CoverAlign Cover::hAlignment()
{
    return _hAlign;
}

void Cover::setLeftMargin(int margin)
{
    if (margin == _leftMargin)
        return;
    _leftMargin=margin;
    emit layoutChanged();
}

void Cover::setTopMargin(int margin)
{
    if (margin == _topMargin)
        return;
    _topMargin=margin;
    emit layoutChanged();
}

void Cover::setVSpace(int space)
{
    if (space == _vSpace)
        return;
    _vSpace=space;
    emit layoutChanged();
}

void Cover::setHSpace(int space)
{
    if (space == _hSpace)
        return;
    _hSpace=space;
    emit layoutChanged();
}

int Cover::coverSize()
{
    return _coverSize;
}

void Cover::setCoverSize(int size)
{
    if (_coverSize == size)
        return;
    _coverSize = size;
    emit layoutChanged();
}

QGraphicsScene * Cover::scene()
{
    return _coverScene;
}

uint Cover::underfullRow()
{
    return _underfullRow;
}

void Cover::setUnderfullRow(int row)
{
    if ( row == _underfullRow)
        return;
    _underfullRow = row;
    emit layoutChanged();
}

void Cover::setPreferVertical(bool p)
{
    if (_preferVertical == p)
        return;
    _preferVertical=p;
    emit layoutChanged();
}

void Cover::setManRows(bool p)
{
    if (_manRows == p)
        return;
    _manRows=p;
    emit coverChanged();
}

bool Cover::manRows()
{
    return _manRows;
}
bool Cover::preferVertical()
{
    return _preferVertical;
}

uint Cover::imageListSize()
{
    return _imageList->size();
}

void Cover::setRows(int rows)
{
    if (_rows == rows )
        return;
    _rows=rows;
    emit layoutChanged();
}

uint Cover::rows()
{
    return _rows;
}

void Cover::setSingleCoverSize(int x, int y)
{
    _singleCoverSize = QSize(x,y);
    emit layoutChanged();
}

QSize Cover::singleCoverSize() const
{
    return _singleCoverSize;
}
void Cover::setSingleCoverAlpha(int alpha)
{
    if (_singleCoverAlpha == alpha)
        return;
    _singleCoverAlpha = alpha;
    int i=0;
    while( i < _pixmapItemList.size())
    {
        QGraphicsPixmapItem * item = _pixmapItemList.value(i);
        QPixmap p = _pixmapList.value(i);
        setAlpha(p);
        item->setPixmap(p);
        i++;
    }
    emit coverChanged();
}

uint Cover::singleCoverAlpha() const
{
    return _singleCoverAlpha;
}

void Cover::setBackgroundColor(QColor & color)
{
    if (color == _backgroundColor)
        return;
    _backgroundColor = color;
    _coverScene->setBackgroundBrush(_backgroundColor);
    emit coverChanged();
}

QColor Cover::backgroundColor() const
{
    return _backgroundColor;
}

bool Cover::autoSingleCoverSize() const
{
    return _autoSingleCoverSize;
}

void Cover::setAutoSingleCoverSize(bool p)
{
    if(p ==_autoSingleCoverSize )
        return;
    _autoSingleCoverSize = p;
    emit layoutChanged();
}

QGraphicsTextItem * Cover::selectedTextItem()
{
    return _coverScene->selectedTextItem();
}

void Cover::addText()
{
    _coverScene->addEmptyText();
}