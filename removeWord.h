#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// removeWord dialog

class removeWord : public CDialogEx
{
	DECLARE_DYNAMIC(removeWord)

public:
	removeWord(CWnd* pParent = nullptr);   // standard constructor
	virtual ~removeWord();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedButtonChoose2();
	string keyword;
	vector<string> oldDef;
protected:
	CEdit idc_key;
public:
	CComboBox comboBox_type;
protected:
	CEdit idc_chosen;
	CListCtrl list_ctrl_def;
	CEdit idc_order;
};
