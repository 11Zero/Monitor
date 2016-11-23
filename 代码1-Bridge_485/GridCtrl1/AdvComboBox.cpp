/////////////////////////////////////////////////////////////////////////////
// AdvComboBox.cpp : implementation file
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
#include "AdvComboBox.h"

#include "GridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_COMBOEDIT 108

/////////////////////////////////////////////////////////////////////////////
// CAdvComboBox
IMPLEMENT_DYNAMIC(CAdvComboBox, CWnd) 

CAdvComboBox::CAdvComboBox( BOOL bInst )
:
	m_pDropWnd(0),
	m_bDropListVisible(0),
	m_bInst( bInst )
{
	RegisterWindowClass();
	m_pEdit = NULL;
	m_zDelta = 0;
	m_nCurSel = -1;
	m_bDropRectStored= false;
	m_bHasFocus = false;
	m_bHasSentFocus = false;
	m_bSelItem = false;
	m_bFirstPaint = true;
	m_nMinVisItems = 5;
	m_bCodeCreate = false;
	m_bAutoAppend = TRUE;
	m_bDropButtonHot = false;
	m_bTrackMouseLeave = false;
	m_nDefaultDropItems = -1;

	m_dwACBStyle = 0;
	m_dwACBStyle |= ACBS_STANDARD;

	CFont fnt;
	fnt.CreatePointFont(80,"Tahoma");

	LOGFONT lf;
	fnt.GetLogFont(&lf);

	lf.lfHeight-=1;

	m_pFont=new CFont;
	m_pFont->CreateFontIndirect(&lf);
}



CAdvComboBox::~CAdvComboBox()
{
	delete m_pFont;
	if( m_pDropWnd )
	{
		m_pDropWnd->ShowWindow( SW_HIDE );
		m_bDropListVisible = FALSE;
		m_pDropWnd->DestroyWindow();
		delete m_pDropWnd;
		m_pDropWnd = NULL;
	}
	if( m_pEdit )
	{
		m_pEdit->DestroyWindow();
		delete m_pEdit;
	}
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CAdvComboBox, CWnd)
	//{{AFX_MSG_MAP(CAdvComboBox)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SHOWWINDOW()
	ON_WM_ENABLE()
	ON_WM_CHILDACTIVATE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_SELECTED_ITEM, OnSelectedItem )
	ON_MESSAGE( WM_ON_DROPDOWN_BUTTON, OnDropdownButton )
	ON_MESSAGE( WM_DESTROY_DROPLIST, OnDestroyDropdownList )
	ON_EN_KILLFOCUS(IDC_COMBOEDIT, OnKillfocusEdit)
	ON_EN_SETFOCUS(IDC_COMBOEDIT, OnSetfocusEdit)
	ON_EN_CHANGE(IDC_COMBOEDIT, OnChangeEdit)
	ON_EN_UPDATE(IDC_COMBOEDIT, OnUpdateEdit)

	ON_MESSAGE( CB_ADDSTRING, OnAddString )
	ON_MESSAGE( CB_SETCURSEL, OnSetCurSel )
	ON_MESSAGE( CB_GETCURSEL, OnGetCurSel )
	ON_MESSAGE( CB_SELECTSTRING, OnSelectString )
	ON_MESSAGE( CB_GETCOUNT, OnGetCount )
	ON_MESSAGE( CB_RESETCONTENT, OnResetContent )
	ON_MESSAGE( CB_GETLBTEXT, OnGetLBText )
	ON_MESSAGE( CB_GETLBTEXTLEN, OnGetLBTextLen )
	ON_MESSAGE( CB_GETTOPINDEX, OnGetTopIndex )
	ON_MESSAGE( CB_SETTOPINDEX, OnSetTopIndex )

END_MESSAGE_MAP()


void CAdvComboBox::SetFont(CFont* pFont){
	LOGFONT lf;
	pFont->GetLogFont(&lf);

	m_pFont->DeleteObject();
	m_pFont->CreateFontIndirect(&lf);

	CWnd::SetFont(m_pFont);
}

/////////////////////////////////////////////////////////////////////////////
// CAdvComboBox message handlers

LONG CAdvComboBox::OnAddString( WPARAM wParam, LPARAM lString )
{
	char* pStr = (char*)lString;
	return AddString( pStr );
}

LONG CAdvComboBox::OnSetCurSel( WPARAM wIndex, LPARAM lParam )
{
	int nIndex = (int)wIndex;
	return SetCurSel( nIndex );
}

LONG CAdvComboBox::OnGetCurSel( WPARAM wParam, LPARAM lParam )
{
	return GetCurSel();
}

LONG CAdvComboBox::OnSelectString( WPARAM wItemStart, LPARAM lString )
{
	int nItem = (int)wItemStart;
	char* pStr = (char*)lString;
	int nIndex = FindStringExact( nItem, pStr );
	return SetCurSel( nIndex );
}

LONG CAdvComboBox::OnGetCount( WPARAM wParam, LPARAM lParam )
{
	return GetCount();
}

LONG CAdvComboBox::OnResetContent( WPARAM wParam, LPARAM lParam )
{
	m_list.clear();
	m_strEdit = "";
	m_nCurSel = -1;
	SetWindowText( "" );
	if( m_pEdit )
	{
		m_pEdit->SetWindowText( "" );
	}
	Invalidate();
	return CB_OKAY;
}

LONG CAdvComboBox::OnGetLBText( WPARAM wIndex, LPARAM lString )
{
	int nIndex = (int)wIndex;
	char* pOutStr = (char*)lString;
	return GetLBText( nIndex, pOutStr );
}


LONG CAdvComboBox::OnGetLBTextLen( WPARAM wIndex, LPARAM lParam )
{
	int nIndex = (int)wIndex;
	return GetLBTextLen( nIndex );
}

LONG CAdvComboBox::OnGetTopIndex( WPARAM wParam, LPARAM lParam )
{
	return GetTopIndex();
}

LONG CAdvComboBox::OnSetTopIndex( WPARAM wIndex, LPARAM lParam )
{
	return SetTopIndex((int)wIndex);
}


BOOL CAdvComboBox::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst;
	hInst = AfxGetInstanceHandle();

	ASSERT( hInst != 0 );

    if( !(::GetClassInfo(hInst, ADVCOMBOBOXCTRL_CLASSNAME, &wndcls)) )
    {
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = 0;
		wndcls.cbWndExtra		= 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = (HBRUSH) (COLOR_WINDOW);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = ADVCOMBOBOXCTRL_CLASSNAME;

        if( !AfxRegisterClass(&wndcls) )
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }
    return TRUE;
}



BOOL CAdvComboBox::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
{
	m_rcCombo = rect;
	m_bCodeCreate = true;

	m_dwACBStyle |= ACBS_FLAT;
	m_dwStyle = dwStyle;

	LoadString( nID );
	
	return CWnd::Create(NULL, "", dwStyle, m_rcCombo, pParentWnd, nID );
}

void CAdvComboBox::LoadString( UINT nStringID )
{
	UINT nIDS;
	if( nStringID )
		nIDS = nStringID;
	else
	{
		nIDS = GetWindowLong( GetSafeHwnd(), GWL_ID );
	}

	//
	// Load string from resources
	CString strItems;
	if( !strItems.LoadString( nIDS ) )
	{
		return;
	}

	//
	// Clear the list
	m_list.clear();

	//
	// Go through the string and look after '\n'.
	char seps[] = "\n";
	char *token;
	int nLen = strItems.GetLength();
	char* szTok = new char[nLen+5];
	memset( szTok, 0, nLen+5 );
	strcpy( szTok, (LPCTSTR)strItems );

	token = strtok( szTok, seps );
	while( token != NULL )
	{
		AddString( token );
		token = strtok( NULL, seps );
	}


	//
	// Add item to list
}

int CAdvComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if(CWnd::OnCreate(lpCreateStruct)==-1)return -1;
	
	if((GetStyle()&CBS_DROPDOWN)&&!(GetStyle()&CBS_SIMPLE)){
		
		CRect rect;
		GetClientRect(rect);
		rect.right = rect.right - ::GetSystemMetrics(SM_CXHSCROLL);

		m_pEdit = new CGEdit;
		DWORD dwStyle = 0;
		dwStyle = WS_VISIBLE|WS_CHILD;
		if(GetStyle()&CBS_AUTOHSCROLL)dwStyle|=ES_AUTOHSCROLL;

		m_pEdit->Create(dwStyle,rect,this,IDC_COMBOEDIT);
		m_pEdit->SetFont(m_pFont);
		m_pEdit->SetWindowText(m_strEdit.c_str());
	}

	return 0;
}

void CAdvComboBox::PreSubclassWindow(){
}

void CAdvComboBox::OnChildActivate(){
	CWnd::OnChildActivate();
}

void CAdvComboBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if( m_nCurSel != -1 )
	{
		m_iter = m_list.begin();
		advance( m_iter, m_nCurSel );
		if( m_iter != m_list.end() )
		{
			m_strEdit = m_iter->strText;
		}
		if( m_bFirstPaint )
		{
			if( m_pEdit )
			{
				m_pEdit->SetWindowText( m_strEdit.c_str() );
				m_bFirstPaint = false;
				m_pEdit->EnableWindow( IsWindowEnabled() );
			}
		}
	}
	
	// TODO: Add your message handler code here
	CRect rect;
	CRect rcText;

	GetClientRect(rect);
	rcText = rect;
	rect.left = rect.right - ::GetSystemMetrics(SM_CXHSCROLL);
	rcText.right = rect.left-1;

	m_rcDropButton = rect;
	GetClientRect(rect);

	BOOL bWndEnabled = IsWindowEnabled();

	COLORREF clrDisabledBkg = G_EDIT_RDNL_CLR;//::GetSysColor(COLOR_BTNFACE);
	COLORREF clrDisabledBorder = ::GetSysColor(COLOR_3DDKSHADOW);
	COLORREF clrDisabledText = ::GetSysColor(COLOR_GRAYTEXT);

	if( !bWndEnabled )
	{
		if( 1 ) // Draw disabled flat control with border? Change to '0'.
		{
			dc.FillSolidRect( rect, clrDisabledBkg );
		}
		else
		{
			CBrush brDisabled(clrDisabledBkg);
			CBrush* pOldBrush = dc.SelectObject(&brDisabled);
			CPen penDisabled( PS_SOLID, 0, clrDisabledBorder);
			CPen* pOldPen = dc.SelectObject(&penDisabled);
			dc.Rectangle(rect);
			dc.SelectObject(pOldBrush);
			dc.SelectObject(pOldPen);
		}
	}
	else
	{
		COLORREF clrEnabledBkg = ::GetSysColor(COLOR_WINDOW);
		dc.FillSolidRect( rect, clrEnabledBkg );
	}


	DWORD dwBtnStyle = 0;
	if(!bWndEnabled )dwBtnStyle|=DFCS_INACTIVE;

	dwBtnStyle|=m_bDropListVisible?(DFCS_SCROLLDOWN|DFCS_PUSHED|DFCS_FLAT):(DFCS_SCROLLDOWN|DFCS_FLAT);


	if( m_dwACBStyle & ACBS_FLAT )dc.DrawFrameControl(m_rcDropButton, DFC_SCROLL, dwBtnStyle );
	else if( m_dwACBStyle & ACBS_STANDARD ){
		COLORREF clrTopLeft = ::GetSysColor(COLOR_3DSHADOW);
		COLORREF clrBottomRight = ::GetSysColor(COLOR_3DHILIGHT);
		dc.Draw3dRect( &rect, clrTopLeft, clrBottomRight );
		clrTopLeft = ::GetSysColor(COLOR_3DDKSHADOW);
		clrBottomRight = ::GetSysColor(COLOR_3DLIGHT);
		rect.DeflateRect(1,1);
		dc.Draw3dRect( &rect, clrTopLeft, clrBottomRight );
		m_rcDropButton.DeflateRect(0,2,0,2);
		m_rcDropButton.left -= 2;
		m_rcDropButton.right -= 2;
		dc.DrawFrameControl(m_rcDropButton, DFC_SCROLL, dwBtnStyle );
		rcText.DeflateRect(4,3,2,3);
	}


	if((GetStyle()&CBS_DROPDOWN)&&(GetStyle()&CBS_SIMPLE)){
		//
		// Draw Text as selected
		COLORREF clrBackground;
		COLORREF clrOldBkColor;
		COLORREF clrOldTextColor;
		clrBackground = ::GetSysColor(COLOR_HIGHLIGHT);
		clrOldBkColor = dc.SetBkColor( clrBackground );
	//	clrOldTextColor = dc.SetTextColor( ::GetSysColor(COLOR_HIGHLIGHTTEXT) );
		int nOldBkMode = dc.SetBkMode( TRANSPARENT );
		CFont* pOldFont = dc.SelectObject( m_pFont );
		if( m_bHasFocus && !m_bDropListVisible )
		{
			dc.FillSolidRect( rcText, bWndEnabled ? clrBackground : clrDisabledBkg );
			clrOldTextColor = dc.SetTextColor( bWndEnabled ? ::GetSysColor(COLOR_HIGHLIGHTTEXT) : clrDisabledText );
			rcText.left+=3;
			dc.DrawText( m_strEdit.c_str(), &rcText, DT_SINGLELINE|DT_VCENTER);
		}
		else
		{
			dc.FillSolidRect( rcText, bWndEnabled ? ::GetSysColor(COLOR_HIGHLIGHTTEXT) : clrDisabledBkg );
			clrOldTextColor = dc.SetTextColor( bWndEnabled ? ::GetSysColor(COLOR_BTNTEXT) : clrDisabledText );

			rcText.left+=3;
			dc.DrawText( m_strEdit.c_str(), &rcText, DT_SINGLELINE|DT_VCENTER);
		}

		dc.SelectObject( pOldFont );
		dc.SetBkMode( nOldBkMode );
	}
	else
	{
		//if( m_pEdit )
		//{
		//	m_pEdit->SetFont( m_pFont );
		//}
	}
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CAdvComboBox::OnEraseBkgnd(CDC* pDC) 
{
	return CWnd::OnEraseBkgnd(pDC);
//	return TRUE;	
}


int CAdvComboBox::SetItemHeight(int nIndex, int nHeight)
{
	if( nIndex == -1 )
	{
		if( nHeight < 10 || nHeight > 50 )
		{
			return CB_ERR;
		}
		else
		{
			//
			// Button rect
			GetClientRect(m_rcDropButton);
			m_rcDropButton.left = m_rcDropButton.right - ::GetSystemMetrics(SM_CXHSCROLL);

			return 0;
		}
	}
	return CB_ERR;
}

void CAdvComboBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( GetFocus() != this )
	{
		SetFocus();
	}

	//
	// Is mouse over drop button?
	if( (GetStyle() & CBS_DROPDOWN) && !(GetStyle() & CBS_SIMPLE) )	// == CBS_DROPDOWN
	{
		if( m_rcDropButton.PtInRect( point ) )
		{
			SendMessage( WM_ON_DROPDOWN_BUTTON );
			InvalidateRect( m_rcDropButton );
			Invalidate();
		}
	}
	else
	if( (GetStyle() & CBS_DROPDOWN) && (GetStyle() & CBS_SIMPLE) )	// == CBS_DROPDOWNLIST
	{
		CRect rc = m_rcCombo;
		GetClientRect( &rc );
		if( rc.PtInRect( point ) )
		{
			SendMessage( WM_ON_DROPDOWN_BUTTON );
			Invalidate();
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}


LONG CAdvComboBox::OnSelectedItem( WPARAM wParam, LPARAM lParam )
{
	list<LIST_ITEM> itemlist;
	list<LIST_ITEM>::iterator itemiter;

	int nPos = (int)wParam;
	itemlist = m_pDropWnd->GetList();
	itemiter = itemlist.begin();
	advance( itemiter, nPos );
	m_strEdit = itemiter->strText;

	m_nCurSel = FindStringExact( 0, m_strEdit.c_str() );

	SetWindowText( m_strEdit.c_str() );
	if( (GetStyle() & CBS_DROPDOWN) && !(GetStyle() & CBS_SIMPLE) )	// == CBS_DROPDOWN
	{
		if( m_pEdit )
		{
			m_pEdit->SetWindowText( m_strEdit.c_str() );
			m_pEdit->SetFocus();
			m_pEdit->SetSel( 0, -1, TRUE );
		}
	}
	// Send message to parent(dialog)
	m_bSelItem = true;
	int nId = GetDlgCtrlID();
	GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SELENDOK), (LPARAM)m_hWnd );

	Invalidate();
	OnDestroyDropdownList(0,0);

	//
	// See to it that the drop button is redrawn
	InvalidateRect( m_rcDropButton );

	GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SELCHANGE), (LPARAM)m_hWnd );

	return TRUE;
}

LONG CAdvComboBox::OnDropdownButton( WPARAM wParam, LPARAM lParam )
{
	//
	//
	if( !m_bDropListVisible )
	{
		//
		// Button is pressed
		//
		// Create list
		if( !m_pDropWnd )
		{
			CreateDropList( m_list );
		}
		m_pDropWnd->ShowWindow( SW_SHOW );
		m_bDropListVisible = TRUE;
	}
	else
	{
		OnDestroyDropdownList(0,0);
	}

	// Return TRUE if OK to go back, else return FALSE.
	return TRUE;
}


LONG CAdvComboBox::OnDestroyDropdownList( WPARAM wParam, LPARAM lParam )
{
	//
	// 
	if( m_pDropWnd )
	{
		m_pDropWnd->GetWindowRect( &m_rcDropWnd );
		m_bDropRectStored = true;
		m_pDropWnd->ShowWindow( SW_HIDE );
		m_bDropListVisible = FALSE;
		m_pDropWnd->DestroyWindow();
		delete m_pDropWnd;
		m_pDropWnd = NULL;

		Invalidate();
		int nId = GetDlgCtrlID();
		if( !m_bSelItem )
		{
			GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SELENDCANCEL), (LPARAM)m_hWnd );
		}
		else
		{
			m_bSelItem = false;
		}
		GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_CLOSEUP), (LPARAM)m_hWnd );
	}
	return TRUE;
}


void CAdvComboBox::CreateDropList( list<LIST_ITEM> &droplist)
{
	CRect rc;
	if( m_pDropWnd )
		ASSERT(0);
	m_pDropWnd = new CDropWnd( this, droplist, m_dwACBStyle );
	GetWindowRect( &rc );
	rc.top = rc.bottom ;

	// Get height by calc items in list times itemheight
	int nCount = (int)m_list.size();
	//
	// Get screen size
	CRect rcWorkArea;
	SystemParametersInfo( SPI_GETWORKAREA, 0, (LPRECT)rcWorkArea, 0) ;
	if( rc.bottom >= rcWorkArea.bottom )
	{
		rc.bottom = rcWorkArea.bottom;
	}
	else
	{
	}
	
	int nStyle = WS_CHILD|WS_BORDER|LBS_DISABLENOSCROLL|LBS_NOTIFY;
	m_pDropWnd->Create( nStyle , rc, 1 ? GetDesktopWindow() : this, 6 );
	m_pDropWnd->GetListBoxPtr()->SetCurSel( m_nCurSel );

	m_pDropWnd->SetFont( m_pFont );

	// Send message to parent(dialog)
	int nId = GetDlgCtrlID();
	GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_DROPDOWN), (LPARAM)m_hWnd );

}




int CAdvComboBox::GetLBText(int nIndex, LPTSTR lpszText)
{
	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	if( m_iter == m_list.end() || nIndex > (int)m_list.size() )
	{
		return CB_ERR;
	}

	strcpy( lpszText, m_iter->strText.c_str() );
	return (int)m_iter->strText.length()+1;
}

void CAdvComboBox::GetLBText(int nIndex, CString &rString)
{
	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	if( m_iter == m_list.end() || nIndex > (int)m_list.size() )
	{
		rString = "";
		return;
	}
	rString = m_iter->strText.c_str();
}

int CAdvComboBox::GetLBTextLen(int nIndex )
{
	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	if( m_iter == m_list.end() || nIndex > (int)m_list.size() )
	{
		return CB_ERR;
	}

	return (int)m_iter->strText.length()+1;
}

int CAdvComboBox::AddString(LPCTSTR lpszString)
{
	LIST_ITEM item;
	item.strText = lpszString;
	item.bChecked = false;
	item.bDisabled = false;
	item.vpItemData = NULL;
	m_list.push_back( item );
	if( GetStyle() & CBS_SORT )
	{
		m_list.sort();
		// Find new item
		return FindString( -1, item.strText.c_str() );
	}
	else
		return (int)m_list.size()-1;
}


int CAdvComboBox::GetText(LPTSTR lpszText)
{
	if( m_pEdit )
	{	
		CString str;
		m_pEdit->GetWindowText( str );
		strcpy( lpszText, (LPCTSTR)str );
		return str.GetLength();
	}
	else
	{
		strcpy( lpszText, m_strEdit.c_str() );
		return (int)m_strEdit.length();
	}
}

void CAdvComboBox::GetText(CString &rString)
{
	if( m_pEdit )
	{	
		m_pEdit->GetWindowText( rString );
	}
	else
	{
		rString = m_strEdit.c_str();
	}
}

void CAdvComboBox::SetText(LPCTSTR lpszText)
{
	if( m_pEdit )
	{	
		m_pEdit->SetWindowText( lpszText );
	}
	m_strEdit = lpszText;
}

BOOL CAdvComboBox::PointInWindow(CPoint ptScreenPoint)
{
	CRect rc;
	GetWindowRect( &rc );
	return rc.PtInRect( ptScreenPoint );
}



BOOL CAdvComboBox::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if( !m_bDropListVisible )
	{
		string str;
		//
		// Select another string from the map
		m_zDelta += zDelta;
		if( m_zDelta >= WHEEL_DELTA )
		{
			//
			// Select item upwards
			m_zDelta = 0;
			SelPrevItem();
		}
		else
		if( m_zDelta <= -WHEEL_DELTA )
		{
			//
			// Select item downwards
			m_zDelta = 0;
			SelNextItem();
		}
	}
	else
	{
		//
		// Handle mousewheel for the droplist here
		//
		// Select another string from the map
		m_zDelta += zDelta;
		if( m_zDelta >= WHEEL_DELTA )
		{
			//
			// Scroll list upwards
			m_zDelta = 0;
			int nTop = m_pDropWnd->GetListBoxPtr()->GetTopIndex();
			nTop -= 3;
			nTop = nTop < 0 ? 0 : nTop;
			m_pDropWnd->GetListBoxPtr()->SetTopIdx( nTop, TRUE );
		}
		else
		if( m_zDelta <= -WHEEL_DELTA )
		{
			//
			// Scroll list downwards
			m_zDelta = 0;
			int nTop = m_pDropWnd->GetListBoxPtr()->GetTopIndex();
			nTop += 3;
			nTop = nTop > m_pDropWnd->GetListBoxPtr()->GetCount() ? m_pDropWnd->GetListBoxPtr()->GetCount() : nTop;
			m_pDropWnd->GetListBoxPtr()->SetTopIdx( nTop, TRUE );
		}
	}
	return TRUE;
//	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CAdvComboBox::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
	if((GetStyle()&CBS_DROPDOWN)&&!(GetStyle()&CBS_SIMPLE)){
		CRect rect;
		GetClientRect(rect);
		rect.right = rect.right - ::GetSystemMetrics(SM_CXHSCROLL);
		m_pEdit->MoveWindow(&rect);
	}
}


void CAdvComboBox::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_bHasFocus = true;
	Invalidate();
//	OutputDebugString( "AdvComboBox got Focus.\n" );
	//
	// Set focus to the edit control? (CBS_DROPDOWN)
	if( (GetStyle() & CBS_DROPDOWN) && !(GetStyle() & CBS_SIMPLE) )	// == CBS_DROPDOWN
	{
		if( m_pEdit )
		{
			m_pEdit->SetFocus();
		}
	}
	BOOL bDropdownList = (GetStyle() & CBS_DROPDOWN) && (GetStyle() & CBS_SIMPLE);
	if( bDropdownList )
	{
		// Send message to parent(dialog)
		int nId = GetDlgCtrlID();
		GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SETFOCUS), (LPARAM)m_hWnd );
	}
}

void CAdvComboBox::OnSetfocusEdit() 
{
	m_bHasFocus = false;

	CWnd* pWnd = GetFocus();
	if( !m_bHasSentFocus )
	{
		// Send message to parent(dialog)
		int nId = GetDlgCtrlID();
		GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SETFOCUS), (LPARAM)m_hWnd );
		m_bHasSentFocus = true;
	}
}

void CAdvComboBox::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);

	// Needed for keydown's like 'Alt-C'("&Cancel" button)
	if( m_pDropWnd ) 
	{
		OnDestroyDropdownList(0,0);
	}
	m_bHasFocus = false;
	Invalidate();

	BOOL bDropdownList = (GetStyle() & CBS_DROPDOWN) && (GetStyle() & CBS_SIMPLE);
	if( bDropdownList && !m_pDropWnd )
	{
		// Send message to parent(dialog)
		int nId = GetDlgCtrlID();
		GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SELENDCANCEL), (LPARAM)m_hWnd );
		GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_KILLFOCUS), (LPARAM)m_hWnd );
	}

}

void CAdvComboBox::OnKillfocusEdit() 
{
	m_bHasFocus = false;
	Invalidate();

	CWnd* pWnd = GetFocus();
	if( !m_pDropWnd && pWnd != this )
	{
		// Send message to parent(dialog)
		int nId = GetDlgCtrlID();
		GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SELENDCANCEL), (LPARAM)m_hWnd );
		GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_KILLFOCUS), (LPARAM)m_hWnd );
		m_bHasSentFocus = false;
		m_pEdit->SetSel(0,0);
	}
}

void CAdvComboBox::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd::OnShowWindow(bShow, nStatus);
	
}

void CAdvComboBox::ModifyACBStyle(UINT nRemoveStyle, UINT nAddStyle)
{
	if( nAddStyle & ACBS_FLAT )
	{
		nRemoveStyle |= ACBS_STANDARD;
	}
	else
	if( nAddStyle & ACBS_STANDARD )
	{
		nRemoveStyle |= ACBS_FLAT;
	}
	m_dwACBStyle &= ~nRemoveStyle;
	m_dwACBStyle |= nAddStyle;
	Invalidate();
}

int CAdvComboBox::GetCount()
{
	return (int)m_list.size();
}

int CAdvComboBox::GetCurSel()
{
	CString str;
	GetText( str );
	return FindStringExact( -1, str );
}

int CAdvComboBox::SetCurSel(int nSelect)
{
	if( nSelect == -1 )
	{
		m_nCurSel = nSelect;
		m_strEdit = "";
		Invalidate();
		return CB_ERR;
	}
	else
	if( m_list.size() == 0 )
	{
		m_nCurSel = nSelect;
		return CB_ERR;
	}
	else
	if( nSelect < -1 || nSelect > (int)m_list.size()-1 )
	{
		return CB_ERR;
	}
	else
	{
		m_nCurSel = nSelect;
		m_iter = m_list.begin();
		advance( m_iter, nSelect );
		m_strEdit = m_iter->strText;
		Invalidate();
		return m_nCurSel;
	}
}

int CAdvComboBox::FindString(int nStartAfter, LPCTSTR lpszString)
{
	int nPos = 0;
	m_iter = m_list.begin();
	if( nStartAfter != -1 )
	{
		advance( m_iter, nStartAfter );
		nPos = nStartAfter;
	}
	for( m_iter; m_iter != m_list.end(); ++m_iter )
	{
		if( strncmp( m_iter->strText.c_str(), lpszString, strlen(lpszString) ) == 0 )
		{
			return nPos;
		}
		nPos++;
	}
	return CB_ERR;
}

int CAdvComboBox::FindStringExact(int nIndexStart, LPCTSTR lpszFind)
{
	if( nIndexStart > (int)m_list.size() && nIndexStart != -1 )
		return CB_ERR;

	int nPos = 0;
	m_iter = m_list.begin();
	if( nIndexStart != -1 )
	{
		advance( m_iter, nIndexStart );
		nPos = nIndexStart;
	}
	for( m_iter; m_iter != m_list.end(); ++m_iter )
	{
		if( strcmp( m_iter->strText.c_str(), lpszFind ) == 0 )
		{
			return nPos;
		}
		nPos++;
	}
	return CB_ERR;
}

int CAdvComboBox::SelectString(int nStartAfter, LPCTSTR lpszString)
{
	if( nStartAfter > (int)m_list.size() )
		return CB_ERR;

	int nPos = 0;
	m_iter = m_list.begin();
	if( nStartAfter != -1 )
	{
		advance( m_iter, nStartAfter );
		nPos = nStartAfter;
	}
	for( m_iter; m_iter != m_list.end(); ++m_iter )
	{
		if( strcmp( m_iter->strText.c_str(), lpszString ) == 0 )
		{
			m_nCurSel = nPos;
			m_strEdit = m_iter->strText;
			Invalidate();
			return nPos;
		}
		nPos++;
	}
	return CB_ERR;
}

int CAdvComboBox::SetItemData(int nIndex, DWORD dwItemData)
{
	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	if( m_iter == m_list.end() || nIndex > (int)m_list.size() )
	{
		return CB_ERR;
	}
	m_iter->vpItemData = (void*)dwItemData;
	return CB_OKAY;
}

DWORD CAdvComboBox::GetItemData(int nIndex)
{
	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	if( m_iter == m_list.end() || nIndex > (int)m_list.size() )
	{
		return CB_ERR;
	}
	return (DWORD)m_iter->vpItemData;
}

int CAdvComboBox::SetItemDataPtr(int nIndex, void *pData)
{
	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	if( m_iter == m_list.end() || nIndex > (int)m_list.size() )
	{
		return CB_ERR;
	}
	m_iter->vpItemData = pData;
	return CB_OKAY;
}

void* CAdvComboBox::GetItemDataPtr(int nIndex)
{
	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	if( m_iter == m_list.end() || nIndex > (int)m_list.size() )
	{
		return (void*)CB_ERR;
	}
	return m_iter->vpItemData;
}

void CAdvComboBox::ResetContent()
{
	m_list.clear();
	m_strEdit = "";
	Invalidate();
}



void AFXAPI DDX_ACBIndex( CDataExchange* pDX, int nIDC, int& index )
{
	HWND hWnd = pDX->PrepareCtrl( nIDC );
	if( pDX->m_bSaveAndValidate )
	{
		CAdvComboBox* pACB = (CAdvComboBox*)pDX->m_pDlgWnd->GetDlgItem( nIDC );
		index = pACB->GetCurSel();
	}
	else
	{
		CAdvComboBox* pACB = (CAdvComboBox*)pDX->m_pDlgWnd->GetDlgItem( nIDC );
		pACB->SetCurSel( index );
	}
}

void AFXAPI DDX_ACBString( CDataExchange* pDX, int nIDC, CString& value )
{
	HWND hWnd = pDX->PrepareCtrl( nIDC );
	if( pDX->m_bSaveAndValidate )
	{
		CAdvComboBox* pACB = (CAdvComboBox*)pDX->m_pDlgWnd->GetDlgItem( nIDC );
		pACB->GetText( value );
	}
	else
	{
		CAdvComboBox* pACB = (CAdvComboBox*)pDX->m_pDlgWnd->GetDlgItem( nIDC );
		pACB->SetText( value );
	}
}

BOOL CAdvComboBox::GetItemDisabled( int nIndex )
{
	if( nIndex > (int)m_list.size() )
		return CB_ERR;

	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	return m_iter->bDisabled;
}

void CAdvComboBox::SetItemDisabled(int nIndex, BOOL bDisabled)
{
	if( nIndex > (int)m_list.size() )
		return;

	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	m_iter->bDisabled = bDisabled;
}

BOOL CAdvComboBox::GetItemChecked( int nIndex )
{
	if( nIndex > (int)m_list.size() )
		return CB_ERR;

	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	return m_iter->bChecked;
}

void CAdvComboBox::SetItemChecked(int nIndex, BOOL bChecked)
{
	if( nIndex > (int)m_list.size() )
		return;

	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	m_iter->bChecked = bChecked;
}


BOOL CAdvComboBox::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN )
	{
		m_bAutoAppend = TRUE;

//		OutputDebugString( "Key was pressed(AdvComboBox)" );
		if( pMsg->wParam == VK_RETURN )
		{
//			OutputDebugString( "(RETURN)\n" );
			if( m_pDropWnd )
			{
				int nPos = m_pDropWnd->GetListBoxPtr()->GetCurSel();
				SendMessage( WM_SELECTED_ITEM, (WPARAM)nPos );
			}
			else
			{
				return CWnd::PreTranslateMessage(pMsg);
			}
		}
		else
		if( pMsg->wParam == VK_ESCAPE )
		{
//			OutputDebugString( "(ESCAPE)\n" );
			if( m_pDropWnd )
			{
				OnDestroyDropdownList(0,0);
				Invalidate();
			}else return CWnd::PreTranslateMessage(pMsg);
		}
		else
		if( pMsg->wParam == VK_F4 )
		{
//			OutputDebugString( "(F4)\n" );
			SendMessage( WM_ON_DROPDOWN_BUTTON );
			Invalidate();
		}
		else
		if( pMsg->wParam == VK_UP )
		{
//			OutputDebugString( "(VK_UP)\n" );
			SelPrevItem();
		}
		else
		if( pMsg->wParam == VK_DOWN )
		{
//			OutputDebugString( "(VK_DOWN)\n" );
			SelNextItem();
		}
		else
		if( pMsg->wParam == VK_DELETE || pMsg->wParam == VK_BACK )
		{
			m_bAutoAppend = FALSE;
			return CWnd::PreTranslateMessage(pMsg);
		}
		else
		if( pMsg->wParam == VK_RIGHT )
		{
			if( m_dwACBStyle & ACBS_AUTOAPPEND )
			{
				// If the cursor is at the end of the text, show autosuggest text
				if( m_pEdit )
				{
					int nS, nE;
					m_pEdit->GetSel( nS, nE );
					if( nS == nE && nS == m_pEdit->LineLength() )
					{
						OnUpdateEdit();
					}
					else
					{
						return CWnd::PreTranslateMessage(pMsg);
					}
				}
			}
			else
			{
				return CWnd::PreTranslateMessage(pMsg);
			}
		}
		else
		{
//			OutputDebugString( "<not handled>\n" );
			return CWnd::PreTranslateMessage(pMsg);
		}
		return TRUE;
	}
	else
	if( pMsg->message == WM_SYSKEYDOWN )
	{
		if( pMsg->wParam == VK_DOWN ||
			pMsg->wParam == VK_UP )
		{
//			OutputDebugString( "(ALT-VK_DOWN)\n" );
			SendMessage( WM_ON_DROPDOWN_BUTTON );
			Invalidate();
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}
void CAdvComboBox::SelPrevItem()
{
	if( m_pDropWnd )
	{
		int nPos = m_pDropWnd->GetListBoxPtr()->GetCurSel();
		if( nPos > 0 )
		{
			m_pDropWnd->GetListBoxPtr()->SetCurSel( --nPos );
		}
	}
	else
	{
		m_iter = m_list.begin();
		advance( m_iter, m_nCurSel );
		--m_iter;
		int nOldSel = m_nCurSel;
		int nPos = m_nCurSel;
		while( m_iter != m_list.end() )
		{
			nPos--;
			if( !m_iter->bDisabled )
			{
				m_strEdit = m_iter->strText;
				if( m_pEdit )
					m_pEdit->SetWindowText( m_strEdit.c_str() );
				m_nCurSel = nPos;
				Invalidate();
				break;
			}
			--m_iter;
		}
		if( nOldSel != m_nCurSel )
		{
			// Send message to parent(dialog)
			int nId = GetDlgCtrlID();
			GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SELENDOK), (LPARAM)m_hWnd );
			GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SELCHANGE), (LPARAM)m_hWnd );
		}
	}
}
void CAdvComboBox::SelNextItem()
{
	if( m_pDropWnd )
	{
		int nPos = m_pDropWnd->GetListBoxPtr()->GetCurSel();
		if( nPos < m_pDropWnd->GetListBoxPtr()->GetCount() )
		{
			m_pDropWnd->GetListBoxPtr()->SetCurSel( ++nPos );
		}
	}
	else
	{
		m_iter = m_list.begin();
		advance( m_iter, m_nCurSel );
		++m_iter;
		int nOldSel = m_nCurSel;
		int nPos = m_nCurSel;
		while( m_iter != m_list.end() )
		{
			nPos++;
			if( !m_iter->bDisabled )
			{
				m_strEdit = m_iter->strText;
				if( m_pEdit )
					m_pEdit->SetWindowText( m_strEdit.c_str() );
				Invalidate();
				m_nCurSel = nPos;
				break;
			}
			++m_iter;
		}
		if( nOldSel != m_nCurSel )
		{
			// Send message to parent(dialog)
			int nId = GetDlgCtrlID();
			GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SELENDOK), (LPARAM)m_hWnd );
			GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_SELCHANGE), (LPARAM)m_hWnd );
		}
	}
}
int CAdvComboBox::GetTopIndex()
{
	if( m_bDropListVisible )
	{
		if( m_pDropWnd )
		{
			return m_pDropWnd->GetListBoxPtr()->GetTopIndex();
		}
	}
	return CB_ERR;
}

int CAdvComboBox::SetTopIndex(int nIndex)
{
	if( m_bDropListVisible )
	{
		if( m_pDropWnd )
		{
			return m_pDropWnd->GetListBoxPtr()->SetTopIndex(nIndex);
		}
	}
	return CB_ERR;
}

//
// Will not allocate anything. I can't see the need in doing that.
// Everything is stored in a STL list.
int CAdvComboBox::InitStorage(int nItems, UINT nBytes)
{
	return nItems;
}


void CAdvComboBox::ShowDropDown(BOOL bShowIt)
{
	if( bShowIt )
	{
		if( !m_bDropListVisible )
		{
			SendMessage( WM_ON_DROPDOWN_BUTTON );
			Invalidate();
		}
	}
	else
	{
		if( m_bDropListVisible )
		{
			SendMessage( WM_DESTROY_DROPLIST );
			Invalidate();
		}
	}
}

void CAdvComboBox::GetDroppedControlRect(LPRECT lprect)
{
	if( m_bDropListVisible )
	{
		m_pDropWnd->GetWindowRect( lprect );
	}
}

BOOL CAdvComboBox::GetDroppedState()
{
	return m_bDropListVisible;
}

int CAdvComboBox::SetExtendedUI(BOOL bExtended)
{
	return CB_OKAY;
}

BOOL CAdvComboBox::GetExtendedUI()
{
	return FALSE;
}

int CAdvComboBox::DeleteString(UINT nIndex)
{
	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	if( m_iter != m_list.end() || nIndex > m_list.size() )
	{
		m_list.erase( m_iter );
		return (int)m_list.size();
	}
	else
	{
		return CB_ERR;
	}
}

int CAdvComboBox::InsertString(int nIndex, LPCTSTR lpszString)
{
	LIST_ITEM item;
	item.strText = lpszString;
	if( nIndex == -1 || (nIndex > (int)m_list.size()) )
	{
		m_list.push_back( item );
		return (int)m_list.size()-1;
	}

	if( nIndex == 0 && (m_list.size()==0) )
	{
		m_list.push_back( item );
		return 0;
	}

	m_iter = m_list.begin();
	advance( m_iter, nIndex );
	if( m_iter != m_list.end() )
	{
		m_iter = m_list.insert( m_iter, item );
		int nPos = 0;
		while( m_iter != m_list.begin() )
		{
			nPos++;
			--m_iter;
		}
		if( nIndex <= m_nCurSel )
		{
			m_nCurSel++;
		}
		return nPos;
	}
	return CB_ERR;
}




DWORD CAdvComboBox::GetEditSel()
{
	if( (GetStyle() & CBS_DROPDOWN) && !(GetStyle() & CBS_SIMPLE) )	// == CBS_DROPDOWN
	{
		if( m_pEdit )
		{
			return m_pEdit->GetSel();
		}
	}
	return CB_ERR;
}

BOOL CAdvComboBox::SetEditSel(int nStartChar, int nEndChar)
{
	if( (GetStyle() & CBS_DROPDOWN) && !(GetStyle() & CBS_SIMPLE) )	// == CBS_DROPDOWN
	{
		if( m_pEdit )
		{
			m_pEdit->SetSel( nStartChar, nEndChar, TRUE );
			return TRUE;
		}
	}
	return CB_ERR;
}


void CAdvComboBox::OnChangeEdit()
{
	if( !m_pDropWnd )
	{
		// Send message to parent(dialog)
		int nId = GetDlgCtrlID();
		GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_EDITCHANGE), (LPARAM)m_hWnd );
	}
}

void CAdvComboBox::OnUpdateEdit()
{
	static bool bAutoAppendInProgress;
	CString strEdit;
	m_pEdit->GetWindowText( strEdit );
	if( GetFocus() == m_pEdit )
	{
		if( !bAutoAppendInProgress )
		{
//			m_nCurSel = -1;
			if( m_dwACBStyle & ACBS_AUTOAPPEND && m_bAutoAppend )
			{
				string str = (LPCTSTR)strEdit;
				int nEditLen = (int)str.length();
				if( !nEditLen )
					return;
				int nStartSel;
				int nEndSel;

				m_pEdit->GetSel( nStartSel, nEndSel );

				LIST_ITEM item;
				m_iter = m_list.begin();
				while( m_iter != m_list.end() )
				{
					item = *m_iter;
					int nPos = (int)m_iter->strText.find( str, 0 );
					if( nPos == 0 )
					{
						bAutoAppendInProgress = true;
						m_pEdit->SetWindowText( m_iter->strText.c_str() );
						m_pEdit->SetSel( nEditLen, (int)m_iter->strText.length(), TRUE );
						bAutoAppendInProgress = false;
						break;
					}
					++m_iter;
				}
			}
		}

		if( !bAutoAppendInProgress )
		{
			if( m_dwACBStyle & ACBS_AUTOSUGGEST )
			{
				list<LIST_ITEM> suggestlist;
				list<LIST_ITEM>::iterator suggestiter;
				string str = (LPCTSTR)strEdit;
				int nEditLen = (int)str.length();
				if( !nEditLen )
				{
					if( m_pDropWnd )
						SendMessage( WM_DESTROY_DROPLIST );
					return;
				}
				int nStartSel;
				int nEndSel;

				m_pEdit->GetSel( nStartSel, nEndSel );

				LIST_ITEM item;
				m_iter = m_list.begin();
				while( m_iter != m_list.end() )
				{
					item = *m_iter;
					int nPos = (int)m_iter->strText.find( str, 0 );
					if( nPos == 0 )
					{
						suggestlist.push_back( item );
					}
					++m_iter;
				}
				if( m_pDropWnd )
					SendMessage( WM_DESTROY_DROPLIST );
				if( suggestlist.size() != 0 )
					CreateDropList( suggestlist );
			}
		}
	}

	if( !m_pDropWnd )
	{
		// Send message to parent(dialog)
		int nId = GetDlgCtrlID();
		GetParent()->SendMessage( WM_COMMAND, MAKEWPARAM(nId,CBN_EDITUPDATE), (LPARAM)m_hWnd );
	}
}






void CAdvComboBox::OnEnable(BOOL bEnable) 
{
	CWnd::OnEnable(bEnable);
	
	Invalidate();
	if( m_pEdit )
	{
		m_pEdit->EnableWindow( bEnable );
	}
	
}

BOOL CAdvComboBox::LimitText(int nMaxChars)
{
	if( m_pEdit )
	{
		int nCh = !nMaxChars ? 65535 : nMaxChars;
		m_pEdit->SetLimitText( nCh );
		return TRUE;
	}
	else
	{
		return CB_ERR;
	}
}

void CAdvComboBox::SetMinVisibleItems(int nMinItems)
{
	m_nMinVisItems = nMinItems;
}

int CAdvComboBox::GetMinVisibleItems()
{
	return m_nMinVisItems;
}

void CAdvComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	bool bChange = m_bDropButtonHot;

	if( (GetStyle() & CBS_DROPDOWN) && !(GetStyle() & CBS_SIMPLE) )  // == CBS_DROPDOWN
	{
		if( m_rcDropButton.PtInRect( point ) )
		{
			m_bDropButtonHot = true;
		}
		else
		{
			m_bDropButtonHot = false;
		}
	}
	else
	if( (GetStyle() & CBS_DROPDOWN) && (GetStyle() & CBS_SIMPLE) )  // == CBS_DROPDOWNLIST
	{
		GetClientRect( &m_rcCombo );
		if( m_rcCombo.PtInRect( point ) )
		{
			m_bDropButtonHot = true;
		}
		else
		{
			m_bDropButtonHot = false;
		}
	}


	if( bChange != m_bDropButtonHot )
	{
		if( !m_bTrackMouseLeave )
		{
			//
			// Could not use TrackMouseEvent() under Release. A bug appeared 
			// the second time the dropwindow was shown, and I did not 
			// have to strenght to go look for it. :)
/*			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = m_hWnd;
			TrackMouseEvent(&tme);*/

			m_bTrackMouseLeave = true;
			SetTimer(1, 50, NULL);
		}

		InvalidateRect( &m_rcDropButton );
	}

	CWnd::OnMouseMove(nFlags, point);

	/*RECT rct;
	GetWindowRect(&rct);

	CWnd* pWnd(GetParent());
	pWnd->ScreenToClient(&rct);

	point.Offset(rct.left,rct.top);

	pWnd->PostMessage(WM_MOUSEMOVE,(WPARAM)nFlags,LPARAM(point.y<<16|point.x));*/
}

void CAdvComboBox::OnMouseLeave() 
{
	// TODO: Add your message handler code here and/or call default
	bool bChange = m_bDropButtonHot;
	m_bDropButtonHot = false;
	m_bTrackMouseLeave = false;

	if( bChange != m_bDropButtonHot )
		InvalidateRect( &m_rcDropButton );
}


void CAdvComboBox::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if( nIDEvent == 1 )
	{
		CPoint point;
		GetCursorPos( &point );
		ScreenToClient( &point );
		if( (GetStyle() & CBS_DROPDOWN) && !(GetStyle() & CBS_SIMPLE) )  // == CBS_DROPDOWN
		{
			if( !m_rcDropButton.PtInRect( point ) )
			{
				KillTimer( 1 );
				OnMouseLeave();
			}
		}
		else
		if( (GetStyle() & CBS_DROPDOWN) && (GetStyle() & CBS_SIMPLE) )  // == CBS_DROPDOWNLIST
		{
			GetClientRect( &m_rcCombo );
			if( !m_rcCombo.PtInRect( point ) )
			{
				KillTimer( 1 );
				OnMouseLeave();
			}
		}

	}
	CWnd::OnTimer(nIDEvent);
}


int CAdvComboBox::GetDefaultVisibleItems()
{
	return m_nDefaultDropItems;
}

void CAdvComboBox::SetDefaultVisibleItems(int nItems)
{
	m_nDefaultDropItems = nItems;
}
