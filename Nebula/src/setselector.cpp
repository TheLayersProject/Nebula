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

#include "setselector.h"

#include <QEvent>
#include <Layers/lalgorithms.h>
#include <Layers/lpaths.h>
#include <Layers/lstring.h>
#include <QLayers/qlbutton.h>

#include "setbutton.h"

using Layers::LString;
using Layers::LDefinition;
using Layers::LTheme;
using QLayers::QLButton;
using QLayers::QLDefinable;
using QLayers::QLGraphic;
using Vortex::VTabBar;

SetSelector::SetSelector(QWidget* parent) :
	//m_theme{ theme },
	//m_definition_view{ new DefinitionView(lController.root_theme()) }, // lController.root_definition()
	QLWidget(parent)
{
	init_set_scroller();
	init_layout();
	m_version_buttons_widget->installEventFilter(this);
	set_object_name("Set Selector");

	m_sidebar->set_object_name("Sidebar");
	m_sidebar->setFixedWidth(298);

	m_set_scroller->set_object_name("Set Scroller");

	m_divider_vertical->set_object_name("Dividers");
	m_divider_vertical->setFixedWidth(4);

	m_version_buttons_widget->setSizePolicy(
		QSizePolicy::Minimum, QSizePolicy::Minimum);

	m_version_buttons_scroll_area->set_object_name("Attribute Editors Scroll Area");
	m_version_buttons_scroll_area->setHorizontalScrollBarPolicy(
		Qt::ScrollBarAlwaysOff);
	m_version_buttons_scroll_area->setWidget(m_version_buttons_widget);
}

void SetSelector::apply_definition(Layers::LDefinition* def)
{
	//clear_version_buttons();
	//m_check_label->hide();
	//m_status_label->hide();
	//m_path_text = "";
	//update_path_label();

	LDefinable::apply_definition(def);

	QList<QObject*> scroller_widget_child_objects =
		m_set_scroller_widget->findChildren<QObject*>();

	for (QObject* scroller_widget_child_object : scroller_widget_child_objects)
		if (SetButton* child_set_button =
			dynamic_cast<SetButton*>(scroller_widget_child_object))
		{
			child_set_button->apply_definition(m_sidebar->definition()->find_item(
				child_set_button->objectName().toStdString().c_str()));
		}

	//QList<QObject*> version_buttons_child_objects =
	//	m_version_buttons_widget->findChildren<QObject*>();

	//for (QObject* version_buttons_child_object : version_buttons_child_objects)
	//	if (QLButton* version_button =
	//		dynamic_cast<QLButton*>(version_buttons_child_object))
	//	{
	//		version_button->apply_definition(definition()->find_item(
	//			version_button->objectName().toStdString().c_str()));
	//	}

	//for (QObject* child_object : m_version_buttons_widget->children())
	//	if (QLButton* version_button = dynamic_cast<QLButton*>(child_object))
	//		version_button->apply_definition(definition()->find_item(
	//			version_button->objectName().toStdString().c_str()));
}

//QList<QLDefinable*> SetSelector::child_qldefinables(
//	Qt::FindChildOptions options)
//{
//	QList<QLDefinable*> child_qldefinables =
//		QLDefinable::child_qldefinables(options);
//
//	for (const auto& set_button_obj : set_buttons_vbox->children())
//		if (SetButton* set_button = dynamic_cast<SetButton*>(set_button_obj))
//			child_qldefinables.append(set_button);
//
//	return child_qldefinables;
//}

void SetSelector::reset()
{
	clear_version_buttons();
}

bool SetSelector::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::Resize)
	{
		update_version_buttons_max_width();
		return true;
	}

	return QLWidget::eventFilter(object, event);
}

void SetSelector::init_layout()
{
	set_buttons_vbox->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout* sidebar_layout = new QVBoxLayout;
	sidebar_layout->addWidget(m_set_scroller);
	m_sidebar->setLayout(sidebar_layout);

	//QHBoxLayout* path_label_layout = new QHBoxLayout;
	//path_label_layout->addWidget(m_path_label);
	//path_label_layout->setSpacing(0);
	//path_label_layout->setContentsMargins(8, 0, 8, 0);

	//QHBoxLayout* mode_tab_bar_layout = new QHBoxLayout;
	//mode_tab_bar_layout->addWidget(m_mode_tab_bar);
	//mode_tab_bar_layout->addStretch();
	//mode_tab_bar_layout->setSpacing(0);
	//mode_tab_bar_layout->setContentsMargins(8, 0, 8, 0);

	QVBoxLayout* right_vbox = new QVBoxLayout;
	//right_vbox->addLayout(path_label_layout);
	//right_vbox->addLayout(mode_tab_bar_layout);
	right_vbox->addWidget(m_version_buttons_scroll_area);
	right_vbox->setSpacing(0);

	m_version_buttons_layout->addStretch();
	m_version_buttons_widget->setLayout(m_version_buttons_layout);

	//m_hbox_layout->addWidget(m_definition_view);
	m_hbox_layout->addWidget(m_sidebar);
	m_hbox_layout->addWidget(m_divider_vertical);
	m_hbox_layout->addLayout(right_vbox);
	m_hbox_layout->setContentsMargins(0, 0, 0, 0);
	m_hbox_layout->setSpacing(0);

	m_main_layout->addLayout(m_hbox_layout);
	m_main_layout->setContentsMargins(0, 0, 0, 0);
	m_main_layout->setSpacing(0);

	setLayout(m_main_layout);
	m_main_layout->activate();
}

void SetSelector::init_set_scroller()
{
	for (const auto& entry :
		std::filesystem::directory_iterator(Layers::definitions_path()))
	{
		if (std::filesystem::is_directory(entry.path()))
		{
			SetButton* set_button = new SetButton(entry.path());
			set_buttons_vbox->addWidget(set_button);

			//if (m_sidebar->definition())
			//	set_button->apply_definition(m_sidebar->definition()->find_item(
			//		set_button->objectName().toStdString().c_str()));

			connect(set_button, &SetButton::clicked,
				[this, set_button, entry]
				{
					if (QLGraphic* logo = set_button->logo())
					{
						emit selected_with_logo(
							set_button->name(),
							set_button->publisher(),
							QLGraphic(*logo));
					}
					else
					{
						emit selected(
							set_button->name(),
							set_button->publisher());
					}

					init_version_buttons(entry.path());

					//edit_definition(theme);

					//m_window->open_central_widget(new DefinitionEditor(theme),
					//theme->object_name().c_str());

					//qDebug() << "DefinitionEditor: Setting theme: " + QString(theme->object_name().c_str());
				});
		}
	}

	//for (auto& _theme : lController.themes())
	//{
	//	LTheme* theme = _theme.second;

	//	if (!theme->publisher().empty())
	//	{
	//		ThemeButton* theme_button = new ThemeButton(theme);
	//		set_buttons_vbox->addWidget(theme_button);

	//		connect(theme_button, &ThemeButton::clicked,
	//			[this, theme]
	//			{
	//				edit_definition(theme);

	//				//m_window->open_central_widget(new DefinitionEditor(theme),
	//				//theme->object_name().c_str());

	//				qDebug() << "DefinitionEditor: Setting theme: " + QString(theme->object_name().c_str());
	//			});
	//	}
	//}

	set_buttons_vbox->addStretch();

	m_set_scroller_widget->setLayout(set_buttons_vbox);
	m_set_scroller->setWidget(m_set_scroller_widget);
}

void SetSelector::init_version_buttons(
	const std::filesystem::path& set_path)
{
	clear_version_buttons();

	for (const auto& entry : std::filesystem::directory_iterator(set_path))
	{
		if (std::filesystem::is_directory(entry.path()))
		{
			QLButton* version_button = new QLButton(
				entry.path().filename().string().c_str());
			version_button->set_object_name("Version Button");
			version_button->set_pointing_hand_cursor();
			version_button->apply_definition(definition()->find_item(
				version_button->objectName().toStdString().c_str()));

			m_version_buttons_layout->insertWidget(
				m_version_buttons_layout->count() - 1, version_button);

			connect(version_button, &QLButton::clicked,
				[this, version_button]
				{
					emit selected_version(
						version_button->text_label()->text());
				});
		}
	}
}

void SetSelector::clear_version_buttons()
{
	for (QObject* child_object : m_version_buttons_widget->children())
		if (QWidget* child_widget = dynamic_cast<QWidget*>(child_object))
			child_widget->deleteLater();
}

void SetSelector::update_version_buttons_max_width()
{
	QMargins margins = m_version_buttons_layout->contentsMargins();

	int scroll_bar_width =
		(m_version_buttons_scroll_area->height() < m_version_buttons_widget->height()) ?
		m_version_buttons_scroll_area->verticalScrollBar()->width() : 0;

	for (QObject* child_object : m_version_buttons_widget->children())
		if (QWidget* child_widget = dynamic_cast<QWidget*>(child_object))
			child_widget->setMaximumWidth(
				m_version_buttons_scroll_area->width() -
				(margins.left() + margins.right() + scroll_bar_width)
			);
}

//void SetSelector::update_path_label()
//{
//	QFontMetrics font_metrics = QFontMetrics(m_path_label->font());
//
//	m_path_label->setText(
//		font_metrics.elidedText(
//			m_path_text, Qt::ElideLeft, m_path_label->width()));
//}
