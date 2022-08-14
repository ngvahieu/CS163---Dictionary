#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// addNewWord dialog

class addNewWord : public CDialogEx
{
	DECLARE_DYNAMIC(addNewWord)

public:
	addNewWord(CWnd* pParent = nullptr);   // standard constructor
	virtual ~addNewWord();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CEdit idc_key;
	CEdit idc_def;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CComboBox comboBox_type;
	afx_msg void OnBnClickedButtonChoose();
protected:
	CEdit idc_chosen;
};
