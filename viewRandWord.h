#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// viewRandWord dialog

class viewRandWord : public CDialogEx
{
	DECLARE_DYNAMIC(viewRandWord)

public:
	viewRandWord(CWnd* pParent = nullptr);   // standard constructor
	virtual ~viewRandWord();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG8 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
protected:
	CEdit idc_ranKey;
	CEdit ranDef;
public:
	CComboBox comboBox_type;
protected:
	CEdit idc_chosen;
public:
	afx_msg void OnBnClickedButtonChoose2();
};
