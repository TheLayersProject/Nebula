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

#include "nebula.h"

#include <QVBoxLayout>

Nebula::Nebula(QWidget* parent) :
	QLWidget(parent)
{
	init_layout();
	set_object_name("Nebula");

	m_definitions_button->set_object_name("Definitions Button");
	m_definitions_button->graphic_label()->setMinimumSize(32, 32);

	m_themes_button->set_object_name("Themes Button");
	m_themes_button->graphic_label()->setMinimumWidth(32);

	m_styles_button->set_object_name("Styles Button");
	m_styles_button->graphic_label()->setMinimumWidth(32);
}

HomeButton* Nebula::definitions_button() const
{
	return m_definitions_button;
}

HomeButton* Nebula::themes_button() const
{
	return m_themes_button;
}

HomeButton* Nebula::styles_button() const
{
	return m_styles_button;
}

void Nebula::init_layout()
{
	QVBoxLayout* buttons_layout = new QVBoxLayout;
	buttons_layout->addStretch();
	buttons_layout->addWidget(m_definitions_button);
	buttons_layout->addWidget(m_themes_button);
	buttons_layout->addWidget(m_styles_button);
	buttons_layout->addStretch();

	QHBoxLayout* main_layout = new QHBoxLayout;
	main_layout->addLayout(buttons_layout);
	setLayout(main_layout);
}
