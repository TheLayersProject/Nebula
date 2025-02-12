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

#ifndef SETDISPLAYER_H
#define SETDISPLAYER_H

#include <Layers/ltheme.h>

#include <QLayers/qlbutton.h>
#include <QLayers/qllabel.h>
#include <QLayers/qlwidget.h>

class SetDisplayer : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void closed();

public:
	SetDisplayer(QWidget* parent = nullptr);

	void set_version(const QString& version_tag);

	void setup(
		const QString& name, const QString& publisher,
		const QLayers::QLGraphic& logo);

	void setup(
		const QString& name, const QString& publisher);

//protected:
//	bool eventFilter(QObject* object, QEvent* event) override;

private:
	//void init_labels(const std::filesystem::path& set_path);
	void init_layout();

	QLayers::QLLabel* m_logo_label{ new QLayers::QLLabel };
	QLayers::QLLabel* m_name_label{ new QLayers::QLLabel };
	QLayers::QLLabel* m_publisher_label{ new QLayers::QLLabel };

	QLayers::QLButton* m_close_button
	{ new QLayers::QLButton(
		QLayers::QLGraphic(":/images/tab_exit.svg", QSize(16, 17))) };
};

#endif // SETDISPLAYER_H
