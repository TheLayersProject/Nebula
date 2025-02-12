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

#include "thememodel.h"

#include "metatypes.h"

#include <Vortex/vapplication.h>

using Layers::LDefinition;
using Layers::LTheme;

ThemeModel::ThemeModel(QObject* parent) :
	QAbstractItemModel(parent)
{
}

int ThemeModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 1;
}

QVariant ThemeModel::data(const QModelIndex& index, int role) const
{
	//if (!index.isValid())
	//	return QVariant();

	//else if (role == Qt::DisplayRole)
	//	return QString::fromStdString(get_item(index)->object_name().c_str());

	//else if (role == Qt::UserRole)
	//	return QVariant::fromValue(get_item(index));

	//return QVariant();

	if (!index.isValid())
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		auto itemName = QString::fromStdString(get_item(index)->object_name().c_str());
		qDebug() << "DisplayRole item name:" << itemName;
		return itemName;
	}
	else if (role == Qt::UserRole)
	{
		auto item = get_item(index);
		qDebug() << "UserRole item:" << item;
		return QVariant::fromValue(item);
	}

	return QVariant();
}

QModelIndex ThemeModel::index(
	int row, int column, const QModelIndex& parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

	LDefinition* parent_item = get_item(parent);
	if (!parent_item)
		return QModelIndex();

	LDefinition* child_item = parent_item->child(row);
	if (child_item)
		return createIndex(row, column, child_item);

	return QModelIndex();
}

QModelIndex ThemeModel::parent(const QModelIndex& index) const
{
	if (!index.isValid())
		return QModelIndex();

	LDefinition* child_item = get_item(index);
	LDefinition* parent_item =
		child_item ? dynamic_cast<LDefinition*>(child_item->parent()) : nullptr;

	//if (parent_item == m_theme->root_item() || !parent_item)
	//	return QModelIndex();

	return createIndex(parent_item->index(), 0, parent_item);
}

int ThemeModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid() && parent.column() > 0)
		return 0;

	const LDefinition* parent_item = get_item(parent);

	return parent_item ?
		parent_item->child_count() : 0;
}

void ThemeModel::set_theme(LTheme* theme)
{
	beginResetModel();
	m_theme = theme;
	//m_theme->load(vApp->app_display_id().toStdString().c_str());
	//m_theme->load();
	m_theme->set_edit_mode_enabled();
	qDebug() << "Theme set to:" << theme->object_name().c_str();
	endResetModel();
}

LDefinition* ThemeModel::get_item(const QModelIndex& index) const
{
	if (index.isValid())
		if (LDefinition* item =
			static_cast<LDefinition*>(index.internalPointer()))
		{
			return item;
		}

	//if (m_theme)
	//	return m_theme->root_item();

	return nullptr;
}
