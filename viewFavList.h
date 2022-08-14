#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// viewFavList dialog

class viewFavList : public CDialogEx
{
	DECLARE_DYNAMIC(viewFavList)

public:
	viewFavList(CWnd* pParent = nullptr);   // standard constructor
	virtual ~viewFavList();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
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
protected:
	CListCtrl list_ctrl_def;
public:
	afx_msg void OnBnClickedCancel();
};
