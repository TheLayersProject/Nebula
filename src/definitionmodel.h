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

#ifndef DEFINITIONMODEL_H
#define DEFINITIONMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <Layers/ltheme.h>

class DefinitionModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	DefinitionModel(QObject* parent = nullptr);

	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	virtual QVariant data(const QModelIndex& index, int role) const override;

	virtual QModelIndex index(int row, int column,
		const QModelIndex& parent = QModelIndex()) const override;

	virtual QModelIndex parent(const QModelIndex& index) const override;

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	void set_definition(Layers::LDefinition* definition);

private:
	Layers::LDefinition* get_item(const QModelIndex& index) const;

	Layers::LDefinition* m_definition{ nullptr };
};

#endif // DEFINITIONMODEL_H
