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

#include "opener.h"

#include "QLayers/qlapplication.h"

#include "editor.h"
#include "nebulawindow.h"
#include "themebutton.h"

using Layers::LTheme;

Opener::Opener(NebulaWindow* window, QWidget* parent) :
	m_window{ window }, QLWidget(parent)
{
	init_theme_scroller();
	init_layout();
	set_object_name("Opener");

	m_theme_scroller->set_object_name("Theme Scroller");
}

void Opener::init_layout()
{
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->addWidget(m_theme_scroller);
	setLayout(main_layout);
}

void Opener::init_theme_scroller()
{
	for (LTheme* theme : qLayersApp->themes())
		if (!theme->publisher().empty())
		{
			ThemeButton* theme_button = new ThemeButton(theme);
			m_theme_vbox->addWidget(theme_button);

			connect(theme_button, &ThemeButton::clicked,
				[this, theme]
				{
					m_window->open_central_widget(new Editor(theme),
					theme->name().c_str());
				});
		}

	m_theme_vbox->addStretch();

	m_theme_scroller_widget->setLayout(m_theme_vbox);
	m_theme_scroller->setWidget(m_theme_scroller_widget);
}
