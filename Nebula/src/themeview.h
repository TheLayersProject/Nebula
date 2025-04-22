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

#ifndef THEMEVIEW_H
#define THEMEVIEW_H

#include <QTreeView>
#include <Layers/lattribute.h>
#include <Layers/ldefinition.h>
#include <QLayers/qlscrollbar.h>
#include <QLayers/qldefinable.h>

#include "thememodel.h"

class ThemeView : public QTreeView, public QLayers::QLDefinable
{
	Q_OBJECT

signals:
	void selected_theme_item_changed(Layers::LDefinition* theme_item);

public:
	ThemeView(Layers::LTheme* theme, QWidget* parent = nullptr);

	//~ThemeView();

	virtual QList<QLayers::QLDefinable*> child_qldefinables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	virtual void update() override;

protected:
	virtual void selectionChanged(
		const QItemSelection& selected,
		const QItemSelection& deselected) override;

private:
	Layers::LAttribute* m_fill{
		lMakeDefinableAttribute(this, "Fill", "#ffffff") };

	Layers::LAttribute* m_text_color{
		lMakeDefinableAttribute(this, "Text Color", "#000000") };

	QLayers::QLScrollBar* m_horizontal_scrollbar{ new QLayers::QLScrollBar };
	QLayers::QLScrollBar* m_vertical_scrollbar{ new QLayers::QLScrollBar };

	ThemeModel* m_model{ new ThemeModel(this) };

	//QMetaObject::Connection m_model_update_connection;
};

#endif // THEMEVIEW_H  
