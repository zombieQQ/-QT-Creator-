#include "RotationChart.h"

RotationChart::RotationChart(QWidget *parent)
    : QWidget(parent)
	, left_index_(7)
	, mid_index_(0)
	, right_index_(1)
	, btn_group_(new QButtonGroup)
{
    ui.setupUi(this);

	InitUi();

	InitConnect();
}

RotationChart::~RotationChart()
{
	if (temp_widget_)
	{
		delete temp_widget_;
		temp_widget_ = nullptr;
	}
}

QWidget* RotationChart::RotationChartShow()
{
    return this;
}

void RotationChart::StartRotationChartTimer()
{
	timer_->start();
}

void RotationChart::InitUi()
{
	// 隐藏按钮
	ui.btn_forward_->setVisible(false);
	ui.btn_back_->setVisible(false);

	for (int i = 0; i < 3; i++)
	{
		QStackedWidget* widget = new QStackedWidget();
		widgets_.emplace_back(widget);
	}

	widgets_[0] = ui.mid_widget_;
	widgets_[1] = ui.left_widget_;
	widgets_[2] = ui.right_widget_;

	ui.mid_widget_->setCurrentIndex(mid_index_);
	ui.left_widget_->setCurrentIndex(left_index_);
	ui.right_widget_->setCurrentIndex(right_index_);

	for (int i = 0; i < 3; i++)
	{
		animation_pos_.emplace_back(std::make_shared<QPropertyAnimation>(widgets_[i], "pos"));
		animation_size_.emplace_back(std::make_shared<QPropertyAnimation>(widgets_[i], "size"));
		animation_group_.emplace_back(std::make_shared<QParallelAnimationGroup>());
	}

	// 轮播图下方按钮添加到Group管理
	btn_group_->addButton(ui.pushButton, 0);
	btn_group_->addButton(ui.pushButton_2, 1);
	btn_group_->addButton(ui.pushButton_3, 2);
	btn_group_->addButton(ui.pushButton_4, 3);
	btn_group_->addButton(ui.pushButton_5, 4);
	btn_group_->addButton(ui.pushButton_6, 5);
	btn_group_->addButton(ui.pushButton_7, 6);
	btn_group_->addButton(ui.pushButton_8, 7);

	// 设置为单选按钮，意味着每次只能有一个按钮被选中
	btn_group_->setExclusive(true);

	btn_group_->button(mid_index_)->setChecked(true);

	timer_->setInterval(2000);

	SetBtnQss();
}

void RotationChart::InitConnect()
{
	connect(ui.btn_forward_, &QPushButton::clicked, this, &RotationChart::SlotForwardBtnClicked);

	connect(ui.btn_back_, &QPushButton::clicked, this, &RotationChart::SlotBackBtnClicked);

	connect(animation_group_[0].get(), &QAbstractAnimation::finished, this, &RotationChart::SlotAnimationFinished);

	connect(timer_, &QTimer::timeout, [this]() {
		SlotForwardBtnClicked();
	});
}

// 处理鼠标进入事件
void RotationChart::enterEvent(QEvent* event)
{
	// 没有使用到事件对象，通过 Q_UNUSED(event) 标记为未使用
	Q_UNUSED(event)
	
	ui.btn_forward_->setVisible(true);
	ui.btn_back_->setVisible(true);
}

// 处理鼠标离开事件
void RotationChart::leaveEvent(QEvent* event)
{
	Q_UNUSED(event)
	
	ui.btn_forward_->setVisible(false);
	ui.btn_back_->setVisible(false);
}

// 设置动画效果
void RotationChart::SetPropertyAnimation(Direction _dir)
{
	QPoint point = QPoint(ui.mid_widget_->geometry().x(), ui.mid_widget_->geometry().y());
	animation_pos_[0]->setStartValue(point);
	animation_pos_[0]->setEndValue(AnimationEndPoint(point, _dir));

	point = QPoint(ui.left_widget_->geometry().x(), ui.left_widget_->geometry().y());
	animation_pos_[1]->setStartValue(point);
	animation_pos_[1]->setEndValue(AnimationEndPoint(point, _dir));

	point = QPoint(ui.right_widget_->geometry().x(), ui.right_widget_->geometry().y());
	animation_pos_[2]->setStartValue(point);
	animation_pos_[2]->setEndValue(AnimationEndPoint(point, _dir));

	QSize size = QSize(QSize(ui.mid_widget_->width(), ui.mid_widget_->height()));
	animation_size_[0]->setStartValue(size);
	animation_size_[0]->setEndValue(AnimationEndSize(size, _dir));

	size = QSize(QSize(ui.left_widget_->width(), ui.left_widget_->height()));
	animation_size_[1]->setStartValue(QSize(ui.left_widget_->width(), ui.left_widget_->height()));
	animation_size_[1]->setEndValue(AnimationEndSize(size, _dir));

	size = QSize(QSize(ui.right_widget_->width(), ui.right_widget_->height()));
	animation_size_[2]->setStartValue(QSize(ui.right_widget_->width(), ui.right_widget_->height()));
	animation_size_[2]->setEndValue(AnimationEndSize(size, _dir));
}

// 设置Qss
void RotationChart::SetBtnQss()
{
	QString filePath = AppPath + StdString2QString(BtnQss);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return;

	QString qss = StdString2QString(qssFile.readAll());

	for (auto it : btn_group_->buttons())
		it->setStyleSheet(qss);

	qssFile.close();
}

// 向前动画结束
void RotationChart::ForwardAnimationFinished()
{
	temp_widget_ = widgets_[0];
	widgets_[0] = widgets_[2];
	widgets_[2] = widgets_[1];
	widgets_[1] = temp_widget_;

	widgets_[1]->stackUnder(widgets_[0]);
	widgets_[2]->stackUnder(widgets_[0]);

	if (mid_index_ == 7)
		mid_index_ = 0;
	else
		mid_index_++;

	if (left_index_ == 7)
		left_index_ = 0;
	else
		left_index_++;

	if (right_index_ == 7)
		right_index_ = 0;
	else
		right_index_++;

	widgets_[0]->setCurrentIndex(mid_index_);
	widgets_[1]->setCurrentIndex(left_index_);
	widgets_[2]->setCurrentIndex(right_index_);

	btn_group_->button(mid_index_)->setChecked(true);
}

// 向后动画结束
void RotationChart::BackAnimationFinished()
{
	temp_widget_ = widgets_[0];
	widgets_[0] = widgets_[1];
	widgets_[1] = widgets_[2];
	widgets_[2] = temp_widget_;

	widgets_[1]->stackUnder(widgets_[0]);
	widgets_[2]->stackUnder(widgets_[0]);

	if (mid_index_ == 0)
		mid_index_ = 7;
	else
		mid_index_--;

	if (left_index_ == 0)
		left_index_ = 7;
	else
		left_index_--;

	if (right_index_ == 0)
		right_index_ = 7;
	else
		right_index_--;

	widgets_[0]->setCurrentIndex(mid_index_);
	widgets_[1]->setCurrentIndex(left_index_);
	widgets_[2]->setCurrentIndex(right_index_);

	btn_group_->button(mid_index_)->setChecked(true);
}

QPoint RotationChart::AnimationEndPoint(const QPoint& _point, Direction _dir)
{
	if (_dir == forward)
	{
		if (_point.x() == 33 && _point.y() == 30)
			return QPoint(307, 30);
		else if (_point.x() == 170 && _point.y() == 10)
			return QPoint(33, 30);
		else if (_point.x() == 307 && _point.y() == 30)
			return QPoint(170, 10);
	}
	else if (_dir == back)
	{
		if (_point.x() == 33 && _point.y() == 30)
			return QPoint(170, 10);
		else if (_point.x() == 170 && _point.y() == 10)
			return QPoint(307, 30);
		else if (_point.x() == 307 && _point.y() == 30)
			return QPoint(33, 30);
	}

	return QPoint();
}

QSize RotationChart::AnimationEndSize(const QSize& _size, Direction _dir)
{
	if (_dir == forward)
	{
		if (_size.height() == 203)
			return QSize(_size.width(), 247);
		else if(_size.height() == 247)
			return QSize(_size.width(), 202);
		else if (_size.height() == 202)
			return QSize(_size.width(), 203);
	}
	else if (_dir == back)
	{
		if (_size.height() == 203)
			return QSize(_size.width(), 202);
		else if (_size.height() == 247)
			return QSize(_size.width(), 203);
		else if (_size.height() == 202)
			return QSize(_size.width(), 247);
	}

	return QSize();
}

// 向前按钮
void RotationChart::SlotForwardBtnClicked()
{
	direction_ = forward;

	SetPropertyAnimation(forward);

	for (int i = 0; i < 3; i++)
	{
		animation_pos_[i]->setDuration(200);
		animation_size_[i]->setDuration(200);

		animation_group_[i]->addAnimation(animation_pos_[i].get());
		animation_group_[i]->addAnimation(animation_size_[i].get());

		animation_group_[i]->start();
	}
}

// 向后按钮
void RotationChart::SlotBackBtnClicked()
{
	direction_ = back;

	SetPropertyAnimation(back);

	for (int i = 0; i < 3; i++)
	{
		animation_pos_[i]->setDuration(200);
		animation_size_[i]->setDuration(200);

		animation_group_[i]->addAnimation(animation_pos_[i].get());
		animation_group_[i]->addAnimation(animation_size_[i].get());

		animation_group_[i]->start();
	}
}

// 动画结束
void RotationChart::SlotAnimationFinished()
{
	if (direction_ == forward)
		ForwardAnimationFinished();
	else if (direction_ == back)
		BackAnimationFinished();
}