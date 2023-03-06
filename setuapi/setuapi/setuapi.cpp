#pragma execution_character_set("utf-8")
#include "setuapi.h"




setuapi::setuapi(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Dirmik();
	ui.label->setScaledContents(true);
	timer = new QTimer();
	connect(timer, &QTimer::timeout, this, &setuapi::LoadImage);
	connect(ui.pushButton, &QPushButton::clicked, [=]() {
		if (ui.pushButton->text() == "���ɫͼ")
		{
			ui.pushButton->setText("ֹͣ��ȡ");
			auto num = ui.spinBox->value();
			auto tag = ui.lineEdit->text();
			int isR18 = 0;
			if (ui.radioButton->isChecked())
			{
				isR18 = 0;
			}
			else if (ui.radioButton_2->isChecked())
			{
				isR18 = 1;
			}
			else if (ui.radioButton_3->isChecked())
			{
				isR18 = 2;
			}
			for (int i = 0; i < num; i++)
			{
				QSharedPointer<huoqu> thread(new huoqu);
				thread->setIsR18(isR18);
				thread->setTag(tag);
				thread->setThreadnum(i + 1);
				thread->seturl();
				/*connect(thread.get(), &huoqu::jieshu, this, [=](QString filename) {
					QMutexLocker lock(&Mutex_filename);
					Filenames.enqueue(filename);
					},Qt::QueuedConnection);*/
					//connect(thread.get(), &huoqu::jieshu, this,&setuapi::Queuefilename, Qt::QueuedConnection);
				connect(thread.get(), &huoqu::jieshu, this, &setuapi::Queuefilename);
				Threads.push_back(thread);
			}
			foreach(auto &thread, Threads)
			{
				thread->start();
			}
			timer->start(1000);
		}
		else if (ui.pushButton->text() == "ֹͣ��ȡ")
		{

			foreach(auto &thread, Threads)
			{
				thread->setStop(true);
				thread->quit();

			}
			while (true)
			{
				auto stopnum = false;
				foreach(auto &thread, Threads)
				{
					stopnum = stopnum || thread->isRunning();
				}
				if (stopnum == false)
				{
					break;
				}
			}
			foreach(auto& thread, Threads)
			{
				disconnect(thread.get(), &huoqu::jieshu, this, &setuapi::Queuefilename);
			}
			Threads.clear();
			timer->stop();
			Filenames.clear();
			ui.pushButton->setText("���ɫͼ");
		}
		});
}
setuapi::~setuapi()
{
	foreach(auto & thread, Threads)
	{
		thread->setStop(true);
		thread->quit();

	}
	while (true)
	{
		auto stopnum = false;
		foreach(auto & thread, Threads)
		{
			stopnum = stopnum || thread->isRunning();
		}
		if (stopnum == false)
		{
			break;
		}
	}
	foreach(auto& thread, Threads)
	{
		disconnect(thread.get(), &huoqu::jieshu, this, &setuapi::Queuefilename);
	}
	Threads.clear();
	timer->stop();
}
void setuapi::LoadImage()
{

	QMutexLocker lock(&Mutex_filename);

	if (!Filenames.isEmpty())
	{
		QString filename;
		filename = Filenames.dequeue();
		//qDebug() << filename;
		QPixmap pixmap;
		if (pixmap.load(filename))
		{
			//QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			pixmap = pixmap.scaled(ui.label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			ui.label->setPixmap(pixmap);
			//ui.label->setScaledContents(true);
		}
	}
}
void setuapi::Dirmik()
{
	QString  curPath = QDir::currentPath();
	QDir dir(curPath);

	QString sub = "ɫͼ";
	dir.mkdir(sub);
}
void setuapi::Queuefilename(QString filename)
{
	QMutexLocker lock(&Mutex_filename);
	Filenames.enqueue(filename);
}