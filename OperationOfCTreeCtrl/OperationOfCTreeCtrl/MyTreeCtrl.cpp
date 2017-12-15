#include "stdafx.h"
#include "MyTreeCtrl.h"
#include "resource.h"


void CMyTreeCtrl::DrawBkground(CDC * pDC)
{
	if (m_imgExpanded.IsNull())
		m_imgExpanded.LoadFromResource(AfxGetInstanceHandle(), IDBMP_EXPANDED);
	ASSERT(!m_imgExpanded.IsNull());

	if (m_imgCollapse.IsNull())
		m_imgCollapse.LoadFromResource(AfxGetInstanceHandle(), IDBMP_COLLAPSE);
	ASSERT(!m_imgCollapse.IsNull());

	if (m_imgFoliage.IsNull())
		m_imgFoliage.LoadFromResource(AfxGetInstanceHandle(), IDBMP_FOLIAGE);
	ASSERT(!m_imgFoliage.IsNull());
}

void CMyTreeCtrl::DrawItem(CDC * pDC, HTREEITEM hItem)
{
	short i = GetItemHeight();

	CRect rtClnt{}, rtTmp{};
	GetClientRect(rtClnt);
	CRect rtItem{};
	GetItemRect(hItem, &rtItem, true);
	CImage* m_pImg{};

	// 背景色
	rtTmp = rtClnt;
	rtTmp.top = rtItem.top;
	rtTmp.bottom = rtItem.bottom;
	if (hItem == GetSelectedItem())
		pDC->FillSolidRect(rtTmp, RGB(140, 140, 140));
	else
		pDC->FillSolidRect(rtTmp, RGB(230, 230, 230));

	// 图片 文字
	if (ItemHasChildren(hItem))	// 有子项
		if (TVIS_EXPANDED & GetItemState(hItem, TVIS_EXPANDED))	// 展开状态
			m_pImg = &m_imgExpanded;
		else
			m_pImg = &m_imgCollapse;	// 折叠状态
	else
		m_pImg = &m_imgFoliage;

	CRect rtImg{};
	rtImg = rtItem;
	rtImg.right = rtItem.left + rtItem.Height();
	m_pImg->Draw(pDC->m_hDC, rtImg, CRect(0, 0, m_pImg->GetWidth(), m_pImg->GetHeight()));

	CRect rtText{};
	rtText = rtItem;
	rtText.left += rtItem.Height();
	rtText.right = rtClnt.right;
	CStringW wcsText = GetItemText(hItem);
	pDC->DrawText(wcsText, rtText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

void CMyTreeCtrl::SetAnyItemHeightRatioInInt(HTREEITEM hItem, short yNewHeightRatioInInt)
{
	TVITEMEX iex{};
	iex.mask = TVIF_INTEGRAL;
	iex.hItem = hItem;
	iex.iIntegral = yNewHeightRatioInInt;
	SendMessage(TVM_SETITEM, 0, LPARAM(&iex));
}

CMyTreeCtrl::CMyTreeCtrl()
{
}


CMyTreeCtrl::~CMyTreeCtrl()
{
}
BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyTreeCtrl::OnNMClick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CMyTreeCtrl::OnTvnSelchanged)
END_MESSAGE_MAP()


void CMyTreeCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CTreeCtrl::OnPaint() for painting messages

	DrawBkground(&dc);

	HTREEITEM hItem = GetFirstVisibleItem();
	while (hItem) {
		DrawItem(&dc, hItem);
		hItem = GetNextVisibleItem(hItem);
	}
}


void CMyTreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	// 得到点击项的句柄,实现是HitTest();选择项变更是在点击之后,所以此时是上个选择项.
	TVHITTESTINFO hti{};

	DWORD dwPos = GetMessagePos();
	hti.pt.x = dwPos << 16 >> 16;
	hti.pt.y = dwPos >> 16;

	::MapWindowPoints(0, pNMHDR->hwndFrom, &hti.pt, 1);

	HTREEITEM hItem = HitTest(&hti);

	// 展开
	if (ItemHasChildren(hItem))
		Expand(hItem, TVE_TOGGLE);

	// 尺寸变更
	if (hPreItem && (hPreItem != hItem))
		SetAnyItemHeightRatioInInt(hPreItem, 1);
	SetAnyItemHeightRatioInInt(hItem, 2);

	// 更新旧项
	hPreItem = hItem;

	// 
	*pResult = 0;
}


void CMyTreeCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 1;
}


void CMyTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 可以用SetItemData()把原尺寸,图片放到项里.还原就不会有bug.
	// 这里有bug,点父节点时.

	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	//SetRedraw(FALSE);
	//SetAnyItemHeightRatioInInt(pNMTreeView->itemOld.hItem, 1);
	//SetAnyItemHeightRatioInInt(pNMTreeView->itemNew.hItem, 2);
	//SetRedraw(TRUE);

	*pResult = 0;
}
