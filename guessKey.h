#pragma once
#include "afxdialogex.h"
#include "dictionaryGUIDlg.h"

// guessKey dialog

class guessKey : public CDialogEx
{
	DECLARE_DYNAMIC(guessKey)

public:
	guessKey(CWnd* pParent = nullptr);   // standard constructor
	virtual ~guessKey();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG12 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CStatic idc_question;
	BOOL rad_1;
	BOOL rad_2;
	BOOL rad_3;
	BOOL rad_4;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	Word randWord;
	vector<string> ans;
	int number_question = 0;
	int score = 0;
protected:
	CStatic idc_ans1;
	CStatic idc_ans2;
	CStatic idc_ans3;
	CStatic idc_ans4; 
	CStatic idc_score;
};
