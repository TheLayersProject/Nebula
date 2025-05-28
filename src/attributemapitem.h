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

#ifndef ATTRIBUTEMAPITEM_H
#define ATTRIBUTEMAPITEM_H

#include <QVariant>
#include <QList>
#include <Layers/lattribute.h>

class AttributeMapItem : public QObject
{
	Q_OBJECT

public:
	AttributeMapItem(Layers::LAttribute* attribute,
		AttributeMapItem* parent = nullptr);

	void append_child(AttributeMapItem* child);

	Layers::LAttribute* attribute() const;

	AttributeMapItem* child(int index) const;

	int child_count() const;

	QMap<QString, AttributeMapItem*>& children();

	int index() const;

private:
	QMap<QString, AttributeMapItem*> m_child_attr_items;
	Layers::LAttribute* m_attribute{ nullptr };
};

#endif // ATTRIBUTEMAPITEM_H
