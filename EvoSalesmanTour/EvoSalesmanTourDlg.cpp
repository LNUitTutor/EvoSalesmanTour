// EvoSalesmanTourDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EvoSalesmanTour.h"
#include "EvoSalesmanTourDlg.h"
#include "afxdialogex.h"
#include <ctime>
#include "Solver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEvoSalesmanTourDlg dialog



CEvoSalesmanTourDlg::CEvoSalesmanTourDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEvoSalesmanTourDlg::IDD, pParent)
	, m_amount(50)
	, m_population(5)
	, m_exchanges(2)
	, m_rotations(1)
	, m_generation_limit(1000)
	, m_towns(nullptr), m_route(nullptr)
	, m_generations(0), m_shortest(0.0)
	, m_pWinThread(nullptr)
	, m_StopReguired(false)
	, m_ThreadRunning(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEvoSalesmanTourDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDEDIT_AMOUNT, m_amount);
	DDV_MinMaxInt(pDX, m_amount, 50, 250);
	DDX_Text(pDX, IDEDIT_POPUL, m_population);
	DDV_MinMaxInt(pDX, m_population, 5, 50);
	DDX_Text(pDX, IDEDIT_EXCHG, m_exchanges);
	DDV_MinMaxInt(pDX, m_exchanges, 2, 15);
	DDX_Text(pDX, IDEDIT_ROTATE, m_rotations);
	DDV_MinMaxInt(pDX, m_rotations, 1, 7);
	DDX_Text(pDX, IDEDIT_GENER, m_generation_limit);
	DDV_MinMaxInt(pDX, m_generation_limit, 1000, 20000);
	DDX_Control(pDX, IDC_EXEMINED, m_Exemined);
	DDX_Control(pDX, IDC_LENGTH, m_Length);
	DDX_Control(pDX, IDBUTTON_GENERATE, m_GenerateButton);
	DDX_Control(pDX, IDBUTTON_START, m_StartButton);
	DDX_Control(pDX, IDBUTTON_STOP, m_StopButton);
}

BEGIN_MESSAGE_MAP(CEvoSalesmanTourDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDBUTTON_GENERATE, &CEvoSalesmanTourDlg::OnBnClickedGenerate)
	ON_BN_CLICKED(IDBUTTON_START, &CEvoSalesmanTourDlg::OnBnClickedStart)
	ON_MESSAGE(WM_UPDATE_GUI, &CEvoSalesmanTourDlg::OnUpdateGui)
	ON_BN_CLICKED(IDBUTTON_STOP, &CEvoSalesmanTourDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDCANCEL, &CEvoSalesmanTourDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CEvoSalesmanTourDlg message handlers

BOOL CEvoSalesmanTourDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	UpdateData(FALSE);
	CWnd* group = GetDlgItem(IDGROUP_TOWNS);
	RECT rect;
	group->GetWindowRect(&rect);
	this->GetClientRect(&m_map_rectangle);
	m_map_rectangle.left = rect.right + 3;
	--m_map_rectangle.right;
	--m_map_rectangle.bottom;
	srand(time(0));
	m_StartButton.EnableWindow(FALSE);
	m_StopButton.EnableWindow(FALSE);
	return TRUE;  
}

void CEvoSalesmanTourDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEvoSalesmanTourDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		dc.SelectStockObject(BLACK_PEN);
		dc.SelectStockObject(WHITE_BRUSH);
		dc.Rectangle(&m_map_rectangle);
		if (m_route != nullptr)
		{
			dc.Polyline(m_route, m_amount + 1);
			delete[] m_route;
			m_route = nullptr;
		}
		if (m_towns != nullptr)
		{
			for (int i = 0; i < m_amount; ++i) dc.Ellipse(m_towns[i].x - 4, m_towns[i].y - 4, m_towns[i].x + 3, m_towns[i].y + 3);
		}
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEvoSalesmanTourDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEvoSalesmanTourDlg::OnBnClickedGenerate()
{
	UpdateData(TRUE);
	delete[] m_towns;
	m_towns = new CPoint[m_amount];
	int width = m_map_rectangle.right - m_map_rectangle.left - 10;
	int heigth = m_map_rectangle.bottom - m_map_rectangle.top - 10;
	for (int i = 0; i < m_amount; ++i)
	{
		m_towns[i].x = rand() % width + m_map_rectangle.left + 5;
		m_towns[i].y = rand() % heigth + m_map_rectangle.top + 5;
	}
	InvalidateRect(&m_map_rectangle);
	m_StartButton.EnableWindow(TRUE);
}


void CEvoSalesmanTourDlg::OnBnClickedStart()
{
	int amount = m_amount;
	UpdateData(TRUE);
	if (amount != m_amount)
	{
		MessageBox(L"Кількість міст змінено.\nГенеруйте нову карту перед розв'язуванням", L"Помилка");
		m_GenerateButton.EnableWindow(TRUE);
		m_GenerateButton.SetFocus();
		m_StartButton.EnableWindow(FALSE);
		return;
	}
	m_GenerateButton.EnableWindow(FALSE);
	m_StartButton.EnableWindow(FALSE);
	m_StopButton.EnableWindow(TRUE);
	m_StopReguired = false;
	m_ThreadRunning = true;
	m_pWinThread = AfxBeginThread(&CEvoSalesmanTourDlg::WorkerThread, (LPVOID)this,
		THREAD_PRIORITY_NORMAL, CREATE_SUSPENDED, 0, NULL);
	m_pWinThread->m_bAutoDelete = TRUE;
	m_pWinThread->ResumeThread();
}

UINT CEvoSalesmanTourDlg::WorkerThread(LPVOID lpParam)
{
	CEvoSalesmanTourDlg* pDlg = (CEvoSalesmanTourDlg*)lpParam;
	if (NULL == pDlg || NULL == pDlg->GetSafeHwnd())
		return 1;
	
	Solver* solver = new Solver(pDlg->m_towns, pDlg->m_amount, pDlg->m_population, 
		pDlg->m_exchanges, pDlg->m_rotations, pDlg->m_generation_limit);
	solver->m_show = [pDlg, solver](int gen, double m_length)
	{ 
		pDlg->m_generations = gen;
		pDlg->m_shortest = m_length;
		pDlg->m_route = solver->Best().Route();
		::PostMessage(pDlg->GetSafeHwnd(), WM_UPDATE_GUI, 0, 0);
		Sleep(100);
	};
	pDlg->m_generations = solver->Solve(pDlg->m_StopReguired);
	pDlg->m_shortest = solver->Best().Length();
	pDlg->m_route = solver->Best().Route();
	delete solver;
	pDlg->OnUpdateGui(0, 0);
	pDlg->m_ThreadRunning = false;
	pDlg->m_GenerateButton.EnableWindow(TRUE);
	pDlg->m_StartButton.EnableWindow(TRUE);
	pDlg->m_StopButton.EnableWindow(FALSE);
	return 0;
}

afx_msg LRESULT CEvoSalesmanTourDlg::OnUpdateGui(WPARAM wParam, LPARAM lParam)
{
	CString g; g.Format(L"Минуло: %d пок.", m_generations);
	m_Exemined.SetWindowTextW(g);
	CString s; s.Format(L"Довжина: %.2f", m_shortest);
	m_Length.SetWindowTextW(s);
	InvalidateRect(&m_map_rectangle);
	return 0;
}


void CEvoSalesmanTourDlg::OnBnClickedStop()
{
	m_StopReguired = true;
	m_GenerateButton.EnableWindow(TRUE);
	m_StartButton.EnableWindow(TRUE);
	m_StopButton.EnableWindow(FALSE);
}


void CEvoSalesmanTourDlg::OnBnClickedCancel()
{
	if (m_ThreadRunning) return;
	CDialogEx::OnCancel();
}
