#include "stdafx.h"
#include "GridCtrl.h"
#include ".\gridctrl.h"

//////////////////////////// Grid edit /////////////////////////
IMPLEMENT_DYNAMIC(CGEdit, CEdit)
CGEdit::CGEdit(){
}

CGEdit::~CGEdit(){
}

BEGIN_MESSAGE_MAP(CGEdit, CEdit)
	ON_WM_ENABLE()
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

void CGEdit::OnEnable(BOOL bEnable){
	SetReadOnly(!bEnable);
}

BOOL CGEdit::PreCreateWindow(CREATESTRUCT& cs){
	cs.dwExStyle=WS_EX_STATICEDGE;
	
	if(cs.style&ES_READONLY)m_bkBrush.CreateSolidBrush(G_EDIT_RDNL_CLR);
	else m_bkBrush.CreateSolidBrush(0xffffff);

	return CEdit::PreCreateWindow(cs);
}
void CGEdit::OnNcPaint(){
	CWindowDC dc(this);

	CRect rctClient;
	GetClientRect(&rctClient);

	CRect rctWnd;
	GetWindowRect(&rctWnd);

	ClientToScreen(&rctClient);
	rctClient.OffsetRect(-rctWnd.TopLeft());
	rctWnd.OffsetRect(-rctWnd.TopLeft());

	dc.ExcludeClipRect(&rctClient);

	if(GetStyle()&ES_READONLY)dc.Draw3dRect(rctWnd,G_EDIT_RDNL_CLR,G_EDIT_RDNL_CLR);
	else dc.Draw3dRect(rctWnd,0xffffff,0xffffff);
}
HBRUSH CGEdit::CtlColor(CDC* pDC, UINT nCtlColor){
	pDC->SetBkMode(TRANSPARENT);
	return m_bkBrush;
}
BOOL CGEdit::SetReadOnly(bool bReadOnly){
	m_bkBrush.DeleteObject();

	if(bReadOnly)m_bkBrush.CreateSolidBrush(G_EDIT_RDNL_CLR);
	else m_bkBrush.CreateSolidBrush(0xffffff);

	return CEdit::SetReadOnly(bReadOnly);
}

//////////////////////// Grid static ////////////////////////////
IMPLEMENT_DYNAMIC(CGStatic, CStatic)
CGStatic::CGStatic(){
}

CGStatic::~CGStatic(){
}

BEGIN_MESSAGE_MAP(CGStatic, CStatic)
END_MESSAGE_MAP()

LRESULT CGStatic::WindowProc(UINT message, WPARAM wParam, LPARAM lParam){
	/*switch(message){
		case WM_PAINT:
			{
				CPaintDC dcPaint(this);

				RECT rct;
				GetClientRect(&rct);

				CDC MemDC;
				MemDC.CreateCompatibleDC(&dcPaint);

				CBitmap bmp;
				bmp.CreateCompatibleBitmap(&dcPaint,rct.right,rct.bottom);

				MemDC.SelectObject(&bmp);

				CWnd* pWnd(GetWindow(GW_CHILD));

				while(pWnd){
					CRect rctChild;
					pWnd->GetWindowRect(&rctChild);

					ScreenToClient(&rctChild);
					dcPaint.ExcludeClipRect(&rctChild);

					pWnd=GetWindow(GW_HWNDNEXT);
				}
				
				DefWindowProc(WM_PAINT,(WPARAM)MemDC.m_hDC,0);

				MemDC.DrawFrameControl(CRect(100,0,130,16),DFC_SCROLL,DFCS_SCROLLDOWN);

				dcPaint.BitBlt(0,0,rct.right,rct.bottom,&MemDC,0,0,SRCCOPY);
			}
			return true;
	}*/
	return CStatic::WindowProc(message, wParam, lParam);
}

///////////////////////////////////////////////////
#define GRID_CTRL_CLASS	"GridCtrl"

CGridCtrl::CGridCtrl():m_pGridMgr(0),m_bMoveSprt(false){
	HINSTANCE hInst(AfxGetInstanceHandle());
	WNDCLASSEX wndClassEx;

	if(!::GetClassInfoEx(hInst,GRID_CTRL_CLASS,&wndClassEx)){

		wndClassEx.cbSize=sizeof(WNDCLASSEX);
		wndClassEx.style=CS_HREDRAW|CS_VREDRAW;
		wndClassEx.lpfnWndProc=::DefWindowProc;
		wndClassEx.cbClsExtra=0;
		wndClassEx.cbWndExtra=0;
		wndClassEx.hInstance=AfxGetInstanceHandle();
		wndClassEx.hIcon=0;
		wndClassEx.hCursor=::LoadCursor(NULL,IDC_ARROW);
		wndClassEx.hbrBackground=CreateSolidBrush(G_BKGND);
		wndClassEx.lpszMenuName=0;
		wndClassEx.lpszClassName=GRID_CTRL_CLASS;
		wndClassEx.hIconSm=0;

		if(!::RegisterClassEx(&wndClassEx))AfxThrowResourceException();
	}

	m_brGHeader.CreateSolidBrush(G_GHEAD_CLR);
	m_brIHeader.CreateSolidBrush(G_IHEAD_CLR);
}
CGridCtrl::~CGridCtrl(){
}

BEGIN_MESSAGE_MAP(CGridCtrl,CWnd)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

bool CGridCtrl::Create(DWORD dwStyle,RECT& rct,CWnd* pParent,UINT nID){
	m_dwStyle=dwStyle;
	m_rct=rct;

	if(m_dwStyle&GS_AUTOVSIZE)m_rct.bottom=m_rct.top;
	
	if(!CWnd::CreateEx(WS_EX_CONTROLPARENT,GRID_CTRL_CLASS,0,WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,m_rct,pParent,nID))return false;

	return true;
}

void CGridCtrl::Recalc(){
	GetClientRect(&m_rct);
	m_rct.bottom=m_rct.top;

	_ThisObj::Recalc();

	if(m_dwStyle&GS_AUTOVSIZE){
		CRect rct;
		GetWindowRect(&rct);

		GetParent()->ScreenToClient(&rct);
		rct.bottom=rct.top+m_rct.bottom;

		MoveWindow(&rct);

	}else Invalidate();
}

void CGridCtrl::PreSubclassWindow(){

	m_pGridMgr=new _GridMgr(this,*static_cast<_ThisObj*>(this));

	CWnd::PreSubclassWindow();
}
void CGridCtrl::OnDestroy(){

	delete m_pGridMgr;

	CWnd::OnDestroy();
}
HBRUSH CGridCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor){
	HBRUSH hbr=CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkMode(TRANSPARENT);

	UINT nID(pWnd->GetDlgCtrlID());

	switch(nCtlColor){
		case CTLCOLOR_STATIC:
			if(nID==GI_GHEAD_ID)hbr=m_brGHeader;
			else if(nID==GI_IHEAD_ID)hbr=m_brIHeader;
			break;
	}
	return hbr;
}
void CGridCtrl::OnSize(UINT nType, int cx, int cy){
	CWnd::OnSize(nType,cx,cy);
	Recalc();
}
void CGridCtrl::OnMouseMove(UINT nFlags, CPoint point){
	__super::OnMouseMove(nFlags, point);
	
	if(m_bMoveSprt){
		point.x-=GITEM_X_SEP/2-1;
		int nXLen(m_pHitCol->m_rct.right-m_pHitCol->m_rct.left);
		int nXPoint(point.x-m_pHitCol->m_rct.left);

		m_pHitCol->m_nXSprtPercent=int(double(nXPoint)/(double(nXLen)/100.));

		if(m_pHitCol->m_nXSprtPercent<15)m_pHitCol->m_nXSprtPercent=15;
		else if(m_pHitCol->m_nXSprtPercent>85)m_pHitCol->m_nXSprtPercent=85;
		
		m_pHitCol->Recalc();

		return;
	}

	m_pHitCol=0;

	_ThisObj::ObjItr itrHdrRow(m_ObjCnt.begin());

	while(itrHdrRow!=m_ObjCnt.end()){
		CRect rct((*itrHdrRow)->m_rct);

		if(rct.PtInRect(point)){
		
			SRowImpl<SHdr>::ObjItr itrHdr((*itrHdrRow)->m_ObjCnt.begin());

			while(itrHdr!=(*itrHdrRow)->m_ObjCnt.end()){
				CRect rct((*itrHdr)->m_rct);
				if(rct.PtInRect(point)){

					SHdr::ObjItr itrItemCol((*itrHdr)->m_ObjCnt.begin());

					while(itrItemCol!=(*itrHdr)->m_ObjCnt.end()){
						CRect rct((*itrItemCol)->m_rct);
						if(point.x-(*itrItemCol)->m_rct.left>=(*itrItemCol)->m_nXSprtPixel&&point.x-(*itrItemCol)->m_rct.left<=(*itrItemCol)->m_nXSprtPixel+GITEM_X_SEP&&
							point.y>(*itrItemCol)->m_rct.top&&point.y<(*itrItemCol)->m_rct.bottom){
							m_pHitCol=*itrItemCol;

							SetCapture();
							SetCursor(::LoadCursor(0,IDC_SIZEWE));
							
							return;
						}
						itrItemCol++;					
					}
				}
				itrHdr++;
			}
		}
		itrHdrRow++;
	}
	ReleaseCapture();
}
void CGridCtrl::OnLButtonDown(UINT nFlags, CPoint point){
	if(m_pHitCol)m_bMoveSprt=true;
	__super::OnLButtonDown(nFlags, point);
}

void CGridCtrl::OnLButtonUp(UINT nFlags, CPoint point){
	m_bMoveSprt=false;
	__super::OnLButtonUp(nFlags, point);
}
BOOL CGridCtrl::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo){
	if(__super::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))return true;
    return GetOwner()->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}