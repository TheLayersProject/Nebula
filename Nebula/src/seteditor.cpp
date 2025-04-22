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

#include "seteditor.h"

#include <QEvent>
#include <Layers/lalgorithms.h>
#include <Layers/lstring.h>
#include <Vortex/vthemebutton.h>

using Layers::LString;
using Layers::LDefinition;
using Layers::LTheme;
using QLayers::QLGrowingDotProgressIndicator;
using Vortex::VTabBar;
using Vortex::VThemeButton;

SetEditor::SetEditor(QWidget* parent) :
	//m_theme{ theme },
	//m_definition_view{ new DefinitionView(lController.root_theme()) }, // lController.root_definition()
	QLWidget(parent)
{
	init_layout();
	//init_theme_scroller();
	m_attr_editors_widget->installEventFilter(this);
	set_object_name("Set Editor");

	m_path_label->set_object_name("Path Label");
	m_path_label->setFixedHeight(40);

	m_editor->set_object_name("Editor");

	m_sidebar->set_object_name("Sidebar");
	m_sidebar->setFixedWidth(298);

	m_mode_tab_bar->add_tab("Files");
	m_mode_tab_bar->add_tab("Editor");
	m_mode_tab_bar->set_current_index(1);
	m_mode_tab_bar->setMinimumHeight(40);

	for (Vortex::VTab* tab : m_mode_tab_bar->tabs())
		tab->hide_close_button();

	connect(m_mode_tab_bar, &VTabBar::index_changed,
		[this](int prev_index, int new_index)
		{
			if (new_index == 0 && !m_attr_editors_scroll_area->isVisible())
			{
				m_attr_editors_scroll_area->show();
				m_text_editor_scroll_area->hide();
			}
			else if (new_index == 1 && !m_text_editor_scroll_area->isVisible())
			{
				m_attr_editors_scroll_area->hide();
				m_text_editor_scroll_area->show();
			}
		});

	m_definition_view->setFixedWidth(298);

	connect(m_definition_view, &DefinitionView::selected_definition_changed,
		[this](LDefinition* definition)
		{
			edit_definition(definition);
		});

	connect(m_definition_view, SIGNAL(selected_theme_item_changed(LDefinition*)),
		this, SLOT(edit_definition(LDefinition*)));

	m_divider_vertical->set_object_name("Dividers");
	m_divider_vertical->setFixedWidth(3);

	m_divider_horizontal->set_object_name("Dividers");
	m_divider_horizontal->setFixedHeight(3);

	m_attr_editors_widget->setSizePolicy(
		QSizePolicy::Minimum, QSizePolicy::Minimum);

	m_attr_editors_scroll_area->set_object_name("Attribute Editors Scroll Area");
	m_attr_editors_scroll_area->setHorizontalScrollBarPolicy(
		Qt::ScrollBarAlwaysOff);
	m_attr_editors_scroll_area->setWidget(m_attr_editors_widget);

	m_text_editor_scroll_area->hide();
	m_text_editor_scroll_area->set_object_name("");
	m_text_editor_scroll_area->setHorizontalScrollBarPolicy(
		Qt::ScrollBarAlwaysOff);
}

void SetEditor::apply_definition(Layers::LDefinition* def, bool is_top_level)
{
	//clear_attr_editors();
	//m_check_label->hide();
	//m_status_label->hide();
	//m_path_text = "";
	//update_path_label();

	LDefinable::apply_definition(def);

	if (definition())
	{
		m_divider_horizontal->apply_definition(
			definition()->find_item("Dividers"));

		m_divider_vertical->apply_definition(
			definition()->find_item("Dividers"));

		//m_attr_editors_scroll_area->apply_definition(
		//	m_editor->definition()->find_item("Attribute Editors Scroll Area"));
	}
}

void SetEditor::setup_view(Layers::LDefinition* def)
{
	m_definition_view->set_definition(def);
}

bool SetEditor::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::Resize)
	{
		update_attr_editors_max_width();
		return true;
	}

	return QLWidget::eventFilter(object, event);
}

void SetEditor::edit_definition(LDefinition* def)
{
	clear_attr_editors();

	QMap<QString, QWidget*> organized_widgets;
	QMap<QString, AttributeEditorGroup*> attr_editor_groups;

	for (auto group_name : def->attribute_group_names())
	{
		QString q_group_name = QString::fromStdString(group_name.c_str());

		AttributeEditorGroup* attr_editor_group =
			new AttributeEditorGroup(q_group_name);
		attr_editor_group->set_object_name("Attribute Editor Groups");

		if (definition())
			attr_editor_group->apply_definition(definition()->find_item(
				attr_editor_group->objectName().toStdString().c_str()));

		attr_editor_groups[q_group_name] = attr_editor_group;
		organized_widgets[q_group_name] = attr_editor_group;
	}

	for (const auto& [key, attr] : def->attributes())
	{
		AttributeEditor* attr_editor = new AttributeEditor(attr);
		attr_editor->set_object_name("Attribute Editors");

		if (definition())
			attr_editor->apply_definition(definition()->find_item(
				attr_editor->objectName().toStdString().c_str()));

		attr_editor->fill_control()->fill()->on_change(
			[this] {
				//reset_save_timer();
			});

		attr_editor->slider()->value()->on_change(
			[this] {
				//reset_save_timer();
			});

		LString attr_name = attr->object_name();

		if (std::find(attr_name.begin(), attr_name.end(),
			'.') != attr_name.end())
		{
			auto group_name = Layers::split<std::vector<LString>>(
				attr_name, '.').front();

			attr_editor_groups[QString::fromStdString(group_name.c_str())]->
				add_attribute_editor(attr_editor);
		}
		else
			organized_widgets[QString::fromStdString(attr_name.c_str())] = attr_editor;
	}

	for (QWidget* widget : organized_widgets)
	{
		widget->setMaximumWidth(m_attr_editors_scroll_area->width());

		m_attr_editors_layout->insertWidget(
			m_attr_editors_layout->count() - 1, widget);
	}

	update_attr_editors_max_width();

	m_path_text = QString::fromStdString(def->path().c_str());
	update_path_label();
}

void SetEditor::init_layout()
{
	set_buttons_vbox->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout* sidebar_layout = new QVBoxLayout;
	sidebar_layout->addWidget(m_definition_view);
	sidebar_layout->setSpacing(0);
	sidebar_layout->setContentsMargins(0, 0, 0, 0);
	//sidebar_layout->addWidget(m_theme_scroller);
	m_sidebar->setLayout(sidebar_layout);

	//QHBoxLayout* path_label_layout = new QHBoxLayout;
	//path_label_layout->addWidget(m_path_label);
	//path_label_layout->setSpacing(0);
	//path_label_layout->setContentsMargins(8, 0, 8, 0);

	QHBoxLayout* mode_tab_bar_layout = new QHBoxLayout;
	mode_tab_bar_layout->addWidget(m_mode_tab_bar);
	mode_tab_bar_layout->addStretch();
	mode_tab_bar_layout->setSpacing(0);
	mode_tab_bar_layout->setContentsMargins(8, 6, 8, 0);

	QVBoxLayout* right_vbox = new QVBoxLayout;
	//right_vbox->addLayout(path_label_layout);
	//right_vbox->addWidget(m_divider_horizontal);
	right_vbox->addWidget(m_attr_editors_scroll_area);
	right_vbox->addWidget(m_text_editor_scroll_area);
	right_vbox->setSpacing(0);

	m_attr_editors_layout->addStretch();
	m_attr_editors_widget->setLayout(m_attr_editors_layout);

	//m_hbox_layout->addWidget(m_definition_view);
	//m_main_layout->addWidget(m_sidebar);

	QHBoxLayout* editor_hbox = new QHBoxLayout;
	editor_hbox->addWidget(m_sidebar);
	editor_hbox->addWidget(m_divider_vertical);
	editor_hbox->addLayout(right_vbox);
	editor_hbox->setContentsMargins(0, 0, 0, 0);
	editor_hbox->setSpacing(0);

	m_editor->setLayout(editor_hbox);

	m_main_layout->addLayout(mode_tab_bar_layout);
	m_main_layout->addWidget(m_divider_horizontal);
	m_main_layout->addWidget(m_editor);
	//m_main_layout->addLayout(right_vbox);
	m_main_layout->setContentsMargins(0, 0, 0, 0);
	m_main_layout->setSpacing(0);

	setLayout(m_main_layout);
	m_main_layout->activate();
}

void SetEditor::init_theme_scroller()
{
	for (auto& _theme : lController.themes())
	{
		LTheme* theme = _theme.second.get();

		if (!theme->publisher().empty())
		{
			VThemeButton* theme_button = new VThemeButton(theme);
			set_buttons_vbox->addWidget(theme_button);

			connect(theme_button, &VThemeButton::clicked,
				[this, theme]
				{
					edit_definition(theme);

					//m_window->open_central_widget(new DefinitionEditor(theme),
					//theme->object_name().c_str());

					qDebug() << "DefinitionEditor: Setting theme: " + QString(theme->object_name().c_str());
				});
		}
	}

	set_buttons_vbox->addStretch();

	m_theme_scroller_widget->setLayout(set_buttons_vbox);
	m_theme_scroller->setWidget(m_theme_scroller_widget);
}

void SetEditor::clear_attr_editors()
{
	for (QObject* child_object : m_attr_editors_widget->children())
		if (QWidget* child_widget = dynamic_cast<QWidget*>(child_object))
			child_widget->deleteLater();
}

void SetEditor::update_attr_editors_max_width()
{
	QMargins margins = m_attr_editors_layout->contentsMargins();

	int scroll_bar_width =
		(m_attr_editors_scroll_area->height() < m_attr_editors_widget->height()) ?
		m_attr_editors_scroll_area->verticalScrollBar()->width() : 0;

	for (QObject* child_object : m_attr_editors_widget->children())
		if (QWidget* child_widget = dynamic_cast<QWidget*>(child_object))
			child_widget->setMaximumWidth(
				m_attr_editors_scroll_area->width() -
				(margins.left() + margins.right() + scroll_bar_width)
			);
}

void SetEditor::update_path_label()
{
	QFontMetrics font_metrics = QFontMetrics(m_path_label->font());

	m_path_label->setText(
		font_metrics.elidedText(
			m_path_text, Qt::ElideLeft, m_path_label->width()));
}
