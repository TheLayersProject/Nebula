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

#include "definitioneditor.h"

#include <QEvent>
#include <Layers/lalgorithms.h>
#include <Layers/lstring.h>

//#include "themebutton.h"

using Layers::LString;
using Layers::LDefinition;
using Layers::LTheme;
using QLayers::QLGraphic;
using QLayers::QLLineEditor;
using Vortex::VTabBar;

DefinitionEditor::DefinitionEditor(QWidget* parent) :
	QLWidget(parent)
{
	init_layout();
	set_object_name("Definition Editor");

	controller->include("QLayers (The Layers Project)/0.2.0");
	controller->include("Fusion (The Layers Project)/0.1.0");
	controller->include("Vortex (The Layers Project)/0.1.0");
	set_editor->setup_view(controller->root_definition());

	m_options_bar->setFixedHeight(50);
	m_options_bar->set_object_name("Options Bar");

	m_search_box->set_object_name("Search Box");
	m_search_box->set_pretext("Search");
	m_search_box->setFixedSize(290, 40);
	m_search_box->left_padding()->set_value(10.0);

	connect(m_search_box, &QLLineEditor::text_edited,
		[this](const QString& text)
		{
			for (SetButton* set_button : set_selector->set_buttons())
			{
				if (text.isEmpty())
				{
					set_button->setVisible(true);
				}
				else
				{
					if (set_button->name().startsWith(text) ||
						set_button->publisher().startsWith(text))
					{
						set_button->setVisible(true);
					}
					else
					{
						set_button->setVisible(false);
					}
				}
			}
		});

	set_displayer->set_object_name("Set Displayer");
	set_displayer->setFixedSize(290, 40);
	set_displayer->hide();

	set_editor->hide();

	connect(set_selector, &SetSelector::selected_with_logo,
		[this](const QString& name, const QString& publisher,
			const QLGraphic& logo)
		{
			m_search_box->hide();

			set_displayer->setup(name, publisher, logo);
			set_displayer->show();
		});

	connect(set_selector, &SetSelector::selected,
		[this](const QString& name, const QString& publisher)
		{
			m_search_box->hide();

			set_displayer->setup(name, publisher);
			set_displayer->show();
		});

	connect(set_selector, &SetSelector::selected_version,
		[this](const QString& version_tag)
		{
			set_displayer->set_version(version_tag);

			set_selector->hide();

			set_editor->show();
		});

	connect(set_displayer, &SetDisplayer::closed,
		[this]
		{
			m_search_box->show();

			set_displayer->hide();

			set_editor->hide();

			set_selector->reset();
			set_selector->show();
		});
}

void DefinitionEditor::init_layout()
{
	m_options_bar_layout->addWidget(m_search_box);
	m_options_bar_layout->addWidget(set_displayer);
	m_options_bar_layout->addStretch();
	m_options_bar_layout->setContentsMargins(8, 0, 8, 0);
	m_options_bar_layout->setSpacing(8);
	m_options_bar->setLayout(m_options_bar_layout);

	m_main_layout->addWidget(m_options_bar);
	m_main_layout->addWidget(set_selector);
	m_main_layout->addWidget(set_editor);
	m_main_layout->setContentsMargins(0, 0, 0, 0);
	m_main_layout->setSpacing(0);

	setLayout(m_main_layout);
	m_main_layout->activate();
}
