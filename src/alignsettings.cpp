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
#include "alignsettings.h"
#include "cover.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QDialogButtonBox>


AlignSettings::AlignSettings(Cover * cover, QWidget *parent)
        : QWidget(parent)
{
    _cover = cover;
    createLayout();
    init();
    connect(_hAlignButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(setHAlignment(int)));
    connect(_vAlignButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(setVAlignment(int)));
    connect(_vSpaceBox, SIGNAL(valueChanged(int)), _cover, SLOT(setVSpace(int)));
    connect(_hSpaceBox, SIGNAL(valueChanged(int)), _cover, SLOT(setHSpace(int)));
    connect(_topMarginBox, SIGNAL(valueChanged(int)), _cover, SLOT(setTopMargin(int)));
    connect(_leftMarginBox, SIGNAL(valueChanged(int)), _cover, SLOT(setLeftMargin(int)));

    connect(_preferButtonGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(setPreferedLayout(QAbstractButton*)));
    connect(_rowBox,SIGNAL(valueChanged(int)), _cover, SLOT(setRows(int)));
    connect(_underfullRowBox,SIGNAL(valueChanged(int)), _cover, SLOT(setUnderfullRow(int)));
    connect(_cover,SIGNAL(coverChanged()),this,SLOT(init()));
}


AlignSettings::~AlignSettings()
{
}

void AlignSettings::createLayout()
{
    setWindowTitle(tr("Anordnung"));
    _mainLayout = new QVBoxLayout(this);

    _preferLayout= new QHBoxLayout;

    _preferButtonGroup = new QButtonGroup;

    _preferHButton = new QPushButton(tr("H"));
    _preferHButton->setToolTip(tr("Horizontale Anordnung bevorzugen"));
    _preferVButton = new QPushButton(tr("V"));
    _preferVButton->setToolTip(tr("Vertikale Anordnung bevorzugen"));
    _preferManualRowsButton = new QPushButton(tr("Man"));
    _preferManualRowsButton->setToolTip(tr("Zeilenanzahl manuell auswählen"));

    _preferHButton->setCheckable(TRUE);
    _preferVButton->setCheckable(TRUE);
    _preferManualRowsButton->setCheckable(TRUE);

    _preferButtonGroup->addButton(_preferHButton);
    _preferButtonGroup->addButton(_preferVButton);
    _preferButtonGroup->addButton(_preferManualRowsButton);

    _preferLayout->addWidget(_preferHButton);
    _preferLayout->addWidget(_preferVButton);
    _preferLayout->addWidget(_preferManualRowsButton);
    _preferLayout->addStretch();

    _mainLayout->addLayout(_preferLayout);

    _rowLayout = new QHBoxLayout;

    _rowBoxLabel = new QLabel(tr("Zeilen:"));
    _rowBox = new QSpinBox;
    _rowBox->setToolTip(tr("Anzahl der Zeilen"));

    _rowLayout->addWidget( _rowBoxLabel );
    _rowLayout->addWidget( _rowBox );
    _rowLayout->addStretch();

    _underfullLayout = new QHBoxLayout;

    _underfullRowLabel = new QLabel(tr("Rest-Zeile"));
    _underfullRowBox = new QSpinBox;
    _underfullRowBox->setToolTip(tr("Nummer der nicht voll gefüllten Zeile"));

    _underfullLayout->addWidget( _underfullRowLabel);
    _underfullLayout->addWidget( _underfullRowBox);
    _underfullLayout->addStretch();

    _mainLayout->addLayout( _rowLayout );
    _mainLayout->addLayout( _underfullLayout );



    _hGroupBox = new QGroupBox(tr("Horizontales Layout"));

    _hLayout = new QVBoxLayout;

    _hButtonLayout = new  QHBoxLayout;

    _hAlignButtonGroup = new QButtonGroup;

    _hAlignLeftButton = new QPushButton(tr("Links"));
    _hAlignLeftButton->setToolTip(tr("Linksbündig"));
    _hAlignCenterButton = new QPushButton(tr("Zentriert"));
    _hAlignCenterButton->setToolTip(tr("Zentriert"));
    _hAlignRightButton = new QPushButton(tr("Rechts"));
    _hAlignRightButton->setToolTip(tr("Rechtbündig"));
    _hAlignEqualButton = new QPushButton(tr("Gleich"));
    _hAlignEqualButton->setToolTip(tr("Gleichverteilt"));
    _hAlignManualButton = new QPushButton(tr("Manuell"));
    _hAlignManualButton->setToolTip(tr("Verteilung manuell einstellen"));
    _hAlignRandomButton = new QPushButton(tr("Zufällig"));
    _hAlignRandomButton->setToolTip(tr("Zufällig verteilen"));

    _hAlignLeftButton->setCheckable(TRUE);
    _hAlignCenterButton->setCheckable(TRUE);
    _hAlignRightButton->setCheckable(TRUE);
    _hAlignEqualButton->setCheckable(TRUE);
    _hAlignManualButton->setCheckable(TRUE);
    _hAlignRandomButton->setCheckable(TRUE);

    _hAlignButtonGroup->addButton(_hAlignLeftButton,Cover::left);
    _hAlignButtonGroup->addButton(_hAlignCenterButton,Cover::center);
    _hAlignButtonGroup->addButton(_hAlignRightButton,Cover::right);
    _hAlignButtonGroup->addButton(_hAlignEqualButton,Cover::equal);
    _hAlignButtonGroup->addButton(_hAlignManualButton,Cover::manual);
    _hAlignButtonGroup->addButton(_hAlignRandomButton,Cover::random);

    _hButtonLayout->addWidget(_hAlignLeftButton);
    _hButtonLayout->addWidget(_hAlignCenterButton);
    _hButtonLayout->addWidget(_hAlignRightButton);
    _hButtonLayout->addWidget(_hAlignEqualButton);
    _hButtonLayout->addWidget(_hAlignManualButton);
    _hButtonLayout->addWidget(_hAlignRandomButton);
    _hButtonLayout->addStretch();

    _hManualLayout = new QHBoxLayout;

    _leftMarginLabel = new QLabel(tr("Linker Rand :"));
    _hSpaceLabel = new QLabel(tr("Abstand :"));
    _leftMarginBox = new QSpinBox;
    _leftMarginBox->setToolTip(tr("Abstand vom linken Rand"));
    _hSpaceBox = new QSpinBox;
    _hSpaceBox->setToolTip(tr("Abstand der Einzelcover untereinander"));

    _hManualLayout->addWidget(_leftMarginLabel);
    _hManualLayout->addWidget(_leftMarginBox);
    _hManualLayout->addWidget(_hSpaceLabel);
    _hManualLayout->addWidget(_hSpaceBox);
    _hManualLayout->addStretch();

    _hLayout->addLayout(_hButtonLayout);
    _hLayout->addLayout(_hManualLayout);

    _hGroupBox->setLayout(_hLayout);

    _mainLayout->addWidget(_hGroupBox);

    _vGroupBox = new QGroupBox(tr("Vertikales Layout"));
    _vLayout = new QVBoxLayout;
    _vButtonLayout = new  QHBoxLayout;
    _vManualLayout = new QHBoxLayout;

    _vAlignButtonGroup = new QButtonGroup;

    _vAlignTopButton = new QPushButton(tr("Oben"));
    _vAlignTopButton->setToolTip(tr("Oben abschließend"));
    _vAlignCenterButton = new QPushButton(tr("Zentriert"));
    _vAlignCenterButton->setToolTip(tr("Vertikal Zentriert"));
    _vAlignBottomButton = new QPushButton(tr("Unten"));
    _vAlignBottomButton->setToolTip(tr("Unten abschließend"));
    _vAlignEqualButton = new QPushButton(tr("Gleich"));
    _vAlignEqualButton->setToolTip(tr("Gleichverteilt"));
    _vAlignManualButton = new QPushButton(tr("Manuell"));
    _vAlignManualButton->setToolTip(tr("Verteilung manuell einstellen"));
    _vAlignRandomButton = new QPushButton(tr("Zufällig"));
    _vAlignRandomButton->setToolTip(tr("Zufällig verteilen"));

    _vAlignTopButton->setCheckable(TRUE);
    _vAlignCenterButton->setCheckable(TRUE);
    _vAlignBottomButton->setCheckable(TRUE);
    _vAlignEqualButton->setCheckable(TRUE);
    _vAlignManualButton->setCheckable(TRUE);
    _vAlignRandomButton->setCheckable(TRUE);

    _vAlignButtonGroup->addButton(_vAlignTopButton,Cover::top);
    _vAlignButtonGroup->addButton(_vAlignCenterButton,Cover::center);
    _vAlignButtonGroup->addButton(_vAlignBottomButton,Cover::bottom);
    _vAlignButtonGroup->addButton(_vAlignEqualButton,Cover::equal);
    _vAlignButtonGroup->addButton(_vAlignManualButton,Cover::manual);
    _vAlignButtonGroup->addButton(_vAlignRandomButton,Cover::random);

    _vButtonLayout->addWidget(_vAlignTopButton);
    _vButtonLayout->addWidget(_vAlignCenterButton);
    _vButtonLayout->addWidget(_vAlignBottomButton);
    _vButtonLayout->addWidget(_vAlignEqualButton);
    _vButtonLayout->addWidget(_vAlignManualButton);
    _vButtonLayout->addWidget(_vAlignRandomButton);
    _vButtonLayout->addStretch();

    _topMarginBox= new QSpinBox();
    _topMarginBox->setToolTip(tr("Abstand vom oberen Rand"));
    _vSpaceBox = new QSpinBox();
    _vSpaceBox->setToolTip(tr("Abstand vom unteren Rand"));
    _vSpaceLabel = new QLabel("Abstand: ");
    _topMarginLabel = new QLabel(tr("Oberer Rand: "));

    _vManualLayout->addWidget(_topMarginLabel);
    _vManualLayout->addWidget(_topMarginBox);
    _vManualLayout->addWidget(_vSpaceLabel);
    _vManualLayout->addWidget(_vSpaceBox);
    _vManualLayout->addStretch();

    _vLayout->addLayout(_vButtonLayout);
    _vLayout->addLayout(_vManualLayout);

    _vGroupBox->setLayout(_vLayout);

    _mainLayout->addWidget(_vGroupBox);
}

void AlignSettings::init()
{
    _vAlignButtonGroup->button(_cover->vAlignment())->setChecked(TRUE);
    _hAlignButtonGroup->button(_cover->hAlignment())->setChecked(TRUE);
    _rowBox->setDisabled(TRUE);
    if (_cover->manRows())
    {
        _preferManualRowsButton->setChecked(TRUE);
        _rowBox->setDisabled(FALSE);
    }
    else if (_cover->preferVertical())
        _preferVButton->setChecked(TRUE);
    else
        _preferHButton->setChecked(TRUE);
    _underfullRowBox->setRange(1,_cover->rows());
    _underfullRowBox->setValue(_cover->underfullRow());
    _rowBox->setRange(1,_cover->imageListSize());
    _rowBox->setValue(_cover->rows());
    _vSpaceBox->setRange(-_cover->coverSize(),_cover->coverSize());
    _hSpaceBox->setRange(-_cover->coverSize(),_cover->coverSize());
    _topMarginBox->setRange(-_cover->coverSize(),_cover->coverSize());
    _leftMarginBox->setRange(-_cover->coverSize(),_cover->coverSize());
    if(_hAlignManualButton->isChecked())
        ;
}

void AlignSettings::setHAlignment(int a)
{
    _cover->setHAlignment((Cover::CoverAlign)a);
    _hSpaceBox->setEnabled(_hAlignManualButton->isChecked());
    _leftMarginBox->setEnabled(_hAlignManualButton->isChecked());
}

void AlignSettings::setVAlignment(int a)
{
    _cover->setVAlignment((Cover::CoverAlign)a);
    _vSpaceBox->setEnabled(_vAlignManualButton->isChecked());
    _topMarginBox->setEnabled(_vAlignManualButton->isChecked());
}

void AlignSettings::setPreferedLayout(QAbstractButton * button)
{
    if (button == _preferVButton)
    {
        _cover->setManRows(FALSE);
        _cover->setPreferVertical(TRUE);
    }
    else if (button == _preferHButton)
    {
        _cover->setPreferVertical(FALSE);
        _cover->setManRows(FALSE);
    }
    else
        _cover->setManRows(TRUE);
}
