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

#include "attributemapmodel.h"

using Layers::LAttribute;
using Layers::LAttributeMap;

AttributeMapModel::AttributeMapModel(QObject* parent) :
	QAbstractItemModel(parent)
{
}

AttributeMapModel::~AttributeMapModel()
{
	delete m_root_item;
}

int AttributeMapModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 1;
}

QVariant AttributeMapModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
	else if (role == Qt::DisplayRole)
	{
		return QString::fromStdString(
			get_item(index)->attribute()->object_name().c_str());
	}
	else if (role == Qt::UserRole)
	{
		return QVariant::fromValue(get_item(index)->attribute());
	}

	return QVariant();
}

QModelIndex AttributeMapModel::index(
	int row, int column, const QModelIndex& parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

	AttributeMapItem* parent_item = get_item(parent);
	if (!parent_item)
		return QModelIndex();

	AttributeMapItem* child_item = parent_item->child(row);
	if (child_item)
		return createIndex(row, column, child_item);

	return QModelIndex();
}

QModelIndex AttributeMapModel::parent(const QModelIndex& index) const
{
	if (!index.isValid())
		return QModelIndex();

	AttributeMapItem* child_item = get_item(index);
	AttributeMapItem* parent_item = child_item ?
		dynamic_cast<AttributeMapItem*>(child_item->parent()) : nullptr;

	if (parent_item == m_root_item || !parent_item)
		return QModelIndex();

	return createIndex(parent_item->index(), 0, parent_item);
}

int AttributeMapModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid() && parent.column() > 0)
		return 0;

	const AttributeMapItem* parent_item = get_item(parent);

	return parent_item ?
		parent_item->child_count() : 0;
}

void AttributeMapModel::set_attributes(
	LAttributeMap attributes, const QStringList& filter_paths)
{
	beginResetModel();

	delete m_root_item;

	m_root_item = new AttributeMapItem(nullptr);

	for (const auto& [key, attr] : attributes)
		if (!filter_paths.contains(QString::fromStdString(attr->path().c_str())))
			m_root_item->append_child(
				init_item(attr, filter_paths, m_root_item));

	endResetModel();
}

AttributeMapItem* AttributeMapModel::init_item(
	LAttribute* attribute, const QStringList& filter_paths,
	AttributeMapItem* parent)
{
	AttributeMapItem* item = new AttributeMapItem(attribute, parent);

	for (const auto& [key, override_attr] : attribute->states())
		item->append_child(init_item(override_attr, filter_paths, item));

	return item;
}

AttributeMapItem* AttributeMapModel::get_item(const QModelIndex& index) const
{
	if (index.isValid())
		if (AttributeMapItem* item =
			static_cast<AttributeMapItem*>(index.internalPointer()))
		{
			return item;
		}

	if (m_root_item)
		return m_root_item;

	return nullptr;
}
