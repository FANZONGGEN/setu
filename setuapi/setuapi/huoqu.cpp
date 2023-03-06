#pragma execution_character_set("utf-8")
#include "huoqu.h"
huoqu::huoqu()
{
	/*m_pHttpMgr.reset(new QNetworkAccessManager());
	m_pHttpMgr1.reset(new QNetworkAccessManager());*/
	//eventLoop.reset(new QEventLoop);
	//eventLoop1.reset(new QEventLoop);
	//currentPicture.reset(new QPixmap());
	curPath = QDir::currentPath();
}
void huoqu::run()
{
	while (!stop)
	{
		//QNetworkAccessManager* m_pHttpMgr = new QNetworkAccessManager();
		QSharedPointer<QNetworkAccessManager> m_pHttpMgr(new QNetworkAccessManager());
		//����url
		//qDebug() << url;
		//QString url = "https://i.pixiv.cat/img-original/img/2020/09/06/23/55/59/84206039_p0.jpg";
		QNetworkRequest requestInfo;
		requestInfo.setUrl(QUrl(url));

		//����¼�ѭ�����ƣ����غ������к����
		QEventLoop eventLoop;
		QNetworkReply* reply = m_pHttpMgr->get(requestInfo);
		//QSharedPointer<QNetworkReply> reply(m_pHttpMgr->get(requestInfo));
		//connect(reply.get(), SIGNAL(finished()), &eventLoop, SLOT(quit()));
		connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
		eventLoop.exec();       //block until finish
		//disconnect(reply.get(), SIGNAL(finished()), &eventLoop, SLOT(quit()));
		disconnect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
		//������
		if (reply->error() == QNetworkReply::NoError&& !stop)
		{
			//qDebug() << "request protobufHttp NoError 1";
		}
		else
		{

			//qDebug() << "request protobufHttp handle errors here 1";
			//delete reply;
			reply->deleteLater();
			reply = nullptr;
			continue;
			//QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
			//statusCodeV��HTTP����������Ӧ�룬reply->error()��Qt����Ĵ����룬���Բο�QT���ĵ�
			//qDebug("request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
			//qDebug(qPrintable(reply->errorString()));
		}
		//���󷵻صĽ��
		responseByte = reply->readAll();
		//delete reply;
		reply->deleteLater();
		reply = nullptr;
		s1 = QJsonDocument::fromJson(responseByte).object().value("data").toArray().at(0).toObject().value("urls").toObject().value("original").toString();
		if (s1.isEmpty())
		{
			continue;
		}
		QString title = QJsonDocument::fromJson(responseByte).object().value("data").toArray().at(0).toObject().value("title").toString();
		QString pid = QString::number(QJsonDocument::fromJson(responseByte).object().value("data").toArray().at(0).toObject().value("pid").toInt());
		//qDebug() << s1;
		//qDebug() << QJsonDocument::fromJson(responseByte).object().value("data").toArray().at(0).toObject().value("title").toString();
		filename = curPath + "/" + sub + "/"+ QString("%1%2.%3").arg(title).arg(pid).arg(s1.right(3));
		f1.setFileName(filename);
		if (f1.exists())
		{
			continue;
		}
		
		//QNetworkAccessManager* m_pHttpMgr1 = new QNetworkAccessManager();
		QSharedPointer<QNetworkAccessManager> m_pHttpMgr1(new QNetworkAccessManager());
		//����url
		//QString url1 = "https://api.lolicon.app/setu/?apikey=23327833606bf37cbb86f3";
		//QString url = "https://i.pixiv.cat/img-original/img/2020/09/06/23/55/59/84206039_p0.jpg";
		QNetworkRequest requestInfo1;
		requestInfo1.setUrl(QUrl(s1));

		//����¼�ѭ�����ƣ����غ������к����
		QEventLoop eventLoop1;
		QNetworkReply* reply1 = m_pHttpMgr1->get(requestInfo1);
		//QSharedPointer<QNetworkReply> reply1(m_pHttpMgr->get(requestInfo));
		//connect(reply1.get(), SIGNAL(finished()), &eventLoop1, SLOT(quit()));
		connect(reply1, SIGNAL(finished()), &eventLoop1, SLOT(quit()));
		eventLoop1.exec();       //block until finish
		//disconnect(reply1.get(), SIGNAL(finished()), &eventLoop1, SLOT(quit()));
		disconnect(reply1, SIGNAL(finished()), &eventLoop1, SLOT(quit()));
		//������
		if (reply1->error() == QNetworkReply::NoError && !stop)
		{
			//qDebug() << "request protobufHttp NoError 2";
		}
		else
		{
			//qDebug() << "request protobufHttp handle errors here 2";
			//delete reply1;
			reply1->deleteLater();
			reply1 = nullptr;
			continue;
			//QVariant statusCodeV = reply1->attribute(QNetworkRequest::HttpStatusCodeAttribute);
			//statusCodeV��HTTP����������Ӧ�룬reply->error()��Qt����Ĵ����룬���Բο�QT���ĵ�
			//qDebug("request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply1->error());
			//qDebug(qPrintable(reply1->errorString()));
		}
		//���󷵻صĽ��
		responseByte = reply1->readAll();
		//delete reply1;
		reply1->deleteLater();
		reply1 = nullptr;
		if (!f1.open(QIODevice::WriteOnly)) {
			continue;
		}
		f1.write(responseByte);
		f1.close();
		//currentPicture->loadFromData(responseByte);
		//filename = curPath + "/" + sub + "/" + QString::number(threadnum) + QDateTime::currentDateTime().toString("yyMMddhhmmss.%1").arg(s1.right(3));
		//currentPicture->save(filename);//����ͼƬ
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

void huoqu::seturl()
{
	url = apiurl;
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
	//requestInfo.setUrl(QUrl(url));
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

huoqu::~huoqu()
{
	/*m_pHttpMgr.clear();
	m_pHttpMgr1.clear();*/
	//currentPicture.clear();
	f1.close();
}

QString huoqu::getTag() const
{
	return tag;
}

void huoqu::setTag(const QString& value)
{
	tag = "tag=" + value;
}