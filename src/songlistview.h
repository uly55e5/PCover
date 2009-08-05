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
#ifndef SONGLISTVIEW_H
#define SONGLISTVIEW_H

#include <QWidget>

class QLabel;
class QLineEdit;
class M3UPlaylist;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;

#include <QString>

/**
	@author David Raug <d.rauh@freenet.de>
*/
class SongListView : public QWidget
{
Q_OBJECT
public:
    SongListView(QWidget * parent=0);
    SongListView(M3UPlaylist * list, QWidget *parent = 0);

    ~SongListView();

    public slots:
        void setFormat(QString format);
        void setPlaylist(M3UPlaylist * list);
        void updateSonglist();
        void addToCoverClicked();
    signals:
        void songlistChanged();
        void addToCover(QString text);
    protected:
        void createLayout();

        M3UPlaylist * _playlist;
        QString _format;

        QLabel * _formatLabel;
        QLabel * _listLabel;

        QPushButton * _addToCoverButton;

        QLineEdit * _formatEdit;

        QVBoxLayout * _mainLayout;
        QHBoxLayout * _editLayout;

        const static QString s_formatToolTip;
};

#endif
