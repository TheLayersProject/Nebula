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

#ifndef NEWTHEMEDIALOG_H
#define NEWTHEMEDIALOG_H

#include <QLayers/qlbutton.h>
#include <QLayers/qldialog.h>
#include <QLayers/qllineeditor.h>

class NewThemeDialog : public QLayers::QLDialog
{
	Q_OBJECT

public:
	NewThemeDialog(QWidget* parent = nullptr);

	Layers::LString name() const;

private:
	void init_layout();

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

	QLayers::QLLineEditor* m_name_editor{ new QLayers::QLLineEditor };

	QLayers::QLButton* m_create_button{
		new QLayers::QLButton(
			QLayers::QLGraphic(":/images/check.svg", QSize(20, 15)),
			"Create")};
};

#endif // NEWTHEMEDIALOG_H
