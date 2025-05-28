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

#include "linkdisplayer.h"

#include <QHBoxLayout>

LinkDisplayer::LinkDisplayer(QWidget* parent) : QLWidget(parent)
{
	init_layout();
	setFixedHeight(24);
	set_object_name("Link Displayer");

	m_link_icon_label->set_object_name("Icon Label");

	m_label->set_object_name("Text Label");
	m_label->set_font_size_f(10.5);
}

void LinkDisplayer::set_link(Layers::LLink* link)
{
	m_label->setText(link->path().c_str());
}

void LinkDisplayer::init_layout()
{
	QHBoxLayout* main_layout = new QHBoxLayout;
	main_layout->addWidget(m_link_icon_label);
	main_layout->addWidget(m_label);
	main_layout->setContentsMargins(8, 0, 8, 0);
	main_layout->setSpacing(5);

	setLayout(main_layout);
}
