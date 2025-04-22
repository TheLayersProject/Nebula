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

#ifndef SETBUTTON_H
#define SETBUTTON_H

#include <Layers/ltheme.h>

#include <QLayers/qllabel.h>
#include <QLayers/qlwidget.h>

class SetButton : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	SetButton(const std::filesystem::path& set_path, QWidget* parent = nullptr);

	QLayers::QLGraphic* logo() const;

	QString name() const;

	std::filesystem::path path() const;

	QString publisher() const;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init_labels(const std::filesystem::path& set_path);
	void init_layout();

	QLayers::QLLabel* m_logo_label{ new QLayers::QLLabel };

	QLayers::QLLabel* m_name_label{ new QLayers::QLLabel };
	QLayers::QLLabel* m_publisher_label{ new QLayers::QLLabel };

	std::filesystem::path m_set_path;
};

#endif // SETBUTTON_H
