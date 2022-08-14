#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// removeWordFavList dialog

class removeWordFavList : public CDialogEx
{
	DECLARE_DYNAMIC(removeWordFavList)

public:
	removeWordFavList(CWnd* pParent = nullptr);   // standard constructor
	virtual ~removeWordFavList();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CComboBox comboBox_type;
	CEdit idc_chosen;
public:
	afx_msg void OnBnClickedButtonChoose2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
protected:
	CListCtrl list_ctrl_def;
public:
	afx_msg void OnBnClickedButton1();
	vector<Word> list;
protected:
	CEdit idc_order;
};
