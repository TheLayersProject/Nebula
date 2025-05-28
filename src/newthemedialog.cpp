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

#include "newthemedialog.h"

#include <Layers/ltheme.h>

using Layers::LString;
using Layers::LTheme;
using QLayers::QLButton;
using QLayers::QLGraphic;
using QLayers::QLLineEditor;

NewThemeDialog::NewThemeDialog(QWidget* parent) : QLDialog("New Theme")
{
	init_layout();
	set_icon(std::make_unique<QLGraphic>(
		":/images/new_theme.svg", QSize(26, 26)));
	set_object_name("New Theme Dialog");
	setFixedSize(430, 220);

	m_name_editor->set_object_name("Name Editor");
	m_name_editor->setFixedHeight(50);
	m_name_editor->set_pretext("Name");
	m_name_editor->left_padding()->set_value(10.0);

	connect(m_name_editor, &QLLineEditor::text_edited,
		[this](const QString& text)
		{
			if (text == "" && !m_create_button->disabled())
			{
				m_create_button->set_disabled();
			}
			else if (text != "" && m_create_button->disabled())
			{
				m_create_button->set_disabled(false);
			}
		});

	m_create_button->set_object_name("Create Button");
	m_create_button->setFixedHeight(50);
	m_create_button->set_pointing_hand_cursor();
	m_create_button->set_disabled();
	m_create_button->layout()->insertStretch(0);
	m_create_button->layout()->addStretch();
	m_create_button->text_label()->set_bold();

	connect(m_create_button, &QLButton::clicked,
		[this] { done(QDialog::Accepted); });

	apply_definition(lController.find_definition(path()));
}

LString NewThemeDialog::name() const
{
	return m_name_editor->text()->as<LString>();
}

void NewThemeDialog::init_layout()
{
	m_main_layout->setContentsMargins(15, 15, 15, 15);
	m_main_layout->setSpacing(25);
	m_main_layout->addStretch();
	m_main_layout->addWidget(m_name_editor);
	m_main_layout->addWidget(m_create_button);
	m_main_layout->addStretch();

	setLayout(m_main_layout);
}
