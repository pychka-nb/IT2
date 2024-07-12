
// IT2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "IT2.h"
#include "IT2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define Pi 3.1415926535

// Диалоговое окно CIT2Dlg



CIT2Dlg::CIT2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IT2_DIALOG, pParent)
	, N(1024)
	, N1(300)
	, N2(600)
	, f1(0.02)
	, f2(0.06)
	, f3(0.02)
	, fd(1)
	, W(20)
	, E(0.005)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIT2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT8, N);
	DDX_Text(pDX, IDC_EDIT2, N1);
	DDX_Text(pDX, IDC_EDIT3, N2);
	DDX_Text(pDX, IDC_EDIT4, f1);
	DDX_Text(pDX, IDC_EDIT5, f2);
	DDX_Text(pDX, IDC_EDIT6, f3);
	DDX_Text(pDX, IDC_EDIT7, fd);
	DDX_Text(pDX, IDC_EDIT1, W);
	DDX_Text(pDX, IDC_EDIT10, E);
}

BEGIN_MESSAGE_MAP(CIT2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CIT2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CIT2Dlg

BOOL CIT2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	graph1.Create(GetDlgItem(IDC_SIGNAL)->GetSafeHwnd());
	graph2.Create(GetDlgItem(IDC_SIGNAL2)->GetSafeHwnd());
	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CIT2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CIT2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*Ф-ция, вычисляющая предел графика*/
double CIT2Dlg::FindMin(vector <double> data, int N)
{
	double min = data[0];
	for (int i = 0; i < N; i++)
	{
		if (min > data[i])
			min = data[i];
	}
	return min;
}
/*Ф-ция, вычисляющая предел графика*/
double CIT2Dlg::FindMax(vector <double> data, int N)
{
	double max = data[0];
	for (int i = 0; i < N; i++)
	{
		if (max < data[i])
			max = data[i];
	}
	return max;
}
void CIT2Dlg::CreateSignal()
{
	double f = 0;
	Sign.clear();
	for (int i = 0; i < N; i++)
	{
		Sign.push_back(sin(f));
		if (i < N1) {
			f += 2* Pi* f1 / fd;
		}
		else if (i < N2) {
			f += 2 * Pi * f2 / fd;
		}
		else {
			f += 2 * Pi * f3 / fd;
		}
		
	}
}

void CIT2Dlg::Signal2()
{
	a1 = 2 * cos(2 * Pi * f2 / fd);
	a2 = 1;
	A = 2;
	for (int i = 0; i < N; i++)
	{
		if (i<A)
			Sign2.push_back((Sign[i] - Sign[i]) * (Sign[i] - Sign[i]));
		else
			Sign2.push_back((Sign[i] - a1 * Sign[i - 1] + a2 * Sign[i - 2]) * (Sign[i] - a1 * Sign[i - 1] + a2 * Sign[i - 2]));

	}
}
double CIT2Dlg::WindowSize(double w)
{
	for (int i = 0; i < N; i++)
	{
		if (-W <= w && w <= W)
		{
			return 1;
		}
		else
			return 0;
	}
}
double CIT2Dlg::SearchPoints()
{
	double Nnew = 0;
	for (int i = W / 2; i < Sign3.size() - W / 2; i++)
	{
		if (Nnew == 0)
		{
			if (E >= Sign3[i])
			{
				Nnew = i;
			}
		}
		else
			if (E <= Sign3[i])
			{
				N22 = i;
				N11 = Nnew;
				return N22;
			}
	}
}

void CIT2Dlg::Svertka()
{
	for (int k = 0; k < N; k++)
	{
		g = 0;
		c = 0;
		for (int n = 0; n < N; n++)
		{
			w = WindowSize(n - k);
			g += w * Sign2[n];
			if (w == 1)
				c += 1;
		}
		Sign3.push_back(g / c);
	}
}

void CIT2Dlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	srand(time(0));
	graph1.DrawW();
	graph2.DrawW();
	UpdateData(true);
	double* data = new double[N];
		
	CreateSignal();
	for (int i = 0; i < N; i++)
	{
		keys.push_back(i / fd);
		data[i] = Sign[i];
	}
	double xmax = (N - 1) / fd,
		ymax = FindMax(Sign, N),
		ymin = FindMin(Sign, N);
	graph1.DrawOne(Sign, 0, xmax, ymin, ymax, keys);
	
	Signal2();
	for (int i = 0; i < N; i++)
	{
		data[i] = Sign2[i];
	}
	ymax = FindMax(Sign2, N);
	ymin = FindMin(Sign2, N);
	//graph2.DrawOne(Sign2, 0, xmax, ymin, ymax, keys);

	WindowSize(W);
	Svertka();
	N11 = SearchPoints();
	N22 = SearchPoints();
	UpdateData(false);
	graph2.DrawError(Sign2, Sign3, 0, xmax, ymin, ymax, E, keys);

	Sign.clear();
	keys.clear();
	Sign2.clear();
	Sign3.clear();
	windowsize.clear();
}
