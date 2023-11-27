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

#ifndef NEBULA_H
#define NEBULA_H

#include <QLayers/qlbutton.h>
#include <QLayers/qlwidget.h>

class Nebula : public QLayers::QLWidget
{
	Q_OBJECT

public:
	Nebula(QWidget* parent = nullptr);

	QLayers::QLButton* create_button() const;

	QLayers::QLButton* open_button() const;

private:
	void init_layout();

	QLayers::QLButton* m_create_button{
		new QLayers::QLButton(
			QLayers::QLGraphic(":/images/new_theme.svg", QSize(20, 20)),
			"Create") };

	QLayers::QLButton* m_open_button{
		new QLayers::QLButton(
			QLayers::QLGraphic("folder.svg", QSize(25, 22)),
			"Open") };
};

#endif // NEBULA_H
