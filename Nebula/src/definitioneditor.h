/*
 * Copyright (C) 2025 The Layers Project
 *
 * This file is part of the Nebula application.
 *
 * Nebula is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nebula is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nebula. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DEFINITIONEDITOR_H
#define DEFINITIONEDITOR_H

#include <QVBoxLayout>
#include <Layers/ldefinition.h>
#include <Layers/lcontroller.h>
#include <Layers/ltheme.h>
#include <QLayers/qldialog.h>
#include <QLayers/qllineeditor.h>
#include <QLayers/qlscrollarea.h>
#include <QLayers/qlwidget.h>
#include <Vortex/vtabbar.h>

#include "attributeeditor.h"
#include "attributeeditorgroup.h"
#include "seteditor.h"
#include "setselector.h"
#include "definitionview.h"
#include "setdisplayer.h"

class DefinitionEditor : public QLayers::QLWidget
{
	Q_OBJECT

public:
	DefinitionEditor(QWidget* parent = nullptr);

private:
	void init_layout();

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

	QHBoxLayout* m_options_bar_layout{ new QHBoxLayout };

	QLWidget* m_options_bar{ new QLWidget };

	QLayers::QLLineEditor* m_search_box{ new QLayers::QLLineEditor };

	SetDisplayer* set_displayer{ new SetDisplayer };

	SetSelector* set_selector{ new SetSelector };

	SetEditor* set_editor{ new SetEditor };

	Layers::LController* controller{ new Layers::LController };
};

#endif // DEFINITIONEDITOR_H
