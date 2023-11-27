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

#ifndef THEMEBUTTON_H
#define THEMEBUTTON_H

#include <Layers/ltheme.h>

#include <QLayers/qllabel.h>
#include <QLayers/qlwidget.h>

class ThemeButton : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	ThemeButton(Layers::LTheme* theme, QWidget* parent = nullptr);

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init_layout();
	void init_style(Layers::LTheme* theme);

	QLayers::QLLabel* m_name_label;
	QLayers::QLLabel* m_publisher_label;
};

#endif // THEMEBUTTON_H
