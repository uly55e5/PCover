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
#ifndef COVER_H
#define COVER_H

#include <QObject>

class M3UPlaylist;
class CoverScene;

class QImage;
class QString;
class QStringList;
class QGraphicsScene;
class QPixmap;
class QGraphicsPixmapItem;
class QGraphicsTextItem;

#include <QSize>
#include <QColor>

/**
	@author David Raug <d.rauh@freenet.de>
*/
class Cover : public QObject
{

Q_OBJECT
public:
    enum CoverAlign{left,top=left,right,bottom=right,center,equal,manual,random};
    Cover(M3UPlaylist * playlist, QObject *parent = 0);
    ~Cover();

    QImage * cover();
    bool saveCover(QString fileName = "cover.jpg");
    QString lastDir();
        // Layout
        CoverAlign vAlignment();
        CoverAlign hAlignment();
        bool preferVertical();
        bool manRows();
        uint rows();
        uint imageListSize();
        int coverSize();
        QGraphicsScene * scene();
        uint underfullRow();
        uint singleCoverAlpha() const;
        QColor backgroundColor() const;
        QSize singleCoverSize() const;
        bool autoSingleCoverSize() const;
        QGraphicsTextItem * selectedTextItem();
    public slots:
        void addText();
        // Layout
        void setPreferVertical(bool p);
        void setManRows(bool p);
        void setRows(int rows);
        void setVAlignment(CoverAlign a);
        void setHAlignment(CoverAlign a);
        void setVSpace(int space);
        void setHSpace(int space);
        void setLeftMargin(int margin);
        void setTopMargin(int margin);
        void setUnderfullRow(int row);
        // Größe und Farbe
        void setCoverSize(int size);
        void setSingleCoverSize(int x, int y);
        void setSingleCoverAlpha(int alpha);
        void setBackgroundColor(QColor & color);
        void setAutoSingleCoverSize(bool p);
        // Verschiedens
        void updateScene();
        void updateCover();
        void addText(QString text);
    signals:
        void coverChanged();
        void settingsChanged();
        void layoutChanged();
        void selectionChanged();
    private:
        void readImageList();
        void readSettings();
        void setAlpha(QPixmap & pixmap);

        QStringList * _imageList;
        M3UPlaylist * _playlist;
        QList<QGraphicsPixmapItem *> _pixmapItemList;
        QList<QPixmap> _pixmapList;
        QString _lastDir;
        CoverScene * _coverScene;

        CoverAlign _hAlign;
        CoverAlign _vAlign;
        int _rows;
        bool _preferVertical;

        bool _manRows;
        bool _autoSingleCoverSize;
        int _underfullRow;
        int _leftMargin;
        int _hSpace;
        int _topMargin;
        int _vSpace;

        uint _singleCoverAlpha;
        QSize _singleCoverSize;
        int _coverSize;
        QColor _backgroundColor;
};

#endif
