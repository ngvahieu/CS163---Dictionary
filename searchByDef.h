#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// searchByDef dialog

class searchByDef : public CDialogEx
{
	DECLARE_DYNAMIC(searchByDef)

public:
	searchByDef(CWnd* pParent = nullptr);   // standard constructor
	virtual ~searchByDef();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	CEdit idc_def;
	CButton btn_search;
	CComboBox comboBox_type;
	CEdit idc_chosen;
	CButton btn_choose;
public:
	CListCtrl list_ctrl_key;
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedButtonChoose();
	afx_msg void OnBnClickedCancel();
};
