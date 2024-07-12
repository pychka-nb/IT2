
// IT2Dlg.h: файл заголовка
//

#pragma once
#include <vector>
#include <iostream>
#include <time.h>
#include "Drawer.h"


// Диалоговое окно CIT2Dlg
class CIT2Dlg : public CDialogEx
{
// Создание
public:
	CIT2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IT2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double N;
	double N1;
	double N2;
	double f1;
	double f2;
	double f3;
	double fd;
	vector <double> Sign,Sign2;
	vector <double> keys;
	void CreateSignal();
	void Signal2();
	double a1, a2,A;
	double W;
	double E;
	double N11;
	double N22;
	void Svertka();
	double WindowSize(double w);
	vector <double> windowsize;
	vector <double> Sign3;
	double g;
	double c;
	double w;
	double SearchPoints();

	double FindMin(vector<double> data, int N);
	double FindMax(vector<double> data, int N);
	Drawer
		graph1, graph2;
	
	afx_msg void OnBnClickedButton1();
	

};
