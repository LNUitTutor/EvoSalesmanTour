
// EvoSalesmanTourDlg.h : header file
//

#pragma once
#define WM_UPDATE_GUI (WM_USER + 100)
#include "afxwin.h"


// CEvoSalesmanTourDlg dialog
class CEvoSalesmanTourDlg : public CDialogEx
{
// Construction
public:
	CEvoSalesmanTourDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EVOSALESMANTOUR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Кількість міст на карті
	int m_amount;
	// Розмір популяції потенційних розв'язків
	int m_population;
	// Кількість мутацій-обмінів
	int m_exchanges;
	// Кількість мутацій-поворотів
	int m_rotations;
	// Максимальна кількість поколінь
	int m_generation_limit;

	// Ділянка побудови карти
	RECT m_map_rectangle;
	// Кількість опрацьованих поколінь
	int m_generations;
	// Поточна найменша довжина
	double m_shortest;

	// Масив m_amount точок для побудови міст і відшукання туру
	CPoint* m_towns;
	// Масив m_amount+1 точок для побудови туру
	CPoint* m_route;
	afx_msg void OnBnClickedGenerate();
	afx_msg void OnBnClickedStart();
	// Зв'язок з написом - кількості випробуваних поколінь
	CStatic m_Exemined;
	// Зв'язок з написом - довжина туру
	CStatic m_Length;
protected:
	afx_msg LRESULT OnUpdateGui(WPARAM wParam, LPARAM lParam);
	// Потік для виконання обчислень
	CWinThread* m_pWinThread;
	// Метод обчислень, що буде виконаний в окремому потоці
	static UINT WorkerThread(LPVOID lpParam);
	// Прапорець зупинки потоку виконання
	bool m_StopReguired;
	// Ознака виконання потоку обчислень
	bool m_ThreadRunning;
public:
	afx_msg void OnBnClickedStop();
	CButton m_GenerateButton;
	CButton m_StartButton;
	CButton m_StopButton;
	afx_msg void OnBnClickedCancel();
};
