#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// searchByKey dialog

class searchByKey : public CDialogEx
{
	DECLARE_DYNAMIC(searchByKey)

public:
	searchByKey(CWnd* pParent = nullptr);   // standard constructor
	virtual ~searchByKey();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	CEdit edt_key;
	CButton btn_search;
	CComboBox comboBox_type;
	CButton btn_choose;
	CEdit edt_chosen;
public:
	CListCtrl list_ctrl_def;
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedButtonChoose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	Node* pLastChar = nullptr;
	string keyWord;
	afx_msg void OnBnClickedButton1();
protected:
	CEdit idc_order;
};
