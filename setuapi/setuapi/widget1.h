#pragma once
#include <qwidget.h>
#include <QtWidgets/QMainWindow>	
#include"ui_Widget1.h"
class widget1 :
	public QWidget
{
	Q_OBJECT	//��Ҫ�ĺ�

public:
	widget1(QWidget* parent = Q_NULLPTR);	//������
	Ui::Widget1class ui;
private:
	//ui�������Ǵ������������Զ����ɵ�"ui_XXX.h"ͷ�ļ����Ѷ���
};

