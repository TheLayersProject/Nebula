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

#ifndef HOMEBUTTON_H
#define HOMEBUTTON_H

#include <QLayers/qllabel.h>
#include <QLayers/qlwidget.h>

#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>

class HomeButton : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	HomeButton(
		std::unique_ptr<QLayers::QLGraphic> graphic,
		const QString& title,
		const QString& description,
		QWidget* parent = nullptr);

	QLayers::QLLabel* graphic_label() const;

	QHBoxLayout* layout() const;

	void set_padding(int padding);

	void set_padding(int left, int top, int right, int bottom);

	QLayers::QLLabel* title_label() const;

protected:
	virtual bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init();
	void init_layout();

	QHBoxLayout* m_main_layout{ new QHBoxLayout };

	QLayers::QLLabel* m_graphic_label{ nullptr };

	QLayers::QLLabel* m_title_label{ nullptr };

	QLayers::QLLabel* m_description_label{ nullptr };

	QLayers::QLStatePool* m_select_states{
		new QLayers::QLStatePool("Select", { "Selected", "Unselected" }) };
};

#endif // HOMEBUTTON_H
