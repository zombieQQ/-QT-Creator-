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

    // �������¼�
    void enterEvent(QEvent* event) override;

	// ��������뿪�¼�
    void leaveEvent(QEvent* event) override;

    // ����Qss
    void SetBtnQss();

    // ���ö���Ч��
    void SetPropertyAnimation(Direction _dir);

	// ��ǰ��������
    void ForwardAnimationFinished();

    // ��󶯻�����
    void BackAnimationFinished();

    QPoint AnimationEndPoint(const QPoint& _point, Direction _dir);

    QSize AnimationEndSize(const QSize& _size, Direction _dir);

private slots:

    // ��ǰ��ť
    void SlotForwardBtnClicked();

    // ���ť
    void SlotBackBtnClicked();

    // ��������
    void SlotAnimationFinished();

private:
    Ui::RotationChartClass ui;

    // �ֲ�ͼ��ʱ��
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
