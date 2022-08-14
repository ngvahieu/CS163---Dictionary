#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// historyOfWord dialog

class historyOfWord : public CDialogEx
{
	DECLARE_DYNAMIC(historyOfWord)

public:
	historyOfWord(CWnd* pParent = nullptr);   // standard constructor
	virtual ~historyOfWord();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl list_ctrl_historyWord;
protected:
	CButton btn_show;
public:
	afx_msg void OnBnClickedButton1();
	Dictionary dict;
	int type = 0;
	afx_msg void OnBnClickedCancel();
};
