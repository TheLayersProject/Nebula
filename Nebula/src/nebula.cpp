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

#include "nebula.h"

#include <QVBoxLayout>
#include "QLayers/qllabel.h"

using QLayers::QLGraphic;
using QLayers::QLLabel;

Nebula::Nebula(QWidget* parent) :
	QLWidget(parent)
{
	init_layout();
	set_object_name("Nebula");

	m_create_button->graphic_label()->setMinimumWidth(30);
	m_create_button->text_label()->set_bold();
	m_create_button->text_label()->set_font_size(13);
	m_create_button->layout()->addStretch();
	m_create_button->setFixedWidth(180);
	m_create_button->setSizePolicy(
		QSizePolicy::Fixed, QSizePolicy::Fixed);

	m_open_button->graphic_label()->setMinimumWidth(30);
	m_open_button->text_label()->set_bold();
	m_open_button->text_label()->set_font_size(13);
	m_open_button->layout()->addStretch();
	m_open_button->setFixedWidth(180);
	m_open_button->setSizePolicy(
		QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QLayers::QLButton* Nebula::create_button() const
{
	return m_create_button;
}

QLayers::QLButton* Nebula::open_button() const
{
	return m_open_button;
}

void Nebula::init_layout()
{
	QVBoxLayout* buttons_layout = new QVBoxLayout;
	buttons_layout->addStretch();
	buttons_layout->addWidget(m_create_button);
	buttons_layout->addWidget(m_open_button);
	buttons_layout->addStretch();

	QHBoxLayout* main_layout = new QHBoxLayout;
	main_layout->addLayout(buttons_layout);
	setLayout(main_layout);
}
