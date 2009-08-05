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
#include "m3uplaylist.h"
#include "songfile.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTime>

#include <QtDebug>
M3UPlaylist::M3UPlaylist ( const QString & name,QObject *parent )
        : QObject ( parent ),_fileName ( name )
{
    _listFormat="%TT. \"%s\" - %a: %D";
    if ( QFile::exists ( name ) )
    {
        QFile file ( name );
        read ( file );
    }
    else
        qWarning() << trUtf8 ( "Playlist " ) << name << trUtf8 ( " nicht gefunden." );
}

M3UPlaylist::M3UPlaylist ( QFile & file, QObject *parent )
        : QObject ( parent )
{
    _listFormat="%TT. \"%s\" - %a: %D";
    read ( file );
}

M3UPlaylist::~M3UPlaylist()
{
    while ( !_playList.isEmpty() )
        delete _playList.takeFirst();

}

void  M3UPlaylist::read ( QFile & file )
{
    if ( file.open ( QIODevice::ReadOnly ) )
    {
        _extended=false;
        QTextStream stream ( &file );
        stream.setCodec ( "UTF-8" );
        while ( !stream.atEnd() )
        {
            QString line = stream.readLine();
            if ( line == "#EXTM3U" )
            {
                _extended = true;
                continue;
            }
            SongListItem * item = new SongListItem;
            if ( _extended && line.startsWith ( "#EXTINF:" ) )
            {
                line = line.remove ( "#EXTINF:" );
                int pos = line.indexOf ( "," );
                item->length = line.left ( pos ).toInt();
                item->title = line.remove ( 0,pos+1 ).trimmed();
                item->fileName = stream.readLine();
                qDebug() << item->title << ": " << item->length << " s" << item->fileName;
            }
            else
                item->fileName = line;
            if ( QFile::exists ( item->fileName ) || QFile::exists ( dir() + "/" + item->fileName ) )
                item->exists = true;
            else
            {
                item->exists =false;
                qWarning() << item->fileName << trUtf8 ( "existiert nicht." );
            }
            _playList.append ( item );
        }
        file.close();
    }
}


QString  M3UPlaylist::fileNameForTrack ( uint track )
{
    if ( _playList[track]->exists )
    {
        QString file = _playList[track]->fileName;
        if ( ! QFile::exists ( file ) )
            file = dir() + "/" + _playList[track]->fileName;
        QFileInfo info ( file );
        return info.canonicalFilePath();
    }
    else
        return _playList[track]->fileName;
}

int  M3UPlaylist::lengthForTrack ( uint track )
{
    return _playList[track]->length;
}

QTime M3UPlaylist::timeForTrack ( uint track )
{
    QTime time;
    time = time.addSecs ( _playList[track]->length );
    return time;
}

QString  M3UPlaylist::titleForTrack ( uint track )
{
    return _playList[track]->title;
}

bool M3UPlaylist::fileForTrackExists ( uint track )
{
    return _playList[track]->exists;
}

int M3UPlaylist::size()
{
    return _playList.size();
}

QString M3UPlaylist::dir()
{
    QFileInfo info ( _fileName );
    return info.dir().absolutePath();
}

QString M3UPlaylist::formattedSonglist ()
{
    QString outlist, line;
    int i=0;
    while ( i < size() )
    {
        line = _listFormat;

        if ( _extended )
        {
            line = line.replace ( "%TT", twoDigitNumber ( i+1 ) );
            line = line.replace ( "%T", QString::number ( i+1 ) );
            line = line.replace ( "%D", timeForTrack ( i ).toString ( "m:ss" ) );
        }
        if ( fileForTrackExists ( i ) )
        {
            SongFile file ( fileNameForTrack ( i ) );
            line = line.replace ( "%s", file.title() );
            line = line.replace ( "%a", file.artist() );
            line = line.replace ( "%l", file.album() );
            line = line.replace ( "%c", file.comment() );
            line = line.replace ( "%y", QString::number ( file.year() ) );
            line = line.replace ( "%tt", twoDigitNumber ( file.track() ) );
            line = line.replace ( "%t", QString::number ( file.track() ) );
            line = line.replace ( "%g", file.genre() );
        }
        else
        {
            line = line.remove ( "%a" );
            line = line.remove ( "%l" );
            line = line.remove ( "%c" );
            line = line.remove ( "%y" );
            line = line.remove ( "%tt" );
            line = line.remove ( "%t" );
            line = line.remove ( "%g" );
            line = line.remove ( "%TT" );
            line = line.remove ( "%T" );
            line = line.remove ( "%D" );
            if ( _extended )
                line = line.replace ( "%s", titleForTrack ( i ) );
            else
            {
                line = line.replace ( "%s", fileNameForTrack ( i ) );
                line = line.remove ( "%F" );
            }
        }
        line = line.replace ( "%F", fileNameForTrack ( i ) );
        line = line.replace ( "\\t","\t");
        outlist += line + "\n";
        i++;
    }
    return outlist;
}

QString M3UPlaylist::twoDigitNumber ( int num )
{
    QString out;
    if ( num >= 0 and num < 10 )
        out += "0";
    out += QString::number ( num );
    return out;
}

QString M3UPlaylist::listFormat() const
{
    return _listFormat;
}

void M3UPlaylist::setListFormat(const QString & format)
{
    _listFormat = format;
}
QString M3UPlaylist::name() const
{
    return _fileName;
}