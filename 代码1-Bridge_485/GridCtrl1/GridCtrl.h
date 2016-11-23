#pragma once

#include "AdvComboBox.h"

#include <vector>
#include <deque>

#define G_BKGND			0xC9DBC8

#define G_GHEAD_CLR		0x9EC29B
#define G_IHEAD_CLR		0xACC2AB
#define G_EDIT_RDNL_CLR	0xE7EEE7

/////// Grid style ////////////////////
#define GS_AUTOVSIZE	0x01

/////// Layout style /////////
#define GLS_NR		0x000000
#define GLS_NC		0x010000
#define GIL_MASK	0xff0000

/////// Grid edit style //////////////
#define GES_PASS	0x1
#define GES_NUMB	0x2
#define GES_MASK	0xf

/////// Grid combo style /////////////
#define GCS_DRDNL	0x0
#define GCS_DRDN	0x1
#define GCS_MASK	0xf

/////// Grid custom style ////////////
#define GCSS_CSBT	0x0100
#define GCSS_MASK	0xff00

/////// Grid shared style ////////////
#define GSS_RDNL	0x10000000
#define GSS_MASK	0xff000000

///////////// Grid edit //////////////////////
class CGEdit : public CEdit{
	DECLARE_DYNAMIC(CGEdit)

public:
	CGEdit();
	virtual ~CGEdit();

	CBrush m_bkBrush;

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	BOOL SetReadOnly(bool bReadOnly=true);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnNcPaint();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};

//////////// Grid static //////////////////////
class CGStatic : public CStatic{
	DECLARE_DYNAMIC(CGStatic)

public:
	CGStatic();
	virtual ~CGStatic();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

/////////////////////

enum GI_TYPE{
	GI_HEADER,
	GI_EDIT,
	GI_COMBO
};

struct grid_item{
	const char* m_pcName;
	DWORD m_dwStyle;
	DWORD m_dwID;
	void* m_pvData;

	GI_TYPE m_giType;

	grid_item(const char* pcName,DWORD dwStyle,DWORD dwID,void* pvData,GI_TYPE giType):
	m_pcName(pcName),m_dwStyle(dwStyle),m_dwID(dwID),m_pvData(pvData),m_giType(giType){
	}
};

#ifndef GI_CONSTR_TYPE
#define GI_CONSTR_TYPE 0x01
#endif

struct gi_hdr:public grid_item{

#if GI_CONSTR_TYPE==0x00
	gi_hdr(const char* pcName=0,DWORD dwStyle=0,DWORD dwID=-1,void* pvData=0):grid_item(pcName,dwStyle,dwID,pvData,GI_HEADER){}

#else if GI_CONSTR_TYPE==0x01
	gi_hdr(const char* pcName=0,void* pvData=0,DWORD dwStyle=0,DWORD dwID=-1):grid_item(pcName,dwStyle,dwID,pvData,GI_HEADER){}

#endif

};

struct gi_edit:public grid_item{

#if GI_CONSTR_TYPE==0x00
	gi_edit(const char* pcName,DWORD dwStyle=0,DWORD dwID=-1,void* pvData=0):grid_item(pcName,dwStyle,dwID,pvData,GI_EDIT){}

#else if GI_CONSTR_TYPE==0x01
	gi_edit(const char* pcName,void* pvData=0,DWORD dwStyle=0,DWORD dwID=-1):grid_item(pcName,dwStyle,dwID,pvData,GI_EDIT){}

#endif

};

struct gi_combo:public grid_item{

#if GI_CONSTR_TYPE==0x00
	gi_combo(const char* pcName,DWORD dwStyle=0,DWORD dwID=-1,void* pvData=0):grid_item(pcName,dwStyle,dwID,pvData,GI_COMBO){}

#else if GI_CONSTR_TYPE==0x01
	gi_combo(const char* pcName,void* pvData=0,DWORD dwStyle=0,DWORD dwID=-1):grid_item(pcName,dwStyle,dwID,pvData,GI_COMBO){}

#endif

};

#define GI_GHEAD_ID	0xfffffffe
#define GI_IHEAD_ID	0xfffffffd

#define GITEM_HEIGHT	16
#define GITEM_X_SEP		2
#define GITEM_Y_SEP		1

#define GHDR_X_SEP		5
#define GHDR_Y_SEP		5

template<class THeader>
struct SGHeader{
	THeader* m_pHdr;

	const GI_TYPE m_giType;
	
	DWORD m_dwStyle;
	DWORD m_dwID;
	void* m_pvData;

	SGHeader(CWnd* pParent,grid_item& gi):
	m_pHdr(0),m_giType(gi.m_giType),m_dwStyle(gi.m_dwStyle),m_dwID(gi.m_dwID),m_pvData(gi.m_pvData){

		if(m_giType==GI_HEADER&&!gi.m_pcName)return;
		else{
			m_pHdr=new THeader;
			m_pHdr->Create(CString(" ")+gi.m_pcName,WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|SS_CENTERIMAGE|SS_ENDELLIPSIS,
				CRect(0,0,0,0),pParent,m_giType==GI_HEADER?GI_GHEAD_ID:GI_IHEAD_ID);
		}
	}
	virtual ~SGHeader(){
		delete m_pHdr;
	}
	void SetFont(CFont& rFont){
		if(m_pHdr)m_pHdr->SetFont(&rFont);
	}
	void SetName(const char* pcName){
		if(m_pHdr)m_pHdr->SetWindowText(pcName);
	}
	CString GetName(){
		CString strName;
		if(m_pHdr)m_pHdr->GetWindowText(strName);
		return strName;
	}
};

template<class TCombo>
class CSubItemMgr{
	TCombo* m_pCombo;

public:
	CSubItemMgr(TCombo* pCombo):m_pCombo(pCombo){}

public:
	void Insert(const char* pcText,LPARAM lData=-1,int nIndex=-1){m_pCombo->SetItemData(m_pCombo->InsertString(nIndex,pcText),(DWORD)lData);}

	void Delete(int nIndex=-1){
		if(nIndex==-1)m_pCombo->ResetContent();
		else m_pCombo->DeleteString(nIndex);
	}

	int Find(const char* pcText){
		return m_pCombo->FindString(-1,pcText);
	}
	int Find(LPARAM lData){
		const int nCount(Count);
		for(int i=0;i<nCount;i++)if(m_pCombo->GetItemData(i)==lData)return i;
		return -1;
	}

	__declspec(property(get=get_Count))int Count;
	int get_Count(){return m_pCombo->GetCount();}

	__declspec(property(put=put_Select,get=get_Select))int Select;
	void put_Select(int nIndex){m_pCombo->SetCurSel(nIndex);}
	int get_Select(){return m_pCombo->GetCurSel();}

	__declspec(property(get=get_Text))CString Text[];
	CString get_Text(){return m_pCombo->GetStyle()&CBS_DROPDOWNLIST?m_pCombo->GetLBText(Select):m_pCombo->GetText(Select);}
	CString get_Text(int nIndex){return m_pCombo->GetStyle()&CBS_DROPDOWNLIST?m_pCombo->GetLBText(nIndex):m_pCombo->GetText(nIndex);}

	__declspec(property(get=get_Data))LPARAM Data[];
	LPARAM get_Data(){return m_pCombo->GetItemData(Select);}
	LPARAM get_Data(int nIndex){return m_pCombo->GetItemData(nIndex);}
};

template<class THeader,class TEdit,class TCombo,class TCstmBtn=CButton>
struct SGItem:public SGHeader<THeader>{
	CWnd* m_pCtrl;
	TCstmBtn* m_pCstmBtn;

	CSubItemMgr<TCombo>* m_pSubItemMgr;

	SGItem(CWnd* pParent,grid_item& gi,const int& rnXSprt):SGHeader<THeader>(pParent,gi),m_rnXSprt(rnXSprt),m_pCstmBtn(0),m_pSubItemMgr(0){
		DWORD dwStyle(WS_VISIBLE|WS_CHILD|WS_TABSTOP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

		if((m_dwStyle&GCSS_MASK)==GCSS_CSBT){
			m_pCstmBtn=new TCstmBtn;
			m_pCstmBtn->Create("...",dwStyle,CRect(0,0,0,0),pParent,m_dwID);

			if((m_dwStyle&GSS_MASK)&GSS_RDNL)m_pCstmBtn->EnableWindow(0);
		}

		if(gi.m_giType==GI_EDIT){
			dwStyle|=ES_AUTOHSCROLL;

			if((m_dwStyle&GSS_MASK)&GSS_RDNL)dwStyle|=ES_READONLY;
			if((m_dwStyle&GES_MASK)&GES_NUMB)dwStyle|=ES_NUMBER;
			if((m_dwStyle&GES_MASK)&GES_PASS)dwStyle|=ES_PASSWORD;

			m_pCtrl=new TEdit;
			static_cast<TEdit*>(m_pCtrl)->Create(dwStyle,CRect(0,0,0,0),pParent,m_dwID);
		
		}else if(gi.m_giType==GI_COMBO){
			if((m_dwStyle&GCS_MASK)==GCS_DRDNL)dwStyle|=CBS_DROPDOWNLIST;
			else if((m_dwStyle&GCS_MASK)==GCS_DRDN)dwStyle|=CBS_DROPDOWN|CBS_AUTOHSCROLL;

			m_pCtrl=new TCombo;
			static_cast<TCombo*>(m_pCtrl)->Create(dwStyle,CRect(0,0,0,0),pParent,m_dwID);

			if((m_dwStyle&GSS_MASK)&GSS_RDNL)static_cast<TCombo*>(m_pCtrl)->EnableWindow(0);

			m_pSubItemMgr=new CSubItemMgr<TCombo>(static_cast<TCombo*>(m_pCtrl));

		}else ASSERT(false);
	}

	virtual ~SGItem(){		
		if(m_giType==GI_EDIT)delete static_cast<TEdit*>(m_pCtrl);
		else if(m_giType==GI_COMBO)delete static_cast<TCombo*>(m_pCtrl);

		delete m_pCstmBtn;
		delete m_pSubItemMgr;
	}

	const int& m_rnXSprt;
	RECT m_rct;

	virtual void Recalc(){
		m_rct.bottom=m_rct.top+GITEM_HEIGHT;

        m_pHdr->MoveWindow(CRect(m_rct.left,m_rct.top,m_rct.left+m_rnXSprt,m_rct.bottom));
		m_pHdr->Invalidate();

		m_pCtrl->MoveWindow(CRect(m_rct.left+m_rnXSprt+GITEM_X_SEP,m_rct.top,m_rct.right-(m_pCstmBtn?GITEM_HEIGHT:0),m_rct.bottom));

		if(m_pCstmBtn)m_pCstmBtn->MoveWindow(CRect(m_rct.right-GITEM_HEIGHT,m_rct.top,m_rct.right,m_rct.bottom));

		m_rct.bottom+=GITEM_Y_SEP;
	}
	void SetFont(CFont& rFont){
		SGHeader<THeader>::SetFont(rFont);
		m_pCtrl->SetFont(&rFont);
		if(m_pCstmBtn)m_pCstmBtn->SetFont(&rFont);
	}
	void SetText(const char* pcText){
		if(m_giType==GI_EDIT)static_cast<TEdit*>(m_pCtrl)->SetWindowText(pcText);
		else if(m_giType==GI_COMBO){
			if((m_dwStyle&GCS_MASK)==GCS_DRDNL)static_cast<TCombo*>(m_pCtrl)->SelectString(0,pcText);
			else 
				static_cast<TCombo*>(m_pCtrl)->SetText(pcText);
		}
	}
	CString GetText(){
		CString strText;
		if(m_giType==GI_EDIT)static_cast<TEdit*>(m_pCtrl)->GetWindowText(strText);
		else if(m_giType==GI_COMBO){
			if((m_dwStyle&GCS_MASK)==GCS_DRDNL)static_cast<TCombo*>(m_pCtrl)->GetLBText(static_cast<TCombo*>(m_pCtrl)->GetCurSel(),strText);
			else static_cast<TCombo*>(m_pCtrl)->GetText(strText);
		}
		return strText;
	}
	void SetReadOnly(bool bReadOnly){
		if(m_giType==GI_EDIT)static_cast<TEdit*>(m_pCtrl)->SetReadOnly(bReadOnly);
		else if(m_giType==GI_COMBO){
			static_cast<TCombo*>(m_pCtrl)->EnableWindow(!bReadOnly);
		}

		if(bReadOnly)m_dwStyle|=GSS_RDNL;
		else m_dwStyle&=(-1^GSS_RDNL);
	}
};

template<class TObj>
struct SObjImpl{
	RECT m_rct;
	std::deque<TObj*> m_ObjCnt;
	typedef class std::deque<TObj*>::iterator ObjItr;

	virtual ~SObjImpl(){
		ObjItr itr(m_ObjCnt.begin());
		while(itr!=m_ObjCnt.end())delete *itr++;
		m_ObjCnt.clear();
	}

	virtual void Recalc()=0;
};

template<class TObj>
struct SColImpl:public SObjImpl<TObj>{
	typedef struct SColImpl<TObj> _ThisObj;

	void Recalc(){
		m_rct.bottom=m_rct.top;

		for(ObjItr itr=m_ObjCnt.begin();itr!=m_ObjCnt.end();itr++){
			(*itr)->m_rct.top=m_rct.bottom;
			(*itr)->m_rct.left=m_rct.left;
			(*itr)->m_rct.right=m_rct.right;

			(*itr)->Recalc();

			if((*itr)->m_rct.bottom>m_rct.bottom)m_rct.bottom=(*itr)->m_rct.bottom;
		}
	}
};

template<class TObj>
struct SRowImpl:public SObjImpl<TObj>{
	typedef struct SRowImpl<TObj> _ThisObj;

	virtual void Recalc(){
		m_rct.bottom=m_rct.top;

		if(!m_ObjCnt.size())return;

		double dWidthObj(double(m_rct.right-m_rct.left+GHDR_X_SEP)/m_ObjCnt.size()-GHDR_X_SEP);
		double dXPos(m_rct.left);

		for(ObjItr itr=m_ObjCnt.begin();itr!=m_ObjCnt.end();itr++){
			(*itr)->m_rct.top=m_rct.top;
			(*itr)->m_rct.left=(int)dXPos;

			dXPos+=dWidthObj;

			(*itr)->m_rct.right=(long)dXPos;

			(*itr)->Recalc();

			if((*itr)->m_rct.bottom>m_rct.bottom)m_rct.bottom=(*itr)->m_rct.bottom;

			dXPos+=GHDR_X_SEP;
		}
	}
};

struct SItemCol:public SColImpl<SGItem<CGStatic,CGEdit,CAdvComboBox> >{
	int m_nXSprtPercent;
	int m_nXSprtPixel;

	virtual void Recalc(){
		m_nXSprtPixel=int(double(m_rct.right-m_rct.left)/100.*m_nXSprtPercent);

		_ThisObj::Recalc();

		m_rct.bottom+=GHDR_Y_SEP;
	}

	SItemCol():m_nXSprtPercent(50){
	}
};

struct SHdr:public SRowImpl<SItemCol>,public SGHeader<CGStatic>{
	SHdr(CWnd* pWnd,grid_item& gi):SGHeader<CGStatic>(pWnd,gi){
	}
	virtual void Recalc(){
		
		if(m_pHdr){
			m_rct.bottom=m_rct.top+GITEM_HEIGHT;
			m_pHdr->MoveWindow(&m_rct);

			m_rct.top=m_rct.bottom+=GITEM_Y_SEP;

		}else m_rct.top+=GHDR_Y_SEP;

		_ThisObj::Recalc();
	}
	void Attach(SHdr& rObjFrom){
		ObjItr itrFromHdr(rObjFrom.m_ObjCnt.begin());
		while(itrFromHdr!=rObjFrom.m_ObjCnt.end()){
			m_ObjCnt.push_back(*itrFromHdr);
			itrFromHdr=rObjFrom.m_ObjCnt.erase(itrFromHdr);
		}
	}
};

struct SFind{
	SColImpl<SRowImpl<SHdr> >::ObjItr m_itrHdrRow;
	SRowImpl<SHdr>::ObjItr m_itrHdr;
	SHdr::ObjItr m_itrItemCol;
	SItemCol::ObjItr m_itrItem;

	GI_TYPE m_giType;
	int m_nCurrPos;
};

/////// Item manager //////////////////
template<class TObj>
class CItemMgr{
	CWnd* m_pWnd;
	TObj& m_rObj;
	SFind& m_rFind;

	CFont m_fntGHeader;
	CFont m_fntIHeader;

public:
	bool Insert(grid_item& gi){
		
		if((gi.m_giType==GI_HEADER&&(gi.m_dwStyle&GIL_MASK)==GLS_NR)||!m_rObj.m_ObjCnt.size()){
			m_rFind.m_itrHdrRow=m_rObj.m_ObjCnt.insert(m_rFind.m_itrHdrRow,new SRowImpl<SHdr>());
			m_rFind.m_itrHdr=(*m_rFind.m_itrHdrRow)->m_ObjCnt.end();
		
		}else{
			if(m_rFind.m_itrHdrRow==m_rObj.m_ObjCnt.end())m_rFind.m_itrHdrRow--;
		}
		
		if((gi.m_giType==GI_HEADER&&(gi.m_dwStyle&GIL_MASK)==GLS_NC)||!(*m_rFind.m_itrHdrRow)->m_ObjCnt.size()){
			m_rFind.m_itrHdr=(*m_rFind.m_itrHdrRow)->m_ObjCnt.insert(m_rFind.m_itrHdr,new SHdr(m_pWnd,gi.m_giType==GI_HEADER?gi:gi_hdr(0)));

			(*m_rFind.m_itrHdr)->SetFont(m_fntGHeader);

			m_rFind.m_itrItemCol=(*m_rFind.m_itrHdr)->m_ObjCnt.end();

		}else if(m_rFind.m_itrHdr==(*m_rFind.m_itrHdrRow)->m_ObjCnt.end())m_rFind.m_itrHdr--;
		
		if(gi.m_giType!=GI_HEADER){

			if(m_rFind.m_giType==GI_HEADER)m_rFind.m_itrItemCol=(*m_rFind.m_itrHdr)->m_ObjCnt.end();

			if((gi.m_dwStyle&GIL_MASK)==GLS_NC||!(*m_rFind.m_itrHdr)->m_ObjCnt.size()){
				m_rFind.m_itrItemCol=(*m_rFind.m_itrHdr)->m_ObjCnt.insert(m_rFind.m_itrItemCol,new SItemCol());
				m_rFind.m_itrItem=(*m_rFind.m_itrItemCol)->m_ObjCnt.end();
			
			}else{
				if(m_rFind.m_itrItemCol==(*m_rFind.m_itrHdr)->m_ObjCnt.end())m_rFind.m_itrItemCol--;
				m_rFind.m_itrItem=(*m_rFind.m_itrItemCol)->m_ObjCnt.end();
			}

			m_rFind.m_itrItem=(*m_rFind.m_itrItemCol)->m_ObjCnt.insert(m_rFind.m_itrItem,new SGItem<CGStatic,CGEdit,CAdvComboBox>(m_pWnd,gi,(*m_rFind.m_itrItemCol)->m_nXSprtPixel));
			(*m_rFind.m_itrItem)->SetFont(m_fntIHeader);
		}

		m_rObj.Recalc();

		return true;
	}

	bool Delete(){

		if(m_rFind.m_nCurrPos==-1)return false;

		if(m_rFind.m_giType==GI_HEADER){
			if(m_rFind.m_itrHdr!=(*m_rFind.m_itrHdrRow)->m_ObjCnt.begin())(*(m_rFind.m_itrHdr-1))->Attach(**m_rFind.m_itrHdr);
			else if(m_rFind.m_itrHdrRow!=m_rObj.m_ObjCnt.begin())(*(m_rFind.m_itrHdrRow-1))->m_ObjCnt.back()->Attach(**m_rFind.m_itrHdr);

			delete *m_rFind.m_itrHdr;
			(*m_rFind.m_itrHdrRow)->m_ObjCnt.erase(m_rFind.m_itrHdr);

			if(!(*m_rFind.m_itrHdrRow)->m_ObjCnt.size()){
				delete *m_rFind.m_itrHdrRow;
				m_rObj.m_ObjCnt.erase(m_rFind.m_itrHdrRow);
			}
		}else{
			delete *m_rFind.m_itrItem;
			(*m_rFind.m_itrItemCol)->m_ObjCnt.erase(m_rFind.m_itrItem);

			if(!(*m_rFind.m_itrItemCol)->m_ObjCnt.size()){
				delete *m_rFind.m_itrItemCol;
				(*m_rFind.m_itrHdr)->m_ObjCnt.erase(m_rFind.m_itrItemCol);
			}
		}

		m_rObj.Recalc();
		return true;
	}

	__declspec(property(put=put_Name,get=get_Name))CString Name;
	void put_Name(CString strName){
		if(m_rFind.m_nCurrPos!=-1){
			if(m_rFind.m_giType==GI_HEADER){
				(*m_rFind.m_itrHdr)->SetName(strName);
			}else{
				(*m_rFind.m_itrItem)->SetName(strName);
			}
		}
	}
	CString get_Name(){
		if(m_rFind.m_nCurrPos!=-1){
			if(m_rFind.m_giType==GI_HEADER){
				return (*m_rFind.m_itrHdr)->GetName();
			}else{
				return (*m_rFind.m_itrItem)->GetName();
			}
		}
		return 0;
	}

	__declspec(property(put=put_Text,get=get_Text))CString Text;
	void put_Text(CString strText){
		if(m_rFind.m_nCurrPos!=-1)
			if(m_rFind.m_giType!=GI_HEADER)(*m_rFind.m_itrItem)->SetText(strText);
	}
	CString get_Text(){
		if(m_rFind.m_nCurrPos!=-1)
			if(m_rFind.m_giType!=GI_HEADER)return (*m_rFind.m_itrItem)->GetText();
		return 0;
	}

	__declspec(property(get=get_Type))GI_TYPE Type;
	GI_TYPE get_Type(){
		if(m_rFind.m_nCurrPos==-1)return GI_TYPE(-1);
		return m_rFind.m_giType;
	}

	__declspec(property(put=put_Data,get=get_Data))void* Data;
	void put_Data(void* pvData){
		if(m_rFind.m_nCurrPos!=-1){
			if(m_rFind.m_giType==GI_HEADER){
				(*m_rFind.m_itrHdr)->m_pvData=pvData;
			}else{
				(*m_rFind.m_itrItem)->m_pvData=pvData;
			}
		}
	}
	void* get_Data(){
		if(m_rFind.m_nCurrPos!=-1){
			if(m_rFind.m_giType==GI_HEADER){
				return (*m_rFind.m_itrHdr)->m_pvData;
			}else{
				return (*m_rFind.m_itrItem)->m_pvData;
			}
		}
		return (void*)-1;
	}

	__declspec(property(get=get_SubItem))CSubItemMgr<CAdvComboBox>* SubItem;
	CSubItemMgr<CAdvComboBox>* get_SubItem(){
		if(m_rFind.m_nCurrPos!=-1&&m_rFind.m_giType!=GI_HEADER)return (*m_rFind.m_itrItem)->m_pSubItemMgr;
		return 0;
	}

	__declspec(property(get=get_ID))int ID;
	int get_ID(){
		if(m_rFind.m_nCurrPos!=-1){
			if(m_rFind.m_giType==GI_HEADER)return (*m_rFind.m_itrHdr)->m_dwID;
			else return (*m_rFind.m_itrItem)->m_dwID;
		}
		return -1;
	}
	__declspec(property(get=get_Index))int Index;
	int get_Index(){return m_rFind.m_nCurrPos;}

	__declspec(property(get=get_Style))DWORD Style;
	DWORD get_Style(){
		if(m_rFind.m_nCurrPos!=-1){
			if(m_rFind.m_giType==GI_HEADER)return (*m_rFind.m_itrHdr)->m_dwStyle;
			else return (*m_rFind.m_itrItem)->m_dwStyle;
		}
		return 0;
	}

	__declspec(property(put=put_ReadOnly,get=get_ReadOnly))bool ReadOnly;
	void put_ReadOnly(bool bReadOnly){
		if(m_rFind.m_nCurrPos!=-1&&m_rFind.m_giType!=GI_HEADER)(*m_rFind.m_itrItem)->SetReadOnly(bReadOnly);
	}
	bool get_ReadOnly(){
		if(m_rFind.m_nCurrPos==-1||m_rFind.m_giType==GI_HEADER)return false;

		return (*m_rFind.m_itrItem)->m_dwStyle&GSS_RDNL;
	}
	
	void SetFocus(){
		if(m_rFind.m_nCurrPos!=-1&&m_rFind.m_giType!=GI_HEADER)static_cast<CWnd*>((*m_rFind.m_itrItem)->m_pCtrl)->SetFocus();
	}

	CItemMgr(CWnd* pWnd,TObj& rObj,SFind& rFind):
	m_pWnd(pWnd),m_rObj(rObj),m_rFind(rFind){

		CFont fntTmp;
		fntTmp.CreatePointFont(80,"Tahoma");

		LOGFONT lf;
		fntTmp.GetLogFont(&lf);

		lf.lfHeight-=1;

		m_fntIHeader.CreateFontIndirect(&lf);

		lf.lfWeight=FW_BOLD;

		m_fntGHeader.CreateFontIndirect(&lf);
	}
};

/////// Grid manager //////////////////
template<class TObj>
class CGridMgr{
	friend class CItemMgr<TObj>;

	CItemMgr<TObj> m_ItemMgr;

	CWnd* m_pWnd;
	TObj& m_rObj;
	SFind m_Find;

public:
	CGridMgr(CWnd* pWnd,TObj& rObj):m_pWnd(pWnd),m_rObj(rObj),m_ItemMgr(pWnd,rObj,m_Find){
	}

	__declspec(property(get=get_ID))CItemMgr<TObj>* ID[];
	CItemMgr<TObj>* get_ID(int nID){
		if(!Find(nID,false)&&nID!=-1)return 0;
		return &m_ItemMgr;
	}
	__declspec(property(get=get_Index))CItemMgr<TObj>* Index[];
	CItemMgr<TObj>* get_Index(int nIndex){
		if(!Find(nIndex,true)&&nIndex!=-1)return 0;
		return &m_ItemMgr;
	}
	void DeleteAll(){
		TObj::ObjItr itr(m_rObj.m_ObjCnt.begin());
		
		while(itr!=m_rObj.m_ObjCnt.end())delete *itr++;
		m_rObj.m_ObjCnt.clear();

		m_rObj.Recalc();
	}

	__declspec(property(put=put_ReadOnlyAll))bool ReadOnlyAll;
	void put_ReadOnlyAll(bool bReadOnly){
		const int nCount(Count);
		for(int i=0;i<nCount;i++)Index[i]->ReadOnly=bReadOnly;
	}

	__declspec(property(get=get_Count))DWORD Count;
	DWORD get_Count(){
		m_Find.m_nCurrPos=0;

		m_Find.m_itrHdrRow=m_rObj.m_ObjCnt.begin();
		while(m_Find.m_itrHdrRow!=m_rObj.m_ObjCnt.end()){
			m_Find.m_nCurrPos+=(DWORD)(*m_Find.m_itrHdrRow)->m_ObjCnt.size();

			m_Find.m_itrHdr=(*m_Find.m_itrHdrRow)->m_ObjCnt.begin();
			while(m_Find.m_itrHdr!=(*m_Find.m_itrHdrRow)->m_ObjCnt.end()){

				m_Find.m_itrItemCol=(*m_Find.m_itrHdr)->m_ObjCnt.begin();
				while(m_Find.m_itrItemCol!=(*m_Find.m_itrHdr)->m_ObjCnt.end())m_Find.m_nCurrPos+=(DWORD)(*m_Find.m_itrItemCol++)->m_ObjCnt.size();

				m_Find.m_itrHdr++;
			}
			m_Find.m_itrHdrRow++;
		}
		return m_Find.m_nCurrPos;
	}

protected:

	bool Find(DWORD dwItem,bool bByPos){
		m_Find.m_itrHdrRow=m_rObj.m_ObjCnt.begin();

		m_Find.m_nCurrPos=0;

		while(m_Find.m_itrHdrRow!=m_rObj.m_ObjCnt.end()){
			m_Find.m_itrHdr=(*m_Find.m_itrHdrRow)->m_ObjCnt.begin();

			while(m_Find.m_itrHdr!=(*m_Find.m_itrHdrRow)->m_ObjCnt.end()){
				
				m_Find.m_giType=GI_HEADER;

				if(bByPos){if(m_Find.m_nCurrPos==dwItem)return true;
				}else if((*m_Find.m_itrHdr)->m_dwID==dwItem)return true;

				m_Find.m_nCurrPos++;

				m_Find.m_itrItemCol=(*m_Find.m_itrHdr)->m_ObjCnt.begin();
				while(m_Find.m_itrItemCol!=(*m_Find.m_itrHdr)->m_ObjCnt.end()){
					m_Find.m_itrItem=(*m_Find.m_itrItemCol)->m_ObjCnt.begin();

					while(m_Find.m_itrItem!=(*m_Find.m_itrItemCol)->m_ObjCnt.end()){

						m_Find.m_giType=(*m_Find.m_itrItem)->m_giType;

						if(bByPos){if(m_Find.m_nCurrPos==dwItem)return true;
						}else if((*m_Find.m_itrItem)->m_dwID==dwItem)return true;

						m_Find.m_nCurrPos++;

						m_Find.m_itrItem++;
					}
					m_Find.m_itrItemCol++;					
				}
				m_Find.m_itrHdr++;
			}
			m_Find.m_itrHdrRow++;
		}

		m_Find.m_nCurrPos=-1;
		return false;
	}
};


/////// CGridCtrl /////////////////////
class CGridCtrl:public CWnd,protected SColImpl<SRowImpl<SHdr> >{

	CBrush m_brGHeader;
	CBrush m_brIHeader;

	typedef class CGridMgr<_ThisObj> _GridMgr;
	friend class _GridMgr;

	DWORD m_dwStyle;
	_GridMgr* m_pGridMgr;

	virtual void Recalc();

public:
	CGridCtrl();
	virtual ~CGridCtrl();

	bool Create(DWORD dwStyle,RECT& rct,CWnd* pParent,UINT nID=-1);

	_GridMgr* operator->(){return m_pGridMgr;}

	CGridCtrl& operator<<(grid_item& gi){

		ASSERT(m_pGridMgr);

		m_pGridMgr->Index[-1]->Insert(gi);
		return *this;
	}

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();

	SItemCol* m_pHitCol;
	bool m_bMoveSprt;

public:
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
};