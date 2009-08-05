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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsView>

class Cover;
class SongListView;
class CoverView;
class SizeSettings;
class AlignSettings;
class TextTools;

class QAction;
class QMenuBar;
class QMenu;
class QVBoxLayout;
class QLabel;
class M3UPlaylist;
class QGraphicsView;
class QHBoxLayout;

#include <QList>
/**
    @author David Raug <d.rauh@freenet.de>
*/
class MainWindow : public QWidget
{
        Q_OBJECT
    public:
        MainWindow ( QWidget *parent = 0 );

        ~MainWindow();
    public slots:
        void openM3UFile();
        void saveCover();
        void savePlaylist();
        void updateCoverView();
        void formatAlignment();
        void setSizeColor();
        void setText();
    private:
        void createActions();
        void createMenu();

        Cover * _cover;
        M3UPlaylist * _currPlaylist;
        QList<M3UPlaylist *> m3uList;
        //QString _currM3UFile;

        QVBoxLayout * _mainLayout;
        QHBoxLayout * _viewLayout;

        QAction * _openM3UAct;
        QAction * _saveCoverAct;
        QAction * _savePlaylistAct;
        QAction * _formatAlignmentAct;
        QAction * _formatSizeColorAct;
        QAction * _toolTextAct;

        QMenuBar * _mainMenuBar;

        QLabel * _coverLabel;

        QMenu * _fileMenu;
        QMenu * _helpMenu;
        QMenu * _formatMenu;

        SongListView * _songListView;
        CoverView * _coverView;
        SizeSettings * _sizeSettings;
        AlignSettings * _alignSettings;
        TextTools * _textTools;
};

class CoverView : public QGraphicsView
{
    public:
        CoverView ( QWidget * parent = 0 );
        CoverView ( QGraphicsScene * scene, QWidget * parent = 0 );
        ~CoverView ();
        int heightForWidth(int w) const;
        QSize sizeHint() const;
    protected:
        void resizeEvent ( QResizeEvent * event );
};

#endif
