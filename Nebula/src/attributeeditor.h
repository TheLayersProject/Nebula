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

#ifndef ATTRIBUTEEDITOR_H
#define ATTRIBUTEEDITOR_H

#include <Layers/lattribute.h>
#include <QLayers/qlbutton.h>
#include <QLayers/qlgraphic.h>
#include <QLayers/qllabel.h>
#include <QLayers/qllineeditor.h>
#include <QLayers/qlminislider.h>
#include <QLayers/qldefinable.h>
#include <QLayers/qlwidget.h>
#include <Fusion/ffillcontrol.h>
#include <Vortex/vtabbar.h>

#include "linkdisplayer.h"

class LinksView;
class NewLinkWidget;

class AttributeEditor : public QLayers::QLWidget
{
	Q_OBJECT

public:
	AttributeEditor(Layers::LAttribute* attr, QWidget* parent = nullptr);

	~AttributeEditor();

	virtual QList<QLayers::QLDefinable*> child_qldefinables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	Fusion::FFillControl* fill_control() const;

	QLayers::QLLineEditor* line_editor() const;

	QLayers::QLMiniSlider* slider() const;

private:
	void init_attributes();
	void init_layout();

	void update_icon_labels();

	Layers::LAttribute* m_attr;

	QHBoxLayout* m_controls_layout{ new QHBoxLayout };
	QHBoxLayout* m_icons_layout{ new QHBoxLayout };
	QHBoxLayout* m_links_buttons_layout{ new QHBoxLayout };
	QVBoxLayout* m_links_layout{ new QVBoxLayout };
	QVBoxLayout* m_overrides_layout{ new QVBoxLayout };

	Fusion::FFillControl* m_fill_control{ new Fusion::FFillControl };

	QLayers::QLLabel* m_label{ new QLayers::QLLabel };

	QLayers::QLMiniSlider* m_slider{ new QLayers::QLMiniSlider };

	QLayers::QLLineEditor* m_line_editor{ new QLayers::QLLineEditor };

	LinkDisplayer* m_link_displayer{ new LinkDisplayer };

	QLayers::QLLabel* m_link_icon_label =
		new QLayers::QLLabel(
			std::make_unique<QLayers::QLGraphic>(
				":/images/chain_link.svg", QSize(8, 18)));

	QLayers::QLLabel* m_overrides_icon_label =
		new QLayers::QLLabel(
			std::make_unique<QLayers::QLGraphic>(
				":/images/overrides_icon.svg", QSize(10, 18)));

	QLayers::QLButton* m_collapse_button{
		new QLayers::QLButton(
			std::make_unique<QLayers::QLGraphic>(
				":/images/collapse_arrow_right.svg", QSize(8, 12)),
			std::make_unique<QLayers::QLGraphic>(
				":/images/collapse_arrow_down.svg", QSize(12, 8))) };

	QLWidget* m_icons_widget{ new QLWidget };

	Vortex::VTabBar* m_features_tab_bar{ new Vortex::VTabBar };

	QWidget* m_features_widget{ new QWidget };

	LinksView* m_links_view;

	NewLinkWidget* m_new_link_widget{ nullptr };

	Layers::LConnectionID m_attr_link_changed_connection;
	QMetaObject::Connection m_new_link_widget_destroyed_connection;

	QLWidget* m_links_widget{ new QLWidget };

	QLWidget* m_overrides_widget{ new QLWidget };

	QLayers::QLButton* m_new_link_button{
		new QLayers::QLButton(
			std::make_unique<QLayers::QLGraphic>(
				":/images/plus.svg", QSize(18, 18)), "New Link") };

	QLayers::QLButton* m_break_link_button{
		new QLayers::QLButton(
			std::make_unique<QLayers::QLGraphic>(
				":/images/tab_exit.svg", QSize(16, 17)), "Break Link") };

	QLayers::QLStatePool* m_status_states{
		new QLayers::QLStatePool("Status", { "Active", "Inactive" }) };
};

#endif // ATTRIBUTEEDITOR_H
