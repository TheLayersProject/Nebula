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

#include "setbutton.h"

#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <Layers/lalgorithms.h>

using Layers::LAttributeMap;
using Layers::LString;
using Layers::LTheme;
using Layers::LDefinition;
using Layers::LVariant;

using QLayers::QLGraphic;
using QLayers::QLLabel;

SetButton::SetButton(const std::filesystem::path& set_path, QWidget* parent) :
	m_set_path{ set_path },
	//m_name_label{ new QLLabel(theme->object_name().c_str()) },
	//m_publisher_label{ new QLLabel(theme->publisher().c_str()) },
	QLWidget(parent)
{
	init_labels(set_path);
	init_layout();
	//init_style(theme);
	installEventFilter(this);
	setFixedHeight(60);
	set_object_name("Set Button");
}

QLGraphic* SetButton::logo() const
{
	return m_logo_label->graphic();
}

QString SetButton::name() const
{
	return m_name_label->text();
}

std::filesystem::path SetButton::path() const
{
	return m_set_path;
}

QString SetButton::publisher() const
{
	return m_publisher_label->text();
}

bool SetButton::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::Enter)
	{
		setCursor(Qt::PointingHandCursor);
	}
	else if (event->type() == QEvent::Leave)
	{
		unsetCursor();
	}
	else if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
			emit clicked();
	}

	return false;
}

void SetButton::init_labels(const std::filesystem::path& set_path)
{
	// Construct the path to the _meta.json file
	std::filesystem::path meta_path = set_path / "_meta.json";

	if (std::filesystem::exists(meta_path))
	{
		// Open and read the _meta.json file into a string
		std::ifstream meta_file(meta_path);
		std::stringstream buffer;
		buffer << meta_file.rdbuf();
		std::string json_str = Layers::remove_whitespace(buffer.str());

		// Parse the JSON using your JSON functionality
		Layers::LJsonLexer lexer(json_str);
		Layers::LJsonParser parser(lexer);
		Layers::LJsonObject meta = parser.parse_object();

		// Extract the name and publisher from the JSON object
		std::string app_name = meta["name"].to_string().c_str();
		std::string publisher_name = meta["publisher"].to_string().c_str();

		// Set up the name label
		m_name_label->setText(app_name.c_str());
		m_name_label->set_object_name("Name Label");
		m_name_label->set_bold();

		// Set up the publisher label with opacity
		QGraphicsOpacityEffect* publisher_opacity = new QGraphicsOpacityEffect;
		publisher_opacity->setOpacity(0.6);
		m_publisher_label->setText(publisher_name.c_str());
		m_publisher_label->setGraphicsEffect(publisher_opacity);
		m_publisher_label->set_object_name("Publisher Label");
		m_publisher_label->set_font_size_f(10.5);

		if (meta.count("logo"))
		{
			std::string logo_rel_path = meta["logo"].to_string().c_str();
			if (!logo_rel_path.empty())
			{
				// Construct the full logo path relative to the set directory
				std::filesystem::path logo_path = set_path / logo_rel_path;
				if (std::filesystem::exists(logo_path))
				{
					m_logo_label->set_graphic(
						std::make_unique<QLayers::QLGraphic>(
							QString::fromStdString(logo_path.string())));
					m_logo_label->setMaximumWidth(35);
				}
				else
				{
					m_logo_label->hide();
				}
			}
			else
			{
				m_logo_label->hide();
			}
		}
		else
		{
			m_logo_label->hide();
		}
	}
	else
	{
		// Fallback if _meta.json is missing: set default texts or leave blank
		m_name_label->setText("Unknown");
		m_publisher_label->setText("");
	}
}

void SetButton::init_layout()
{
	QVBoxLayout* text_layout = new QVBoxLayout;
	text_layout->addWidget(m_name_label, Qt::AlignLeft);
	text_layout->addWidget(m_publisher_label, Qt::AlignLeft);
	text_layout->setContentsMargins(0, 0, 0 ,0);
	text_layout->setSpacing(0);

	QHBoxLayout* main_layout = new QHBoxLayout;
	if (m_logo_label)
		main_layout->addWidget(m_logo_label);
	main_layout->addLayout(text_layout);
	main_layout->addStretch();
	main_layout->setContentsMargins(12, 9, 6, 8);
	main_layout->setSpacing(8);
	setLayout(main_layout);
}
