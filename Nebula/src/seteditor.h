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

#ifndef DEFINITIONSETEDITOR_H
#define DEFINITIONSETEDITOR_H

#include <QVBoxLayout>
#include <Layers/ltheme.h>
#include <Layers/ldefinition.h>
#include <QLayers/qldialog.h>
#include <QLayers/qlgrowingdotprogressindicator.h>
#include <QLayers/qlscrollarea.h>
#include <QLayers/qlwidget.h>
#include <Vortex/vtabbar.h>

#include "attributeeditor.h"
#include "attributeeditorgroup.h"
#include "definitionview.h"

class SetEditor : public QLayers::QLWidget
{
	Q_OBJECT

public:
	SetEditor(QWidget* parent = nullptr);

	virtual void apply_definition(Layers::LDefinition* def) override;

	void setup_view(Layers::LDefinition* def);

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

public slots:
	void edit_definition(Layers::LDefinition* def);

private:
	void init_layout();
	void init_theme_scroller();

	void clear_attr_editors();

	void update_attr_editors_max_width();

	void update_path_label();

	//Layers::LTheme* m_theme;

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

	QVBoxLayout* m_attr_editors_layout{ new QVBoxLayout };

	QVBoxLayout* set_buttons_vbox{ new QVBoxLayout };

	QLayers::QLScrollArea* m_theme_scroller{ new QLayers::QLScrollArea };

	QWidget* m_theme_scroller_widget{ new QWidget };

	QLWidget* m_sidebar{ new QLWidget };

	DefinitionView* m_definition_view{ new DefinitionView };

	QLWidget* m_divider_horizontal{ new QLWidget };
	QLWidget* m_divider_vertical{ new QLWidget };

	QString m_path_text;

	QLayers::QLLabel* m_path_label{ new QLayers::QLLabel };

	Vortex::VTabBar* m_mode_tab_bar{ new Vortex::VTabBar };

	QLayers::QLScrollArea* m_attr_editors_scroll_area{
		new QLayers::QLScrollArea };

	QLayers::QLScrollArea* m_text_editor_scroll_area{
		new QLayers::QLScrollArea };

	QWidget* m_attr_editors_widget{ new QWidget };

	QLWidget* m_editor{ new QLWidget };
};

#endif // DEFINITIONSETEDITOR_H
