#pragma execution_character_set("utf-8")
#include "huoqu.h"
huoqu::huoqu()
{

}
void huoqu::run()
{
	while (!stop)
	{
		auto url = apiurl;
		if (isR18 == 0)
		{
			url = url + tag;
		}
		else if (isR18 == 1)
		{
			url = url + tag + "&r18=1";
		}
		else if (isR18 == 2)
		{
			url = url + tag + "&r18=2";
		}
		QNetworkAccessManager *m_pHttpMgr = new QNetworkAccessManager();
		//����url
		//qDebug() << url;
		//QString url = "https://i.pixiv.cat/img-original/img/2020/09/06/23/55/59/84206039_p0.jpg";
		QNetworkRequest requestInfo;
		requestInfo.setUrl(QUrl(url));

		//����¼�ѭ�����ƣ����غ������к����
		QEventLoop eventLoop;
		QNetworkReply *reply = m_pHttpMgr->get(requestInfo);
		connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
		eventLoop.exec();       //block until finish
		//������
		if (reply->error() == QNetworkReply::NoError)
		{
			//qDebug() << "request protobufHttp NoError";
		}
		else
		{
			//qDebug() << "request protobufHttp handle errors here";
			continue;
			//QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
			//statusCodeV��HTTP����������Ӧ�룬reply->error()��Qt����Ĵ����룬���Բο�QT���ĵ�
			//qDebug("request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
			//qDebug(qPrintable(reply->errorString()));
		}
		//���󷵻صĽ��
		QByteArray responseByte = reply->readAll();
		QJsonObject json;
		json = QJsonDocument::fromJson(responseByte).object();
		auto data = json.value("data").toArray();
		auto s1 = data.at(0).toObject().value("urls").toObject().value("original").toString();
		if (s1.isEmpty())
		{
			continue;
		}
		//qDebug() << s1;



		QNetworkAccessManager *m_pHttpMgr1 = new QNetworkAccessManager();
		//����url
		//QString url1 = "https://api.lolicon.app/setu/?apikey=23327833606bf37cbb86f3";
		//QString url = "https://i.pixiv.cat/img-original/img/2020/09/06/23/55/59/84206039_p0.jpg";
		QNetworkRequest requestInfo1;
		requestInfo1.setUrl(QUrl(s1));

		//����¼�ѭ�����ƣ����غ������к����
		QEventLoop eventLoop1;
		QNetworkReply *reply1 = m_pHttpMgr1->get(requestInfo1);
		connect(reply1, SIGNAL(finished()), &eventLoop1, SLOT(quit()));
		eventLoop1.exec();       //block until finish
		//������
		if (reply1->error() == QNetworkReply::NoError)
		{
			//qDebug() << "request protobufHttp NoError";
		}
		else
		{
			//qDebug() << "request protobufHttp handle errors here";
			continue;
			//QVariant statusCodeV = reply1->attribute(QNetworkRequest::HttpStatusCodeAttribute);
			//statusCodeV��HTTP����������Ӧ�룬reply->error()��Qt����Ĵ����룬���Բο�QT���ĵ�
			//qDebug("request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply1->error());
			//qDebug(qPrintable(reply1->errorString()));
		}
		//���󷵻صĽ��
		QByteArray responseByte1 = reply1->readAll();

		auto currentPicture = new QPixmap;
		currentPicture->loadFromData(responseByte1);
		QDateTime now;
		// QString filename =  tr("/storage/emulated/0/ɫͼ/")+now.currentDateTime().toString("yyMMddhhmmss.jpg");
		QString filename;
		QString  curPath = QDir::currentPath();
		QDir dir(curPath);
		QString sub = "ɫͼ";
		dir.mkdir(sub);
		filename = curPath + "/" + sub + "/" + QString::number(threadnum) + now.currentDateTime().toString("yyMMddhhmmss.%1").arg(s1.right(3));
		currentPicture->save(filename);//����ͼƬ
		//qDebug() << filename;
		emit jieshu(filename);
	}
}

bool huoqu::getStop() const
{
	return stop;
}

void huoqu::setStop(bool value)
{
	stop = value;
}

int huoqu::getThreadnum() const
{
	return threadnum;
}

void huoqu::setThreadnum(int value)
{
	threadnum = value;
}

int huoqu::getIsR18() const
{
	return isR18;
}

void huoqu::setIsR18(int value)
{
	isR18 = value;
}

QString huoqu::getTag() const
{
	return tag;
}

void huoqu::setTag(const QString &value)
{
	tag = "tag=" + value;
}