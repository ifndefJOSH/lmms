/*
 * MeterModel.cpp - model for meter specification
 *
 * Copyright (c) 2008-2010 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 *
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#include "MeterModel.h"
#include "AutomationClip.h"


namespace lmms
{

MeterModel::MeterModel( Model * _parent ) :
	Model( _parent ),
	m_numeratorModel(4, 1, 32, this, tr("Numerator")),
	m_denominatorModel(4, 1, 32, this, tr("Denominator"), false, true)
{
	connect( &m_numeratorModel, SIGNAL(dataChanged()),
			this, SIGNAL(dataChanged()), Qt::DirectConnection );
	connect( &m_denominatorModel, SIGNAL(dataChanged()),
			this, SIGNAL(dataChanged()), Qt::DirectConnection );
}


void MeterModel::reset()
{
	m_numeratorModel.setValue( 4 );
	m_denominatorModel.setValue( 4 );

	AutomationClip::globalAutomationClip( &m_numeratorModel )->clear();
	AutomationClip::globalAutomationClip( &m_denominatorModel )->clear();
}




void MeterModel::saveSettings( QDomDocument & _doc, QDomElement & _this,
								const QString & _name )
{
	m_numeratorModel.saveSettings( _doc, _this, _name + "_numerator" );
	m_denominatorModel.saveSettings( _doc, _this, _name + "_denominator" );
}




void MeterModel::loadSettings( const QDomElement & _this,
								const QString & _name )
{
	// Reset the denominator model to only accept powers of two and then
	// if it encounters a non-base2 denominator, it will disable this itself
	m_denominatorModel.setRestrictToTwoPowers(true);
	m_numeratorModel.loadSettings( _this, _name + "_numerator" );
	m_denominatorModel.loadSettings( _this, _name + "_denominator" );
}


} // namespace lmms
