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

#ifndef LINKSVIEW
#define LINKSVIEW

#include <QWidget>
#include <Layers/lattribute.h>
#include <Layers/lconnections.h>
#include <QLayers/qlsvgrenderer.h>
#include <QLayers/qldefinable.h>

class LinksView : public QWidget, public QLayers::QLDefinable
{
	Q_OBJECT

public:
	LinksView(Layers::LAttribute* attr, QWidget* parent = nullptr);

	~LinksView();

	void update_view();

protected:
	virtual void paintEvent(QPaintEvent* event) override;

private:
	void paint_item_dot(
		QPainter* painter,
		const QRect& item_rect,
		int x);

	void paint_item_text(
		QPainter* painter,
		const QString& text,
		const QRect& item_rect,
		QFont font,
		int x);

	void update_height();

	Layers::LAttribute* m_attr;

	Layers::LConnectionID m_attr_link_changed_connection;

	Layers::LAttribute* m_text_color{
		new Layers::LAttribute("Text Color", "#000000", this) };

	QString m_parent_path;

	QStringList m_link_paths;
	QStringList m_dependent_paths;

	QLayers::QLSvgRenderer* m_dot_svg{
		new QLayers::QLSvgRenderer(":/images/dot.svg", this) };

	QLayers::QLSvgRenderer* m_link_arrow_svg{
		new QLayers::QLSvgRenderer(":/images/link_arrow.svg", this) };

	QLayers::QLSvgRenderer* m_dependent_arrow_svg{
		new QLayers::QLSvgRenderer(":/images/dependent_arrow.svg", this) };

	QLayers::QLSvgRenderer* m_dependent_arrow_2_svg{
		new QLayers::QLSvgRenderer(":/images/dependent_arrow_2.svg", this) };
};

#endif // LINKSVIEW
