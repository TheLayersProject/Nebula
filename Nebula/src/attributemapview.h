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

#ifndef ATTRIBUTEMAPVIEW_H
#define ATTRIBUTEMAPVIEW_H

#include <QTreeView>
#include <Layers/lattribute.h>
#include <QLayers/qlscrollbar.h>
#include <QLayers/qldefinable.h>

#include "attributemapmodel.h"

class AttributeMapView :
	public QTreeView, public QLayers::QLDefinable
{
	Q_OBJECT

signals:
	void selected_map_item_changed(Layers::LAttribute* attr);

public:
	AttributeMapView(QWidget* parent = nullptr);

	//~AttributeMapView();

	virtual QList<QLayers::QLDefinable*> child_qldefinables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	void set_attributes(
		Layers::LAttributeMap attributes, const QStringList& filter_paths);

	virtual void update() override;

protected:
	virtual void selectionChanged(
		const QItemSelection& selected,
		const QItemSelection& deselected) override;

private:
	Layers::LAttribute* m_fill{
		new Layers::LAttribute("Fill", "#ffffff", this) };

	Layers::LAttribute* m_text_color{
		new Layers::LAttribute("Text Color", "#000000", this) };

	QLayers::QLScrollBar* m_horizontal_scrollbar{ new QLayers::QLScrollBar };
	QLayers::QLScrollBar* m_vertical_scrollbar{ new QLayers::QLScrollBar };

	AttributeMapModel* m_model{ new AttributeMapModel };

	//QMetaObject::Connection m_model_update_connection;
};

#endif // ATTRIBUTEMAPVIEW_H  
