#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// resetDict dialog

class resetDict : public CDialogEx
{
	DECLARE_DYNAMIC(resetDict)

public:
	resetDict(CWnd* pParent = nullptr);   // standard constructor
	virtual ~resetDict();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox comboBox_type;
protected:
	CEdit idc_chosen;
public:
	afx_msg void OnBnClickedButtonChoose2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
