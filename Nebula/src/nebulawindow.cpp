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

#include "nebulawindow.h"

#include <QLayers/qlgraphic.h>

#include "nebula.h"
#include "definitioneditor.h"
#include "themeeditor.h"

using QLayers::QLButton;
using QLayers::QLGraphic;

NebulaWindow::NebulaWindow(QWidget* parent) :
	VMainWindow(parent)
{
	setWindowIcon(QIcon(":/images/nebula_logo.svg"));

	QLGraphic logo_graphic = QLGraphic(":/images/nebula_logo.svg", QSize(35, 31));
	logo_graphic.svg_renderer()->exclude_from_theme("black_holes");
	logo_graphic.svg_renderer()->exclude_from_theme("stars");
	logo_graphic.svg_renderer()->exclude_from_theme("nebula2");
	logo_graphic.svg_renderer()->exclude_from_theme("nebula3");
	logo_graphic.svg_renderer()->exclude_from_theme("nebula4");
	logo_graphic.svg_renderer()->exclude_from_theme("nebula5");

	Nebula* nebula = new Nebula;

	connect(nebula->definitions_button(), &HomeButton::clicked,
		[this]
		{
			open_central_widget(
				new DefinitionEditor(this), QLGraphic(":/images/definitions.svg", QSize(29, 18)),
				"Definitions");
		});

	connect(nebula->themes_button(), &HomeButton::clicked,
		[this]
		{
			open_central_widget(
				new ThemeEditor(this), QLGraphic(":/images/themes.svg", QSize(25, 25)),
				"Themes");
		});

	open_central_widget(nebula, logo_graphic, "Nebula");
}
