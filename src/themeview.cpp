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

#include "themeview.h"

#include <QEvent>
#include <QPainter>
#include <Layers/lstring.h>
//#include <Vortex/vapplication.h>

#include "metatypes.h"

using Layers::LString;
using Layers::LDefinition;
using Layers::LTheme;
using QLayers::QLDefinable;
//using Vortex::VApplication;

ThemeView::ThemeView(LTheme* theme, QWidget* parent) :
	QTreeView(parent)
{
	set_object_name("Theme View");

	m_model->set_theme(theme);

	qDebug() << "Model Theme:" << theme->object_name().c_str();

	//m_model_update_connection =
	//	connect(vApp, &VApplication::active_theme_changed,
	//		[this] {
	//			m_model->set_theme(Vortex::activeTheme());
	//		});

	setHeaderHidden(true);
	setHorizontalScrollBar(m_horizontal_scrollbar);
	setModel(m_model);
	setVerticalScrollBar(m_vertical_scrollbar);

	m_horizontal_scrollbar->set_object_name("Horizontal ScrollBar");
	m_vertical_scrollbar->set_object_name("Vertical ScrollBar");
	
	update();
}

//ThemeView::~ThemeView()
//{
//	disconnect(m_model_update_connection);
//}

QList<QLDefinable*> ThemeView::child_qldefinables(
	Qt::FindChildOptions options)
{
	QList<QLDefinable*> child_qldefinables =
		QLDefinable::child_qldefinables(options);

	child_qldefinables.append(m_horizontal_scrollbar);
	child_qldefinables.append(m_vertical_scrollbar);

	return child_qldefinables;
}

void ThemeView::update()
{
	QString style_sheet =
		"QAbstractItemView {"
		"background: " +
			QString::fromStdString(m_fill->as<LString>().c_str()) + ";"
		"border: none;"
		"}"

		"QAbstractItemView::item {"
		"height: 40px;"
		"color: " +
			QString::fromStdString(m_text_color->as<LString>().c_str()) + ";"
		"}";

	setStyleSheet(style_sheet);

	QWidget::update();
}

void ThemeView::selectionChanged(
	const QItemSelection& selected,
	const QItemSelection& deselected)
{
	QModelIndexList indexes = selected.indexes();

	if (!indexes.isEmpty())
		emit selected_theme_item_changed(
			indexes.first().data(Qt::UserRole).value<LDefinition*>());
}
