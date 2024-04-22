#include "CustomTitleBar.h"

#include <qpushbutton.h>

CustomTitleBar::CustomTitleBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    InitUi();

    InitConnect();
}

CustomTitleBar::~CustomTitleBar()
{}

// ��ʼ��
void CustomTitleBar::InitUi()
{
    setFixedHeight(75);

    // �����׷������Ϊ�棬�Ա����϶�ʱ��������
    setMouseTracking(true);

    // ������
    QAction* actionSearch = new QAction(ui.edit_search_);
    actionSearch->setIcon(QIcon(AppPath + StdString2QString("/../res/����.png")));
    actionSearch->setChecked(false);
    ui.edit_search_->addAction(actionSearch, QLineEdit::LeadingPosition);

    SettingQss("title_bar_red.qss");
}

// ��ʼ������
void CustomTitleBar::InitConnect()
{
    // ��С��
    connect(ui.btn_min_, &QPushButton::clicked, [this]() {
        parentWidget()->showMinimized();
    });

    // ���
    connect(ui.btn_max_, &QPushButton::clicked, [this]() {
        parentWidget()->showMaximized();
    });

    // �ر�
    connect(ui.btn_close_, &QPushButton::clicked, [this]() {
        parentWidget()->close();
    });

    // ǰһ��
	connect(ui.btn_back_, &QPushButton::clicked, [this]() {
		emit SignalForwardAndBackWard(true);
	});

    // ��һ��
	connect(ui.btn_forward_, &QPushButton::clicked, [this]() {
		emit SignalForwardAndBackWard(false);
	});

	connect(ui.btn_skin_, &QPushButton::clicked, [this](bool checked) {

        if (checked)
        {
            peeling_widget_->move(QCursor::pos().x() - 200, QCursor::pos().y() + 42);
            peeling_widget_->show();
        }
        else
            peeling_widget_->hide();

	});

    connect(peeling_widget_, &Peeling::SignalSetCustomWidgetQss, [=](const std::string& _qssFileName) {
        SettingQss(_qssFileName);
    });
}

// ����qss
void CustomTitleBar::SettingQss(const std::string& _qssFileName)
{
	QString filePath = AppPath + "/../src/MainControl/" + StdString2QString(_qssFileName);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return;

	QString qss = StdString2QString(qssFile.readAll());

	ui.btn_back_->setStyleSheet(qss);
	ui.btn_forward_->setStyleSheet(qss);
	ui.edit_search_->setStyleSheet(qss);
	ui.btn_speech_->setStyleSheet(qss);
	ui.btn_head_->setStyleSheet(qss);
	ui.btn_login_->setStyleSheet(qss);
	ui.btn_vip_->setStyleSheet(qss);
	ui.btn_skin_->setStyleSheet(qss);
	ui.btn_setting_->setStyleSheet(qss);
	ui.btn_msg_->setStyleSheet(qss);
	ui.btn_mini_->setStyleSheet(qss);
	ui.btn_min_->setStyleSheet(qss);
	ui.btn_max_->setStyleSheet(qss);
	ui.btn_close_->setStyleSheet(qss);

	qssFile.close();

    cur_qss_file_name_ = _qssFileName;

    update();
}

// ��갴���¼�
void CustomTitleBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) 
    {
        // ��¼��갴��ʱ�ĳ�ʼλ��
        dragStartPosition_ = event->globalPos() - parentWidget()->geometry().topLeft();

        peeling_widget_->hide();
        ui.btn_skin_->setChecked(false);
    }
}

// ����ƶ��¼�������ʵ���϶�Ч��
void CustomTitleBar::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        // �����ƶ�����
        QPoint moveDistance = event->globalPos() - dragStartPosition_;
        // �ƶ�������
        parentWidget()->move(moveDistance);
    }
}

// �����Զ���������ı���
void CustomTitleBar::paintEvent(QPaintEvent* event)
{
    // ��������Ʊ������ı���
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if(cur_qss_file_name_ == "title_bar_red.qss")
        painter.fillRect(rect(), QColor("#EC4141"));  // ���ñ�����ɫΪ��ɫ
	else if (cur_qss_file_name_ == "title_bar_pink.qss")
		painter.fillRect(rect(), QColor("#FBA7C7"));
	else if (cur_qss_file_name_ == "title_bar_black.qss")
		painter.fillRect(rect(), QColor("#222225"));
	else if (cur_qss_file_name_ == "title_bar_blue.qss")
		painter.fillRect(rect(), QColor("#66C0FD"));
	else if (cur_qss_file_name_ == "title_bar_green.qss")
		painter.fillRect(rect(), QColor("#53C576"));
	else if (cur_qss_file_name_ == "title_bar_gold.qss")
		painter.fillRect(rect(), QColor("#FBD180"));
}