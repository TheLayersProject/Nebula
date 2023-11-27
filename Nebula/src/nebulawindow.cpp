/*
 * Copyright (C) 2023 The Layers Project
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
#include "opener.h"

using QLayers::QLButton;
using QLayers::QLGraphic;

NebulaWindow::NebulaWindow(QWidget* parent) :
	QLMainWindow(parent)
{
	setWindowIcon(QIcon("nebula_logo_static.png"));

	QLGraphic logo_graphic = QLGraphic("nebula_logo.svg", QSize(35, 35));
	logo_graphic.svg_renderer()->exclude_from_theme("black_holes");
	logo_graphic.svg_renderer()->exclude_from_theme("stars");

	Nebula* nebula = new Nebula;

	connect(nebula->open_button(), &QLButton::clicked,
		[this]
		{
			open_central_widget(
				new Opener(this), QLGraphic("folder.svg", QSize(25, 22)),
				"Open");
		});

	open_central_widget(nebula, logo_graphic, "Nebula");
}
