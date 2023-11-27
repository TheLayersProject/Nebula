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

#include "themebutton.h"

#include <QMouseEvent>
#include <QVBoxLayout>

using Layers::LAttributeMap;
using Layers::LString;
using Layers::LTheme;
using Layers::LThemeItem;
using Layers::LVariant;

using QLayers::QLLabel;

ThemeButton::ThemeButton(LTheme* theme, QWidget* parent) :
	m_name_label{ new QLLabel(theme->name().c_str()) },
	m_publisher_label{ new QLLabel(theme->publisher().c_str()) },
	QLWidget(parent)
{
	init_layout();
	init_style(theme);
	installEventFilter(this);
	setFixedHeight(60);
	set_corner_radii(5.0);
	border_thickness()->set_value(2.0);

	m_name_label->set_bold();

	m_publisher_label->set_font_size_f(10.5);
}

bool ThemeButton::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::Enter)
	{
		setCursor(Qt::PointingHandCursor);
	}
	else if (event->type() == QEvent::Leave)
	{
		unsetCursor();
	}
	else if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
			emit clicked();
	}

	return false;
}

void ThemeButton::init_layout()
{
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->addWidget(m_name_label, Qt::AlignLeft);
	main_layout->addWidget(m_publisher_label, Qt::AlignLeft);
	main_layout->setContentsMargins(17, 9, 6, 8);
	main_layout->setSpacing(0);
	setLayout(main_layout);
}

void ThemeButton::init_style(LTheme* theme)
{
	std::map<LString, LThemeItem*> theme_items =
		theme->load_file((theme->directory() / "app.json").string().c_str());

	if (theme_items.find("App") != theme_items.end())
	{
		LAttributeMap attributes = theme_items["App"]->attributes();

		if (attributes.find("Foreground") != attributes.end())
		{
			LVariant forground_val = attributes["Foreground"]->value();

			m_name_label->text_color()->set_value(forground_val);
			m_publisher_label->text_color()->set_value(forground_val);
		}

		if (attributes.find("Primary") != attributes.end())
			fill()->set_value(attributes["Primary"]->value());

		if (attributes.find("Tertiary") != attributes.end())
			border_fill()->set_value(attributes["Tertiary"]->value());
	}

	for (const auto& [key, theme_item] : theme_items)
		delete theme_item;

	theme_items.clear();
}
