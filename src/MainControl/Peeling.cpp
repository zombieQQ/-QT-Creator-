#include "Peeling.h"

Peeling::Peeling(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint);

	InitConnect();
}

Peeling::~Peeling()
{}

void Peeling::InitConnect()
{
	connect(ui.btn_black, &QPushButton::clicked, [this]() {
		emit SignalSetCustomWidgetQss("title_bar_black.qss");
	});

	connect(ui.btn_red, &QPushButton::clicked, [this]() {
		emit SignalSetCustomWidgetQss("title_bar_red.qss");
	});

	connect(ui.btn_pink, &QPushButton::clicked, [this]() {
		emit SignalSetCustomWidgetQss("title_bar_pink.qss");
	});

	connect(ui.btn_blue, &QPushButton::clicked, [this]() {
		emit SignalSetCustomWidgetQss("title_bar_blue.qss");
	});

	connect(ui.btn_gold, &QPushButton::clicked, [this]() {
		emit SignalSetCustomWidgetQss("title_bar_gold.qss");
	});

	connect(ui.btn_green, &QPushButton::clicked, [this]() {
		emit SignalSetCustomWidgetQss("title_bar_green.qss");
	});
}
