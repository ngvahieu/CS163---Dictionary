
// dictionaryGUIDlg.h : header file
//

#pragma once
#include "function.h"

extern Dictionary dict;
extern int type;

// CdictionaryGUIDlg dialog
class CdictionaryGUIDlg : public CDialogEx
{
// Construction
public:
	CdictionaryGUIDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DICTIONARYGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CComboBox combo_type;
	CButton btn_choose;
	CEdit edt_type;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
protected:
	BOOL rad_1;
	BOOL rad_2;
	BOOL rad_3;
	BOOL rad_4;
	BOOL rad_5;
	BOOL rad_6;
	BOOL rad_7;
	BOOL rad_8;
	BOOL rad_9;
	BOOL rad_10;
	BOOL rad_11;
	BOOL rad_12;
public:
	afx_msg void OnBnClickedRadio2();
};
