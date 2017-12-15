#pragma once
#include "afxcmn.h"
class CMyTreeCtrl :
	public CTreeCtrl
{
	// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	// Attributions ********************************************************************************************
public:
	CImage m_imgExpanded{}, m_imgCollapse{}, m_imgFoliage{};

	// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	// Methods *************************************************************************************************
public:
	void DrawBkground(CDC* pDC);									// 绘制背景色
	void DrawItem(CDC* pDC, HTREEITEM hItem);						// 绘制项
	void SetAnyItemHeight(HTREEITEM hItem, short yNewHeight);		// 设制任何项的高度

	// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	// Separator ***********************************************************************************************
public:
	CMyTreeCtrl();
	~CMyTreeCtrl();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);		// 实现项的单击响应
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);		// 取消项的双击响应
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);	// 实现改变项时的响应
};

