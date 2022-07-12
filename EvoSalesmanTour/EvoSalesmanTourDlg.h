
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
	// ʳ������ ��� �� ����
	int m_amount;
	// ����� ��������� ����������� ����'����
	int m_population;
	// ʳ������ �������-�����
	int m_exchanges;
	// ʳ������ �������-��������
	int m_rotations;
	// ����������� ������� �������
	int m_generation_limit;

	// ĳ����� �������� �����
	RECT m_map_rectangle;
	// ʳ������ ������������ �������
	int m_generations;
	// ������� �������� �������
	double m_shortest;

	// ����� m_amount ����� ��� �������� ��� � ��������� ����
	CPoint* m_towns;
	// ����� m_amount+1 ����� ��� �������� ����
	CPoint* m_route;
	afx_msg void OnBnClickedGenerate();
	afx_msg void OnBnClickedStart();
	// ��'���� � ������� - ������� ������������ �������
	CStatic m_Exemined;
	// ��'���� � ������� - ������� ����
	CStatic m_Length;
protected:
	afx_msg LRESULT OnUpdateGui(WPARAM wParam, LPARAM lParam);
	// ���� ��� ��������� ���������
	CWinThread* m_pWinThread;
	// ����� ���������, �� ���� ��������� � �������� ������
	static UINT WorkerThread(LPVOID lpParam);
	// ��������� ������� ������ ���������
	bool m_StopReguired;
	// ������ ��������� ������ ���������
	bool m_ThreadRunning;
public:
	afx_msg void OnBnClickedStop();
	CButton m_GenerateButton;
	CButton m_StartButton;
	CButton m_StopButton;
	afx_msg void OnBnClickedCancel();
};
