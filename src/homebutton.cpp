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

#include "homebutton.h"

#include <QMouseEvent>
#include <Layers/lobjectfactory.h>

using Layers::LAttribute;
using QLayers::QLGraphic;
using QLayers::QLLabel;

HomeButton::HomeButton(
	std::unique_ptr<QLGraphic> graphic,
	const QString& title,
	const QString& description,
	QWidget* parent) :
	m_graphic_label{ new QLLabel(std::move(graphic)) },
	m_title_label{ new QLLabel(title) },
	m_description_label{ new QLLabel(description) },
	QLWidget(parent)
{
	init();

	m_corner_radii_top_left->set_value(7.0);
	m_corner_radii_top_right->set_value(7.0);
	m_corner_radii_bottom_left->set_value(7.0);
	m_corner_radii_bottom_right->set_value(7.0);
}

QLLabel* HomeButton::graphic_label() const
{
	return m_graphic_label;
}

QHBoxLayout* HomeButton::layout() const
{
	return m_main_layout;
}

void HomeButton::set_padding(int padding)
{
	m_main_layout->setContentsMargins(padding, padding, padding, padding);
}

void HomeButton::set_padding(int left, int top, int right, int bottom)
{
	m_main_layout->setContentsMargins(left, top, right, bottom);
}

QLLabel* HomeButton::title_label() const
{
	return m_title_label;
}

bool HomeButton::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			emit clicked();
		}
	}
	else if (event->type() == QEvent::Enter)
	{
		m_select_states->set_state("Selected");
		setCursor(Qt::PointingHandCursor);
	}
	else if (event->type() == QEvent::Leave)
	{
		m_select_states->set_state("Unselected");
		unsetCursor();
	}

	QLWidget::eventFilter(object, event);

	return false;
}

void HomeButton::init()
{
	init_layout();
	installEventFilter(this);
	add_state_pool(m_select_states);

	m_select_states->set_state("Unselected");

	//m_button_opacity->setOpacity(1.0);
	//setGraphicsEffect(m_button_opacity);
	setFixedSize(310, 60);

	if (m_graphic_label)
	{
		m_graphic_label->setAlignment(Qt::AlignCenter);
		m_graphic_label->set_object_name("Graphic");

		m_graphic_label->graphic()->svg_renderer()->color()->set_value(
			"#808080");
		//Layers::lMake<LAttribute>(
		//	m_graphic_label->graphic()->svg_renderer()->color(),
		//	"Selected", "#c0c0c0");
		//m_graphic_label->graphic()->svg_renderer()->color()->create_state(
		//	"Selected", "#c0c0c0");
	}

	m_title_label->set_object_name("Title Label");
	m_title_label->set_bold();
	m_title_label->set_font_size(13);

	QGraphicsOpacityEffect* description_opacity = new QGraphicsOpacityEffect;
	description_opacity->setOpacity(0.6);
	m_description_label->setGraphicsEffect(description_opacity);

	m_description_label->set_object_name("Description Label");
	m_description_label->set_font_size(11);
	m_description_label->setWordWrap(true);
}

void HomeButton::init_layout()
{
	QVBoxLayout* left_layout = new QVBoxLayout;
	left_layout->setSpacing(5);
	left_layout->setContentsMargins(0, 0, 0, 0);
	left_layout->addWidget(m_graphic_label);
	left_layout->addStretch();

	QVBoxLayout* right_layout = new QVBoxLayout;
	right_layout->setSpacing(5);
	right_layout->setContentsMargins(0, 0, 0, 0);
	right_layout->addWidget(m_title_label);
	right_layout->addWidget(m_description_label);
	right_layout->addStretch();

	m_main_layout->addLayout(left_layout);
	m_main_layout->addLayout(right_layout);
	m_main_layout->setStretchFactor(left_layout, 0);
	m_main_layout->setStretchFactor(right_layout, 1);
	setLayout(m_main_layout);

	m_graphic_label->setAlignment(Qt::AlignTop);
}
