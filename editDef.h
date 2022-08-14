#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// editDef dialog

class editDef : public CDialogEx
{
	DECLARE_DYNAMIC(editDef)

public:
	editDef(CWnd* pParent = nullptr);   // standard constructor
	virtual ~editDef();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CEdit idc_key;
public:
	CComboBox comboBox_type;
protected:
	CEdit idc_chosen;
	CEdit idc_newDef;
public:
	afx_msg void OnBnClickedCancel();
protected:
	CListCtrl list_ctrl_def;
public:
	afx_msg void OnBnClickedSearch();
protected:
	CEdit idc_order;
public:
	afx_msg void OnBnClickedButtonOk();
	vector<string> oldDef;
	string keyword;
	afx_msg void OnBnClickedButtonChoose2();
};
