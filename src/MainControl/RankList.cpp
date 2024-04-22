#include "RankList.h"

RankList::RankList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	InitUi();

	InitData();
}

RankList::~RankList()
{}

QWidget* RankList::GetWidget()
{
	CreateSoarTableWidget();

	CreateNewSongTableWidget();

	scroll_area_ = new QScrollArea;
	QScrollBar* verticalScrollBar = scroll_area_->verticalScrollBar();

	QString qss = OpenQssFile(ScrollAreaQss);

	verticalScrollBar->setStyleSheet(qss);

	scroll_area_->setFrameShape(QFrame::NoFrame);
	scroll_area_->setWidgetResizable(true);  // ���ù��������Զ�������С

	// ����һ���ڲ���С�����������ڹ���������
	QWidget* contentWidget = new QWidget(scroll_area_);
	QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);

	contentLayout->addWidget(this);

	// ���ù��������С����
	scroll_area_->setWidget(contentWidget);

	return scroll_area_;
}

void RankList::InitUi()
{
	QString qss = OpenQssFile(ViewAllQss);

	ui.new_song_btn->setStyleSheet(qss);
	ui.soar_btn->setStyleSheet(qss);

	// ��ȡ��ǰ����
	QDateTime currentDateTime = QDateTime::currentDateTime();

	// ��ȡ��ǰ����
	QDate currentDate = currentDateTime.date();

	// ��ȡ�·ݺ�����
	int month = currentDate.month();
	int day = currentDate.day();

	QString date = QString::number(month) + StdString2QString("��") + QString::number(day) + StdString2QString("�ո���");
	ui.soar_label->setText(StdString2QString("�����") + "\n" + date);
	ui.new_song_label->setText(StdString2QString("�¸��") + "\n" + date);
}

void RankList::InitData()
{
	soarTableData.push_back({ "1", "302%", "Outlaw������֮ͽ��", "Sewas" });
	soarTableData.push_back({ "2", "285%", "����1440", "ʱ��������" });
	soarTableData.push_back({ "3", "202%", "ʮ���µ��漣��������������", "������" });
	soarTableData.push_back({ "4", "188%", "Qay Raggi�������ɫ��", "Ahmatjan-Ebrayim" });
	soarTableData.push_back({ "5", "188%", "��𿪳���", "�����Ϸ�������ѧ����" });

	newTableData.push_back({ "1", "202%", "��Ѿ��Ѿ��live��", "������" });
	newTableData.push_back({ "2", "185%", "��ս", "Vinida (���ݴ�)" });
	newTableData.push_back({ "3", "302%", "ʮ���µ��漣��������������", "������" });
	newTableData.push_back({ "4", "108%", "Ļ������", "����Bo" });
	newTableData.push_back({ "5", "128%", "����", "Ѧ֮ǫ" });
}

void RankList::CreateSoarTableWidget()
{
	soarTableWidget_ = global_gui_factory_->CreateHeaderLessTableWidget();

	soarTableWidget_->SetRowCol(5, 4);

	soarTableWidget_->UpdateTableWidget(soarTableData);

	QVBoxLayout* layout = new QVBoxLayout(ui.soar_list);
	layout->addWidget((QWidget*)soarTableWidget_->GetWidget());
	layout->setContentsMargins(0, 0, 0, 0);
}

void RankList::CreateNewSongTableWidget()
{
	newSongTableWidget_ = global_gui_factory_->CreateHeaderLessTableWidget();

	newSongTableWidget_->SetRowCol(5, 4);

	newSongTableWidget_->UpdateTableWidget(newTableData);

	QVBoxLayout* layout = new QVBoxLayout(ui.new_song_list);
	layout->addWidget((QWidget*)newSongTableWidget_->GetWidget());

	layout->setContentsMargins(0, 0, 0, 0);
}

QString RankList::OpenQssFile(std::string _qssFile)
{
	QString filePath = AppPath + StdString2QString(_qssFile);
	QFile qssFile(filePath);
	if (!qssFile.open(QFile::ReadOnly | QFile::Text))
		return "";

	QString qss = StdString2QString(qssFile.readAll());

	qssFile.close();

	return qss;
}