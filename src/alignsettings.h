/***************************************************************************
 *   Copyright (C) 2007 by David Rauh   *
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
#ifndef ALIGNSETTINGS_H
#define ALIGNSETTINGS_H

#include <QWidget>

class Cover;

class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QButtonGroup;
class QPushButton;
class QSpinBox;
class QCheckBox;
class QDialogButtonBox;
class QAbstractButton;
class QLabel;

/**
	@author David Rauh <dave@bolivien>
*/
class AlignSettings : public QWidget
{
    Q_OBJECT
public:
    AlignSettings(Cover * cover, QWidget *parent = 0);
    ~AlignSettings();

private slots:
        void setPreferedLayout(QAbstractButton * button);
        void setHAlignment(int a);
        void setVAlignment(int a);
        void init();
private:
    void createLayout();

    Cover * _cover;

    QVBoxLayout * _mainLayout;
    QVBoxLayout * _hLayout;
    QVBoxLayout * _vLayout;

    QHBoxLayout * _preferLayout;
    QHBoxLayout * _rowLayout;
    QHBoxLayout * _underfullLayout;
    QHBoxLayout * _hButtonLayout;
    QHBoxLayout * _hManualLayout;
    QHBoxLayout * _vButtonLayout;
    QHBoxLayout * _vManualLayout;

    QGroupBox * _hGroupBox;
    QGroupBox * _vGroupBox;

    QButtonGroup * _preferButtonGroup;
    QButtonGroup * _hAlignButtonGroup;
    QButtonGroup * _vAlignButtonGroup;

    QPushButton * _preferHButton;
    QPushButton * _preferVButton;
    QPushButton * _preferManualRowsButton;
    QPushButton * _hAlignLeftButton;
    QPushButton * _hAlignCenterButton;
    QPushButton * _hAlignRightButton;
    QPushButton * _hAlignEqualButton;
    QPushButton * _hAlignManualButton;
    QPushButton * _hAlignRandomButton;
    QPushButton * _vAlignTopButton;
    QPushButton * _vAlignCenterButton;
    QPushButton * _vAlignBottomButton;
    QPushButton * _vAlignEqualButton;
    QPushButton * _vAlignManualButton;
    QPushButton * _vAlignRandomButton;

    QLabel * _rowBoxLabel;
    QLabel * _leftMarginLabel;
    QLabel * _topMarginLabel;
    QLabel * _hSpaceLabel;
    QLabel * _vSpaceLabel;
    QLabel * _underfullRowLabel;

    QSpinBox * _leftMarginBox;
    QSpinBox * _hSpaceBox;
    QSpinBox * _topMarginBox;
    QSpinBox * _vSpaceBox;
    QSpinBox * _underfullRowBox;
    QSpinBox * _rowBox;

    QDialogButtonBox * _dialogButtonBox;
};

#endif
