#include "widget1.h"
#include <QtWidgets/QApplication>
#include <QtNetwork/QtNetwork>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QFont>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueIterator>
#include<qmovie.h>
#include<QButtonGroup>
#include<QThread>
#include <qthread.h>
widget1::widget1(QWidget* parent)
	: QWidget(parent)	//���캯����ʼ���б�QWidget
{
	//�����������setupUi�������ú����ɣ�����ᱻUI���ǵ����޷����
	
	ui.setupUi(this);
	
}
