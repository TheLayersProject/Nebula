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

#include "attributemapitem.h"

using Layers::LAttribute;

AttributeMapItem::AttributeMapItem(
	LAttribute* attribute, AttributeMapItem* parent) :
	m_attribute{ attribute }, QObject(parent) {}

void AttributeMapItem::append_child(AttributeMapItem* child)
{
	m_child_attr_items[
		QString::fromStdString(child->m_attribute->object_name().c_str())
	] = child;
}

LAttribute* AttributeMapItem::attribute() const
{
	return m_attribute;
}

AttributeMapItem* AttributeMapItem::child(int index) const
{
	if (index < 0 || index >= m_child_attr_items.size())
		return nullptr;
	return m_child_attr_items[m_child_attr_items.keys().at(index)];
}

int AttributeMapItem::child_count() const
{
	return m_child_attr_items.count();
}

QMap<QString, AttributeMapItem*>& AttributeMapItem::children()
{
	return m_child_attr_items;
}

int AttributeMapItem::index() const
{
	if (AttributeMapItem* parent_item =
		dynamic_cast<AttributeMapItem*>(parent()))
	{
		QStringList keys = parent_item->m_child_attr_items.keys();

		for (int i = 0; i < keys.size(); i++)
		{
			AttributeMapItem* parent_child_attr_item =
				parent_item->m_child_attr_items[keys.at(i)];

			if (parent_child_attr_item == this)
				return i;
		}
	}

	return 0;
}
