#pragma once

#include <QtWidgets/QWidget>
#include <QStackedWidget>
#include <QButtonGroup>
#include <qfile.h>
#include <QCoreApplication>
#include <QApplication>
#include <QPropertyAnimation>
#include <unordered_map>
#include <QParallelAnimationGroup>
#include <QTimer>

#include "interface/IRotationChart.h"
#include "ui_RotationChart.h"

#define		AppPath		QCoreApplication::applicationDirPath()
#define     BtnQss      "/../src/RotationChart/btn.qss"

enum Direction
{
    forward = 0,
    back,
};

class RotationChart 
    : public QWidget
    , public IRotationChart
{
    Q_OBJECT

public:
    RotationChart(QWidget *parent = nullptr);
    ~RotationChart();

    virtual QWidget* RotationChartShow() override;

    virtual void StartRotationChartTimer() override;

private:

    void InitUi();

    void InitConnect();

    // 鼠标进入事件
    void enterEvent(QEvent* event) override;

	// 处理鼠标离开事件
    void leaveEvent(QEvent* event) override;

    // 设置Qss
    void SetBtnQss();

    // 设置动画效果
    void SetPropertyAnimation(Direction _dir);

	// 向前动画结束
    void ForwardAnimationFinished();

    // 向后动画结束
    void BackAnimationFinished();

    QPoint AnimationEndPoint(const QPoint& _point, Direction _dir);

    QSize AnimationEndSize(const QSize& _size, Direction _dir);

private slots:

    // 向前按钮
    void SlotForwardBtnClicked();

    // 向后按钮
    void SlotBackBtnClicked();

    // 动画结束
    void SlotAnimationFinished();

private:
    Ui::RotationChartClass ui;

    // 轮播图定时器
    QTimer* timer_ = new QTimer;

    QStackedWidget* temp_widget_;

    QButtonGroup* btn_group_;

    std::vector<std::shared_ptr<QPropertyAnimation>>        animation_pos_;
    std::vector<std::shared_ptr<QPropertyAnimation>>        animation_size_;
    std::vector<std::shared_ptr<QParallelAnimationGroup>>   animation_group_;

    std::vector<QStackedWidget*>            widgets_;

    Direction                               direction_;

	int                                     left_index_;
	int                                     right_index_;
	int                                     mid_index_;
};
