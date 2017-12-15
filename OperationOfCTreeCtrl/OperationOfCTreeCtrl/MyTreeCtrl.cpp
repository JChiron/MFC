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

	// ����ɫ
	rtTmp = rtClnt;
	rtTmp.top = rtItem.top;
	rtTmp.bottom = rtItem.bottom;
	if (hItem == GetSelectedItem())
		pDC->FillSolidRect(rtTmp, RGB(140, 140, 140));
	else
		pDC->FillSolidRect(rtTmp, RGB(230, 230, 230));

	// ͼƬ ����
	if (ItemHasChildren(hItem))	// ������
		if (TVIS_EXPANDED & GetItemState(hItem, TVIS_EXPANDED))	// չ��״̬
			m_pImg = &m_imgExpanded;
		else
			m_pImg = &m_imgCollapse;	// �۵�״̬
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
	// �õ������ľ��,ʵ����HitTest();ѡ���������ڵ��֮��,���Դ�ʱ���ϸ�ѡ����.
	TVHITTESTINFO hti{};

	DWORD dwPos = GetMessagePos();
	hti.pt.x = dwPos << 16 >> 16;
	hti.pt.y = dwPos >> 16;

	::MapWindowPoints(0, pNMHDR->hwndFrom, &hti.pt, 1);

	HTREEITEM hItem = HitTest(&hti);

	// չ��
	if (ItemHasChildren(hItem))
		Expand(hItem, TVE_TOGGLE);

	// �ߴ���
	if (hPreItem && (hPreItem != hItem))
		SetAnyItemHeightRatioInInt(hPreItem, 1);
	SetAnyItemHeightRatioInInt(hItem, 2);

	// ���¾���
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
	// ������SetItemData()��ԭ�ߴ�,ͼƬ�ŵ�����.��ԭ�Ͳ�����bug.
	// ������bug,�㸸�ڵ�ʱ.

	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	//SetRedraw(FALSE);
	//SetAnyItemHeightRatioInInt(pNMTreeView->itemOld.hItem, 1);
	//SetAnyItemHeightRatioInInt(pNMTreeView->itemNew.hItem, 2);
	//SetRedraw(TRUE);

	*pResult = 0;
}
