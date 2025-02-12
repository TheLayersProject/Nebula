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

#ifndef ATTRIBUTEEDITORGROUP_H
#define ATTRIBUTEEDITORGROUP_H

#include <QLayers/qlbutton.h>
#include <QLayers/qlwidget.h>

#include "attributeeditor.h"

class AttributeEditorGroup : public QLayers::QLWidget
{
	Q_OBJECT

public:
	AttributeEditorGroup(const QString& name, QWidget* parent = nullptr);

	void add_attribute_editor(AttributeEditor* attribute_editor);

private:
	void init_layout();

	void set_collapsed(bool collapsed = true);

	QLayers::QLButton* m_collapse_button{
		new QLayers::QLButton(
			QLayers::QLGraphic(
				":/images/collapse_arrow_right.svg", QSize(8, 12)),
			QLayers::QLGraphic(
				":/images/collapse_arrow_down.svg", QSize(12, 8))) };

	bool m_collapsed{ true };

	QLayers::QLLabel* m_label{ new QLayers::QLLabel };

	QList<AttributeEditor*> m_attribute_editors;

	QVBoxLayout* m_widgets_vbox{ new QVBoxLayout };
};

#endif // ATTRIBUTEEDITORGROUP_H
