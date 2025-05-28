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

#ifndef NEWLINKWIDGET
#define NEWLINKWIDGET

#include <Layers/lattribute.h>
#include <QLayers/qlbutton.h>
#include <QLayers/qllineeditor.h>
#include <QLayers/qlresizer.h>
#include <QLayers/qlsplitter.h>
#include <QLayers/qlwidget.h>

#include "attributemapview.h"
#include "definitionview.h"

class NewLinkWidget : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void visibility_changed(bool is_visible);

public:
	NewLinkWidget(Layers::LTheme* theme, Layers::LAttribute* attr,
		QWidget* parent = nullptr);

private:
	void init_layout();

	Layers::LAttribute* m_attr;

	Layers::LAttribute* m_selected_link_attr;

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

	QLayers::QLSplitter* m_splitter{ new QLayers::QLSplitter };

	DefinitionView* m_definition_view;

	AttributeMapView* m_attr_map_view{ new AttributeMapView };

	QLayers::QLLineEditor* m_path_editor{ new QLayers::QLLineEditor };

	QLayers::QLButton* m_apply_link_button{
		new QLayers::QLButton(
			std::make_unique<QLayers::QLGraphic>(
				":/images/check.svg", QSize(16, 13)), "Apply Link") };

	QLayers::QLButton* m_cancel_button{
		new QLayers::QLButton(
			std::make_unique<QLayers::QLGraphic>(
				":/images/tab_exit.svg", QSize(16, 17)), "Cancel") };

	QLayers::QLResizer* m_resizer{
		new QLayers::QLResizer(QLayers::QLSizeDimension::Height) };
};

#endif // NEWLINKWIDGET
