/////////////////////////////////////////////////////////////////////////////
// DropWnd.cpp : implementation file
// 
// CAdvComboBox Control
// Version: 2.1
// Date: September 2002
// Author: Mathias Tunared
// Email: Mathias@inorbit.com
// Copyright (c) 2002. All Rights Reserved.
//
// This code, in compiled form or as source code, may be redistributed 
// unmodified PROVIDING it is not sold for profit without the authors 
// written consent, and providing that this notice and the authors name 
// and all copyright notices remains intact.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DropWnd.h"

#include "AdvComboBox.h"
#include "DropListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropWnd

CDropWnd::CDropWnd( CWnd* pComboParent, list<LIST_ITEM> &itemlist, DWORD dwACBStyle )
:
	m_pComboParent( pComboParent ),
	m_list( itemlist ),
	m_dwACBStyle( dwACBStyle )
{
	m_bResizing = false;

	m_pListFont = new CFont;
	LOGFONT logFont;
	memset( &logFont, 0, sizeof(LOGFONT) );
	strcpy( logFont.lfFaceName, "MS Sans Serif" );
	logFont.lfHeight = 12;
	m_pListFont->CreateFontIndirect(&logFont);
}

CDropWnd::~CDropWnd()
{
	delete m_pListFont;
	delete m_scrollbar;
	delete m_listbox;
}


BEGIN_MESSAGE_MAP(CDropWnd, CWnd)
	//{{AFX_MSG_MAP(CDropWnd)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_SHOWWINDOW()
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_VRC_SETCAPTURE, OnSetCapture )
	ON_MESSAGE( WM_VRC_RELEASECAPTURE, OnReleaseCapture )
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDropWnd message handlers

BOOL CDropWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	//
	// Calc the size of the wnd
	
	return CWnd::PreCreateWindow(cs);
}

//BOOL CDropWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
BOOL CDropWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CWnd::Create(0, 0, dwStyle, rect, pParentWnd, nID, pContext);
}

int CDropWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CRect rcWnd;
	GetClientRect( &rcWnd );

	//
	// Because this window doesn't have an owner, there will appear 
	// a 'blank' button on the taskbar. The following are to hide 
	// that 'blank' button on the taskbar
	ModifyStyleEx( 0, WS_EX_TOOLWINDOW );
	SetWindowPos( &wndTopMost, lpCreateStruct->x, lpCreateStruct->y, lpCreateStruct->cx, lpCreateStruct->cy, SWP_SHOWWINDOW );

	//
	// Create scrollbar
	m_rcScroll = rcWnd;
	m_rcScroll.left = m_rcScroll.right - ::GetSystemMetrics(SM_CXVSCROLL);
	m_rcScroll.bottom -= ::GetSystemMetrics(SM_CYVSCROLL);
	m_scrollbar = new CDropScrollBar;
	VERIFY(m_scrollbar->Create( SBS_VERT | SBS_RIGHTALIGN | WS_CHILD, m_rcScroll, this, 100));

	//
	// Create listbox
	m_rcList.SetRect( lpCreateStruct->x, lpCreateStruct->y, lpCreateStruct->x+lpCreateStruct->cx-::GetSystemMetrics(SM_CXVSCROLL), lpCreateStruct->y+lpCreateStruct->cy );
	ScreenToClient( m_rcList );
	m_listbox = new CDropListBox(m_pComboParent, m_scrollbar);
	VERIFY(m_listbox->Create( /*WS_VISIBLE | */WS_CHILD | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED, m_rcList, this, 101 ) );
	m_listbox->SetDLBStyle( m_dwACBStyle );
	m_listbox->ShowWindow( SW_SHOW );


	//
	// Resize this wnd so INTEGRAL_HEIGHT applies!?
	CRect rc;
	int nH = m_listbox->GetItemHeight(0);
	nH = nH*(int)m_list.size()+2;
	// Get screen size
	int nScrX = GetSystemMetrics( SM_CXSCREEN );
	int nScrY = GetSystemMetrics( SM_CYSCREEN );

	int nDefaultItems = static_cast<CAdvComboBox*>(m_pComboParent)->GetDefaultVisibleItems();

	//
	// Check to see if the window should be placed over the combobox
	int nY = lpCreateStruct->y;
	int nItems = (int)m_list.size();
	int nItemHeight = m_listbox->GetItemHeight(0);
	int nVisHeight = nScrY - lpCreateStruct->y;
	if( (nVisHeight / nItemHeight) < static_cast<CAdvComboBox*>(m_pComboParent)->GetMinVisibleItems() )
	{
		CRect rcCombo;
		m_pComboParent->GetWindowRect( &rcCombo );
		int nComboTopY = lpCreateStruct->y - rcCombo.Height();
		if( nDefaultItems == -1 || nDefaultItems > nItems )
		{
			nY = (nComboTopY - nH) < 0 ? 0 : (nComboTopY - nH);
			nH = (nY + nH) > nComboTopY ? nComboTopY - nY : nH;
		}
		else
		{
			nY = nComboTopY - nItemHeight*nDefaultItems;
			nY -= 2;
			nY = nY < 0 ? 0 : nY;
			nH = nComboTopY - nY;
		}
	}
	else
	{
		//
		// Place the window below the combo
		// Check height
		if( nDefaultItems == -1 || nDefaultItems > nItems )
		{
			if( lpCreateStruct->y + nH > nScrY )
			{
				nH = nScrY - lpCreateStruct->y;
			}
			else
			if( nH < ::GetSystemMetrics(SM_CYVSCROLL) )
			{
				nH = ::GetSystemMetrics(SM_CYVSCROLL);
			}
		}
		else
		{
			nH = nDefaultItems * nItemHeight;
			nH = (nY+nH) > nScrY ? nScrY-nY : nH;
			nH += 2;
		}
	}

	// Calc width
	int nW = 0;
	CSize size(0,0);
	for( m_iter = m_list.begin(); m_iter != m_list.end(); ++m_iter )
	{
		m_listbox->GetTextSize( m_iter->strText.c_str(), (int)m_iter->strText.length(), size );
		nW = (size.cx > nW) ? size.cx : nW;
	}
	nW += m_rcScroll.Width() +8;
	// Check min width
	if( nW < m_rcList.Width() )
	{
		nW = lpCreateStruct->cx;
	}
	// Check max width
	int nX = lpCreateStruct->x;
	if( nW > nScrX - lpCreateStruct->x )
	{
		nX = nScrX - nW;
		if( nX < 0 )
			nX = 0;
	}
	if( nX == 0 && nW > nScrX )
		nW = nScrX;

	SetWindowPos( &wndTopMost, nX, nY, nW, nH, SWP_SHOWWINDOW|SWP_NOZORDER );

	GetClientRect( &rcWnd );

	//
	// Create sizehandle
	m_rcSizeHandle = rcWnd;
	GetClientRect( &m_rcSizeHandle );
	m_rcSizeHandle.left = m_rcSizeHandle.right - ::GetSystemMetrics(SM_CXVSCROLL);
	m_rcSizeHandle.top = m_rcSizeHandle.bottom - ::GetSystemMetrics(SM_CYVSCROLL);

	//
	// Add items to listbox
	LIST_ITEM item;
	for( m_iter = m_list.begin(); m_iter != m_list.end(); ++m_iter )
	{
		item = *m_iter;
		m_listbox->AddListItem( item );
	}

	//
	// Set values in scrollbar
	m_scrollbar->SetListBox( m_listbox );
	m_scrollbar->ShowScrollBar();
//	SendMessage( WM_SHOWWINDOW, (WPARAM)1, 0 );

	//
	//
	SetCapture();
	return 0;
}



LONG CDropWnd::OnSetCapture( WPARAM wParam, LPARAM lParam )
{
	SetCapture();
	return FALSE;
}

LONG CDropWnd::OnReleaseCapture( WPARAM wParam, LPARAM lParam )
{
	ReleaseCapture();
	return FALSE;
}


void CDropWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	//
	//
	if( m_bResizing )
	{
		CRect rcWnd;
		GetWindowRect( &rcWnd );
		if( point.x + m_nMouseDiffX >= ::GetSystemMetrics(SM_CXVSCROLL) )
		{
			rcWnd.right = rcWnd.left + point.x + m_nMouseDiffX +2;
		}
		else
		{
			rcWnd.right = rcWnd.left + ::GetSystemMetrics(SM_CXVSCROLL) +1;
		}

		if( point.y + m_nMouseDiffY >= ::GetSystemMetrics(SM_CYVSCROLL) )
		{
			rcWnd.bottom = rcWnd.top + point.y + m_nMouseDiffY +2;
		}
		else
		{
			rcWnd.bottom = rcWnd.top + ::GetSystemMetrics(SM_CXVSCROLL) +1;
		}
		MoveWindow( &rcWnd );
		return;
	}

	//
	// Check point
	if( m_rcList.PtInRect( point ) )
	{
		HCURSOR hCursor = LoadCursor( NULL, IDC_ARROW );
		SetCursor( hCursor );
		ReleaseCapture();
		m_scrollbar->SendMessage( WM_VRC_RELEASECAPTURE );
		m_listbox->SetFocus();
		m_listbox->SendMessage( WM_VRC_SETCAPTURE );
	}
	else
	if( m_rcScroll.PtInRect( point ) )
	{
		HCURSOR hCursor = LoadCursor( NULL, IDC_ARROW );
		SetCursor( hCursor );
		m_scrollbar->SetFocus();
		ReleaseCapture();
		m_listbox->SendMessage( WM_VRC_RELEASECAPTURE );
		m_scrollbar->SendMessage( WM_VRC_SETCAPTURE );
	}
	else
	{
		if( m_rcSizeHandle.PtInRect( point ) )
		{
			HCURSOR hCursor = LoadCursor( NULL, IDC_SIZENWSE );
			SetCursor( hCursor );
		}
		else
		{
			HCURSOR hCursor = LoadCursor( NULL, IDC_ARROW );
			SetCursor( hCursor );
		}
		SetCapture();
		CWnd::OnMouseMove(nFlags, point);
	}
}

void CDropWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( m_rcSizeHandle.PtInRect( point ) )
	{
		m_bResizing = true;
		m_ptLastResize = point;

		CRect rcClient;
		GetClientRect( &rcClient );
		m_nMouseDiffX = rcClient.Width() - point.x;
		m_nMouseDiffY = rcClient.Height() - point.y;
		return;
	}


//
// Clean up the code below...
//

	CRect rc;
	CRect rcVScroll(0,0,0,0);
	GetClientRect( &rc );
	DWORD dwStyle = GetStyle();
	
	// Take away vertical scroll

	if( rc.PtInRect( point ) )
	{
	}
	else
	{
		//
		// Calc the point in the parent(PropertyListBox)
		CWnd* pParent = m_pComboParent->GetParent();
		CRect rcParentClient;
		CRect rcParentWnd;
		pParent->GetClientRect( &rcParentClient );
		pParent->GetWindowRect( &rcParentWnd );

		CPoint pt = point;
		ClientToScreen( &pt );
			pt.x -= rcParentWnd.left;
			pt.y -= rcParentWnd.top;

		CAdvComboBox* pList = static_cast<CAdvComboBox*>(m_pComboParent);
		if( !pList->PointInWindow( pt ) )
		{
			
			ReleaseCapture();

//			CString str;
//			str.Format( "MousePos (NOT PtInRect): X:%d, y:%d\n", pt.x, pt.y );
//			OutputDebugString( str );
			m_pComboParent->PostMessage( WM_DESTROY_DROPLIST );
		}
		else
		{
//			CString str;
//			str.Format( "MousePos in combo\n " );
//			OutputDebugString( str );
			ReleaseCapture();
			m_pComboParent->PostMessage( WM_DESTROY_DROPLIST );
		}
		//
		// Send input to parent
/*		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.dx = pt.x;
		input.mi.dy = pt.y;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		input.mi.time = 0;
		SendInput( 1, &input, sizeof(INPUT) );
*/
	}

	
	CWnd::OnLButtonDown(nFlags, point);
}

void CDropWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( m_bResizing )
	{
		m_bResizing = false;
	}
	CWnd::OnLButtonUp(nFlags, point);
}




void CDropWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	m_rcList.SetRect( 0, 0, cx-::GetSystemMetrics(SM_CXVSCROLL), cy );
	m_listbox->MoveWindow( &m_rcList );

	m_rcScroll.SetRect( cx-::GetSystemMetrics(SM_CXVSCROLL), 0, cx, cy-::GetSystemMetrics(SM_CYVSCROLL) );
	m_scrollbar->MoveWindow( &m_rcScroll );

	m_rcSizeHandle.SetRect( cx-::GetSystemMetrics(SM_CXVSCROLL), cy-::GetSystemMetrics(SM_CYVSCROLL), cx, cy );
	InvalidateRect( &m_rcSizeHandle );

	//
	// Fix the scrollbar
	SCROLLINFO info;
	info.cbSize = sizeof(SCROLLINFO);
	if( m_scrollbar->GetScrollInfo( &info, SIF_ALL|SIF_DISABLENOSCROLL ) )
	{
		info.nPage = m_listbox->GetBottomIndex() - m_listbox->GetTopIndex();
		m_scrollbar->SetScrollInfo( &info );
	}

}

void CDropWnd::OnPaint() {
	CPaintDC dc(this);
	dc.DrawFrameControl(m_rcSizeHandle, DFC_SCROLL, DFCS_SCROLLSIZEGRIP );
}

BOOL CDropWnd::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ReleaseCapture();
	m_listbox->DestroyWindow();
	
	return CWnd::DestroyWindow();
}

void CDropWnd::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if( bShow )
	{
//		AnimateWindow( GetSafeHwnd(), 80, AW_VER_POSITIVE | AW_ACTIVATE | AW_SLIDE);
	}
	else
	{
//		AnimateWindow( GetSafeHwnd(), 80, AW_VER_NEGATIVE | AW_HIDE | AW_SLIDE);
	}
	
}


void CDropWnd::OnActivateApp(BOOL bActive, DWORD hTask) 
{
	CWnd::OnActivateApp(bActive, (HTASK)hTask);
	
	// TODO: Add your message handler code here
	if( bActive )
	{
	}
	else
	{
		m_pComboParent->PostMessage( WM_DESTROY_DROPLIST );
	}
	
}





