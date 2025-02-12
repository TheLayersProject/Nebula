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

#include "setdisplayer.h"

#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QVBoxLayout>

using Layers::LAttributeMap;
using Layers::LString;
using Layers::LTheme;
using Layers::LDefinition;
using Layers::LVariant;

using QLayers::QLButton;
using QLayers::QLGraphic;
using QLayers::QLLabel;

SetDisplayer::SetDisplayer(QWidget* parent) :
	QLWidget(parent)
{
	init_layout();
	set_object_name("Set Displayer");

	QGraphicsOpacityEffect* publisher_opacity = new QGraphicsOpacityEffect;
	publisher_opacity->setOpacity(0.6);

	m_logo_label->setMaximumWidth(35);

	m_name_label->set_object_name("Name Label");
	m_name_label->set_bold();
	
	m_publisher_label->setGraphicsEffect(publisher_opacity);
	m_publisher_label->set_object_name("Publisher Label");
	m_publisher_label->set_font_size_f(10.5);

	m_close_button->set_object_name("Close Button");

	connect(m_close_button, &QLButton::clicked,
		[this] { emit closed(); });
}

void SetDisplayer::set_version(const QString& version_tag)
{
	m_name_label->setText(m_name_label->text() + "/" + version_tag);
}

void SetDisplayer::setup(
	const QString& name, const QString& publisher, const QLGraphic& logo)
{
	m_name_label->setText(name);
	m_publisher_label->setText(publisher);
	m_logo_label->set_graphic(logo);
	m_logo_label->show();

	QLDefinable::update();
}

void SetDisplayer::setup(
	const QString& name, const QString& publisher)
{
	m_name_label->setText(name);
	m_publisher_label->setText(publisher);
	m_logo_label->reset();
	m_logo_label->hide();

	QLDefinable::update();
}

void SetDisplayer::init_layout()
{
	QVBoxLayout* text_layout = new QVBoxLayout;
	text_layout->addWidget(m_name_label, Qt::AlignLeft);
	text_layout->addWidget(m_publisher_label, Qt::AlignLeft);
	text_layout->setContentsMargins(0, 4, 0, 4);
	text_layout->setSpacing(0);

	QHBoxLayout* main_layout = new QHBoxLayout;
	if (m_logo_label)
		main_layout->addWidget(m_logo_label);
	main_layout->addLayout(text_layout);
	main_layout->addStretch();
	main_layout->addWidget(m_close_button);
	main_layout->setContentsMargins(5, 0, 0, 0);
	main_layout->setSpacing(8);
	setLayout(main_layout);
}
