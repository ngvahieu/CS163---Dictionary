#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// guessDef dialog

class guessDef : public CDialogEx
{
	DECLARE_DYNAMIC(guessDef)

public:
	guessDef(CWnd* pParent = nullptr);   // standard constructor
	virtual ~guessDef();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG11 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	Word randWord;
	vector<string> ans;
	int number_question = 0;
	int score = 0;
protected:
	CButton idc_play;
	CStatic idc_question;
	CStatic idc_score;
	BOOL rad_1;
	BOOL rad_2;
	BOOL rad_3;
	BOOL rad_4;
	CStatic idc_ans1;
	CStatic idc_ans2;
	CStatic idc_ans3;
	CStatic idc_ans4;
};
