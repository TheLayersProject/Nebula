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

#ifndef LINKDISPLAYER_H
#define LINKDISPLAYER_H

#include <Layers/llink.h>
#include <QLayers/qllabel.h>
#include <QLayers/qlwidget.h>

class LinkDisplayer : public QLayers::QLWidget
{
	Q_OBJECT

public:
	LinkDisplayer(QWidget* parent = nullptr);

	void set_link(Layers::LLink* link);

private:
	void init_attributes();
	void init_layout();

	QLayers::QLLabel* m_label{ new QLayers::QLLabel };

	QLayers::QLLabel* m_link_icon_label =
		new QLayers::QLLabel(
			QLayers::QLGraphic(":/images/chain_link.svg", QSize(8, 18)));
};

#endif // LINKDISPLAYER_H
