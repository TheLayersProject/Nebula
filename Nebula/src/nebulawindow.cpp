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

	Nebula* nebula = new Nebula;

	connect(nebula->definitions_button(), &HomeButton::clicked,
		[this]
		{
			open_central_widget(
				new DefinitionEditor(this),
				std::make_unique<QLayers::QLGraphic>(
					":/images/definitions.svg", QSize(29, 18)),
				"Definitions");
		});

	connect(nebula->themes_button(), &HomeButton::clicked,
		[this]
		{
			open_central_widget(
				new ThemeEditor(this),
				std::make_unique<QLayers::QLGraphic>(
					":/images/themes.svg", QSize(25, 25)),
				"Themes");
		});

	std::unique_ptr<QLGraphic> tab_logo =
		std::make_unique<QLGraphic>(":/images/nebula_logo.svg", QSize(35, 31));
	tab_logo->svg_renderer()->exclude_from_theme("black_holes");
	tab_logo->svg_renderer()->exclude_from_theme("stars");
	tab_logo->svg_renderer()->exclude_from_theme("nebula2");
	tab_logo->svg_renderer()->exclude_from_theme("nebula3");
	tab_logo->svg_renderer()->exclude_from_theme("nebula4");
	tab_logo->svg_renderer()->exclude_from_theme("nebula5");

	open_central_widget(nebula, std::move(tab_logo), "Nebula");
}
