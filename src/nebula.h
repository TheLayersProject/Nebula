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

#ifndef NEBULA_H
#define NEBULA_H

#include <QLayers/qlbutton.h>
#include <QLayers/qlwidget.h>

#include "homebutton.h"

class Nebula : public QLayers::QLWidget
{
	Q_OBJECT

public:
	Nebula(QWidget* parent = nullptr);

	HomeButton* definitions_button() const;

	HomeButton* themes_button() const;

	HomeButton* styles_button() const;

private:
	void init_layout();

	HomeButton* m_definitions_button{
		new HomeButton(
			std::make_unique<QLayers::QLGraphic>(
				":/images/definitions.svg", QSize(30, 19)),
			"Definitions",
			"Define your applications") };
			//"Define the default values and structure of your widgets") };

	HomeButton* m_themes_button{
		new HomeButton(
			std::make_unique<QLayers::QLGraphic>(
				":/images/themes.svg", QSize(30, 30)),
			"Themes",
			"Control a universe of applications") };
			//"Create themes that can be applied to any Layers app") };

	HomeButton* m_styles_button{
		new HomeButton(
			std::make_unique<QLayers::QLGraphic>(
				":/images/styles.svg", QSize(26, 25)),
			"Styles",
			"Redefine applications") };
			//"Craft styles that illuminate apps through the cosmic void") };
			//"Create styles to command your apps and make them shine") };
			//"Create styles that customize specifics of any Layers app") };
};

#endif // NEBULA_H
