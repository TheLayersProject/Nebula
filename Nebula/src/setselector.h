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

#ifndef DEFINITIONSETSELECTOR_H
#define DEFINITIONSETSELECTOR_H

#include <QVBoxLayout>
#include <Layers/ltheme.h>
#include <Layers/ldefinition.h>
#include <QLayers/qldialog.h>
#include <QLayers/qlscrollarea.h>
#include <QLayers/qlwidget.h>
#include <Vortex/vtabbar.h>

#include "attributeeditor.h"
#include "attributeeditorgroup.h"
#include "definitionview.h"

class SetSelector : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void selected_with_logo(const QString& name, const QString& publisher, const QLayers::QLGraphic& logo);
	void selected(const QString& name, const QString& publisher);

signals:
	void selected_version(const QString& version_tag);

public:
	SetSelector(QWidget* parent = nullptr);

	virtual void apply_definition(Layers::LDefinition* def) override;

	//virtual QList<QLayers::QLDefinable*> child_qldefinables(
	//	Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	//) override;

	void reset();

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init_layout();
	void init_set_scroller();
	void init_version_buttons(const std::filesystem::path& set_path);

	void clear_version_buttons();

	void update_version_buttons_max_width();

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

	QHBoxLayout* m_hbox_layout{ new QHBoxLayout };

	QVBoxLayout* m_version_buttons_layout{ new QVBoxLayout };

	QVBoxLayout* set_buttons_vbox{ new QVBoxLayout };

	QLayers::QLScrollArea* m_set_scroller{ new QLayers::QLScrollArea };

	QWidget* m_set_scroller_widget{ new QWidget };

	QLWidget* m_sidebar{ new QLWidget };

	QLWidget* m_divider_vertical{ new QLWidget };

	QLayers::QLScrollArea* m_version_buttons_scroll_area{
		new QLayers::QLScrollArea };

	QWidget* m_version_buttons_widget{ new QWidget };
};

#endif // DEFINITIONSETSELECTOR_H
