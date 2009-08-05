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
#include "mainwindow.h"
#include "m3uplaylist.h"
#include "cover.h"
#include "songlistview.h"
#include "alignsettings.h"
#include "sizesettings.h"
#include "texttools.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QtDebug>
#include <QLabel>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
 : QWidget(parent)
{
    _sizeSettings = 0;
    _alignSettings = 0;
    _textTools = 0;
    _cover = 0;
    _currPlaylist = 0;
    createActions();
    createMenu();

    _mainLayout = new QVBoxLayout(this);
    _mainLayout->addWidget(_mainMenuBar);

    _viewLayout = new QHBoxLayout;

    _coverView = new CoverView;
    _songListView = new SongListView;
    _viewLayout->addWidget(_coverView);
    _viewLayout->addWidget(_songListView);

    _mainLayout->addLayout(_viewLayout);
    _mainLayout->addStretch();
// _coverLabel = new QLabel;
// _mainLayout->addWidget(_coverLabel);
    connect(_songListView, SIGNAL(songlistChanged()), this, SLOT(updateCoverView()));
    resize(1000,700);


}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    _openM3UAct = new QAction( tr( "M3U-&Playlist öffnen" ), this );
    _openM3UAct->setShortcut( tr( "Ctrl+O" ) );
    _openM3UAct->setStatusTip( tr( "Öffnet die Playlist zur Erstellung des Covers" ) );

    _saveCoverAct = new QAction( tr( "Cover speichern" ), this);
    _saveCoverAct->setShortcut( tr( "Ctrl+S" ) );
    _saveCoverAct->setStatusTip( tr( "Speichert das aktuelle Cover") );
    _saveCoverAct->setDisabled(TRUE);

    _savePlaylistAct = new QAction( tr( "Playlist als Text speichern" ), this);
    _savePlaylistAct->setShortcut( tr( "Ctrl+P" ) );
    _savePlaylistAct->setStatusTip( tr( "Speichert die aktuelle Playlist") );
    _savePlaylistAct->setDisabled(TRUE);

    _formatAlignmentAct = new QAction(tr( "Anordnung..." ),this);
    _formatAlignmentAct->setShortcut(tr ("Ctrl+A"));
    _formatAlignmentAct->setStatusTip(tr( "Anordnung der Einzelcover" ));
    _formatAlignmentAct->setDisabled(TRUE);

    _formatSizeColorAct = new QAction(tr("Größe und Farbe..."),this);
    _formatSizeColorAct->setStatusTip(tr("Einstellung von Größen und Farben"));
    _formatSizeColorAct->setDisabled(TRUE);

    _toolTextAct = new QAction(tr("Text..."),this);


    connect(_openM3UAct, SIGNAL(triggered()), this, SLOT(openM3UFile()));
    connect(_saveCoverAct, SIGNAL(triggered()), this, SLOT(saveCover()));
    connect(_savePlaylistAct, SIGNAL(triggered()), this, SLOT(savePlaylist()));
    connect(_formatAlignmentAct, SIGNAL(triggered()), this, SLOT(formatAlignment()));
    connect(_formatSizeColorAct, SIGNAL(triggered()), this, SLOT(setSizeColor()));
    connect(_toolTextAct, SIGNAL(triggered()), this, SLOT(setText()));
}

void MainWindow::createMenu()
{
    _mainMenuBar = new QMenuBar();

    _fileMenu = _mainMenuBar->addMenu( tr( "Datei" ) );
    _fileMenu->addAction( _openM3UAct );
    _fileMenu->addSeparator();
    _fileMenu->addAction( _saveCoverAct );
    _fileMenu->addAction( _savePlaylistAct );

    _formatMenu = _mainMenuBar->addMenu( tr( "Werkzeuge" ));
    _formatMenu->addAction( _formatAlignmentAct  );
    _formatMenu->addAction( _formatSizeColorAct );
    _formatMenu->addAction( _toolTextAct );

    _mainMenuBar->addSeparator();
    _helpMenu = _mainMenuBar->addMenu( tr( "Hilfe" ) );
}

void MainWindow::openM3UFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("M3UPlaylist öffnen"),
                                            QDir::homePath(), tr("Playlists (*.m3u)"));
    if (fileName.isEmpty())
        return;
    if (_currPlaylist != 0)
        m3uList.prepend(_currPlaylist);
    delete _cover;
    _currPlaylist = new M3UPlaylist(fileName);
    _cover = new Cover(_currPlaylist);
    _songListView->setPlaylist(_currPlaylist);
    _saveCoverAct->setDisabled(FALSE);
    _savePlaylistAct->setDisabled(FALSE);
    _formatAlignmentAct->setDisabled(FALSE);
    _formatSizeColorAct->setDisabled(FALSE);
    connect(_cover,SIGNAL(coverChanged()),this, SLOT(updateCoverView()));    _coverView->setScene(_cover->scene());
    connect(_songListView, SIGNAL(addToCover(QString)), _cover, SLOT(addText(QString)));
    updateCoverView();
}

void MainWindow::saveCover()
{
    if (_cover == 0)
        return;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Cover speichern"),
            _cover->lastDir(), tr("Bilder (*.png *.jpg)"));
    if (! _cover->saveCover(fileName))
        QMessageBox::warning(this, tr("Speichern nicht möglich"),tr("Das Speichern der Playlist war nicht möglich. Überprüfen Sie, ob der Datenträger beschreibbar ist."));
}

void MainWindow::updateCoverView()
{
    if (_cover == 0)
        return;
    _coverView->fitInView(_coverView->sceneRect());
}

void MainWindow::savePlaylist()
{
    if (_currPlaylist == 0)
        return;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Playlist speichern"),
            _cover->lastDir(), tr("Textdateien (*.txt)"));
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream out(&file);
        QString str = _currPlaylist->formattedSonglist();
        out << str;
    }
    else
        QMessageBox::warning(this, tr("Speichern nicht möglich"),tr("Das Speichern der Playlist war nicht möglich. Überprüfen Sie, ob der Datenträger beschreibbar ist."));
}

void MainWindow::formatAlignment()
{
    if (_alignSettings == 0)
        _alignSettings=new AlignSettings(_cover);
    _alignSettings->show();
}

void MainWindow::setSizeColor()
{
    if (_sizeSettings == 0)
        _sizeSettings = new SizeSettings(_cover);
    _sizeSettings->show();
}

void MainWindow::setText()
{
        if (_textTools == 0)
        _textTools = new TextTools(_cover);
        _textTools->show();
}

CoverView::CoverView ( QWidget * parent)
    : QGraphicsView(parent)
{
    QSizePolicy policy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    policy.setHeightForWidth(TRUE);
    setSizePolicy(policy);
}

CoverView::CoverView ( QGraphicsScene * scene, QWidget * parent)
    : QGraphicsView(scene,parent)
{
}

CoverView::~CoverView ()
{
}

int CoverView::heightForWidth(int w) const
{
    return w;
}

QSize CoverView::sizeHint() const
{
    return QSize(700,700);
}

void CoverView::resizeEvent ( QResizeEvent * event )
{
    fitInView(sceneRect());
}