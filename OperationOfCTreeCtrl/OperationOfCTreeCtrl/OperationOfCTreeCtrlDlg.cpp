
// OperationOfCTreeCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OperationOfCTreeCtrl.h"
#include "OperationOfCTreeCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COperationOfCTreeCtrlDlg dialog



COperationOfCTreeCtrlDlg::COperationOfCTreeCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPERATIONOFCTREECTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COperationOfCTreeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COperationOfCTreeCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &COperationOfCTreeCtrlDlg::OnBnClickedOk)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// COperationOfCTreeCtrlDlg message handlers

BOOL COperationOfCTreeCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	// Separator ***********************************************************************************************
	if (!m_tv.m_hWnd)
	{
		CRect rt{};
		GetClientRect(rt);
		rt.DeflateRect(1, 1);

		bool bRet = m_tv.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_FULLROWSELECT, rt, this, 0x1000);
		ASSERT(bRet);

		m_tv.SetBkColor(RGB(240, 240, 240));
		// SetItemHeight()是设置控件所有项的高度.

		HTREEITEM hRoot{}, hItem{}, hFoliage{};
		CStringW wcsTmp{};
		for (int i = 0; i < 5; i++)
		{
			wcsTmp.Format(L"Root-%d", i);
			hRoot = m_tv.InsertItem(wcsTmp);

			for (int j = 0; j < 10; j++)
			{
				wcsTmp.Format(L"Item-%d-%d", i, j);
				hItem = m_tv.InsertItem(wcsTmp, hRoot);

				for (int k = 0; k < 10; k++)
				{
					wcsTmp.Format(L"Item-%d-%d-%d", i, j, k);
					m_tv.InsertItem(wcsTmp, hItem);
				}
			}
		}

		wcsTmp.Format(L"Root-5");
		m_tv.InsertItem(wcsTmp);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COperationOfCTreeCtrlDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COperationOfCTreeCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COperationOfCTreeCtrlDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	// CDialogEx::OnOK();
}


void COperationOfCTreeCtrlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_tv.m_hWnd)
	{
		CRect rt{};
		GetClientRect(rt);
		rt.DeflateRect(1, 1);
		m_tv.MoveWindow(rt);
	}
}
