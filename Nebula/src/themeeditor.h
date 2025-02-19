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

#ifndef THEMEEDITOR_H
#define THEMEEDITOR_H

#include <QVBoxLayout>
#include <Layers/ltheme.h>
#include <Layers/ldefinition.h>
#include <QLayers/qldialog.h>
#include <QLayers/qlgrowingdotprogressindicator.h>
#include <QLayers/qlscrollarea.h>
#include <QLayers/qlwidget.h>
#include <Vortex/vtabbar.h>
#include <Vortex/vthemebutton.h>

#include "attributeeditor.h"
#include "attributeeditorgroup.h"
#include "definitionview.h"

class ThemeEditor : public QLayers::QLWidget
{
	Q_OBJECT

public:
	ThemeEditor(QWidget* parent = nullptr);

	virtual void apply_definition(Layers::LDefinition* def) override;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

public slots:
	void edit_theme(Layers::LTheme* theme);

	void reset_save_timer();

private:
	void init_layout();
	void init_theme_scroller();

	void add_theme_button(Layers::LTheme* theme);

	void clear_attr_editors();

	void update_attr_editors_max_width();

	void update_path_label();

	//Layers::LTheme* m_theme;

	std::map<Layers::LTheme*, Vortex::VThemeButton*> theme_buttons;

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

	QHBoxLayout* m_hbox_layout{ new QHBoxLayout };

	QVBoxLayout* m_attr_editors_layout{ new QVBoxLayout };

	QHBoxLayout* m_options_bar_layout{ new QHBoxLayout };

	QVBoxLayout* theme_buttons_vbox{ new QVBoxLayout };

	QLayers::QLLineEditor* m_search_box{ new QLayers::QLLineEditor };

	QLayers::QLButton* m_new_theme_button{
		new QLayers::QLButton(
			QLayers::QLGraphic(":/images/new_theme.svg", QSize(26, 26))) };

	QLayers::QLScrollArea* m_theme_scroller{ new QLayers::QLScrollArea };

	QWidget* m_theme_scroller_widget{ new QWidget };

	QLWidget* m_sidebar{ new QLWidget };

	//DefinitionView* m_definition_view;

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

	QLWidget* m_options_bar{ new QLWidget };

	QLayers::QLLabel* m_check_label{
		new QLayers::QLLabel(
			QLayers::QLGraphic(":/images/check.svg", QSize(16, 13))) };

	QLayers::QLLabel* m_status_label{ new QLayers::QLLabel("Saved") };

	QLayers::QLGrowingDotProgressIndicator* m_save_progress_indicator{
		new QLayers::QLGrowingDotProgressIndicator };
};

#endif // THEMEEDITOR_H
