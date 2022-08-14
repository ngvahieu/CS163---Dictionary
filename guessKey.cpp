// guessKey.cpp : implementation file
//

#include "pch.h"
#include "dictionaryGUI.h"
#include "afxdialogex.h"
#include "guessKey.h"


// guessKey dialog

IMPLEMENT_DYNAMIC(guessKey, CDialogEx)

guessKey::guessKey(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG12, pParent)
	, rad_1(FALSE)
	, rad_2(FALSE)
	, rad_3(FALSE)
	, rad_4(FALSE)
{

}

guessKey::~guessKey()
{
}

void guessKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_QUES, idc_question);
	DDX_Check(pDX, IDC_RADIO1, rad_1);
	DDX_Check(pDX, IDC_RADIO2, rad_2);
	DDX_Check(pDX, IDC_RADIO13, rad_3);
	DDX_Check(pDX, IDC_RADIO14, rad_4);

	DDX_Control(pDX, IDC_ANS_1, idc_ans1);
	DDX_Control(pDX, IDC_ANS_2, idc_ans2);
	DDX_Control(pDX, IDC_ANS_3, idc_ans3);
	DDX_Control(pDX, IDC_ANS_4, idc_ans4);
	DDX_Control(pDX, IDC_SCORE, idc_score);
}


BEGIN_MESSAGE_MAP(guessKey, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &guessKey::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &guessKey::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &guessKey::OnBnClickedCancel)
END_MESSAGE_MAP()


// guessKey message handlers


void guessKey::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if (number_question) return;
	srand((int)time(0));
	type = rand() % 5;
	dict.guessWord(dict, type, randWord, ans);
	number_question++;

	CString key(randWord.def.c_str());
	CString ques;
	ques.Format(L"%d", number_question);
	idc_question.SetWindowText(ques + _T(".What is the keyword of '") + key + _T("':"));
	CString ans1(ans[0].c_str());
	idc_ans1.SetWindowText(_T("A. ") + ans1);
	CString ans2(ans[1].c_str());
	idc_ans2.SetWindowText(_T("B. ") + ans2);
	CString ans3(ans[2].c_str());
	idc_ans3.SetWindowText(_T("C. ") + ans3);
	CString ans4(ans[3].c_str());
	idc_ans4.SetWindowText(_T("D. ") + ans4);
}


void guessKey::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (number_question == 0 || number_question > 5) return;
	if (rad_1 == 1) {
		CString key;
		GetDlgItemText(IDC_ANS_1, key);
		CT2CA pszConvertedAnsiString(key);
		string d(pszConvertedAnsiString);
		d.erase(d.begin());
		d.erase(d.begin());
		d.erase(d.begin());
		if (d == randWord.key) {
			
			MessageBox(_T("TRUE !"));
			score++;
		}
		else {
			MessageBox(_T("FALSE !"));
		}
	}
	if (rad_2 == 1) {
		CString key;
		GetDlgItemText(IDC_ANS_2, key);
		CT2CA pszConvertedAnsiString(key);
		string d(pszConvertedAnsiString);
		d.erase(d.begin());
		d.erase(d.begin());
		d.erase(d.begin());
		if (d == randWord.key) {
			MessageBox(_T("TRUE !"));
			score++;
		}
		else {
			MessageBox(_T("FALSE !"));
		}
	}
	if (rad_3 == 1) {
		CString key;
		GetDlgItemText(IDC_ANS_3, key);
		CT2CA pszConvertedAnsiString(key);
		string d(pszConvertedAnsiString);
		d.erase(d.begin());
		d.erase(d.begin());
		d.erase(d.begin());
		if (d == randWord.key) {
			MessageBox(_T("TRUE !"));
			score++;
		}
		else {
			MessageBox(_T("FALSE !"));
		}
	}
	if (rad_4 == 1) {
		CString key;
		GetDlgItemText(IDC_ANS_4, key);
		CT2CA pszConvertedAnsiString(key);
		string d(pszConvertedAnsiString);
		d.erase(d.begin());
		d.erase(d.begin());
		d.erase(d.begin());
		if (d == randWord.key) {
			MessageBox(_T("TRUE !"));
			score++;
		}
		else {
			MessageBox(_T("FALSE !"));
		}
	}
	CString point;
	point.Format(L"%d", score);
	idc_score.SetWindowText(_T("Score: ") + point + _T("/5"));

	srand((int)time(0));
	type = rand() % 5;
	dict.guessWord(dict, type, randWord, ans);
	number_question++;

	if (number_question <= 5) {
		CString key(randWord.def.c_str());
		CString ques;
		ques.Format(L"%d", number_question);
		idc_question.SetWindowText(ques + _T(".What is the keyword of '") + key + _T("':"));
		CString ans1(ans[0].c_str());
		idc_ans1.SetWindowText(_T("A. ") + ans1);
		CString ans2(ans[1].c_str());
		idc_ans2.SetWindowText(_T("B. ") + ans2);
		CString ans3(ans[2].c_str());
		idc_ans3.SetWindowText(_T("C. ") + ans3);
		CString ans4(ans[3].c_str());
		idc_ans4.SetWindowText(_T("D. ") + ans4);
	}
	else {
		CString point;
		point.Format(L"%d", score);
		MessageBox(_T("YOUR SCORE: ") + point + _T("/5"));
	}
}


void guessKey::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
	CdictionaryGUIDlg mainMenu;
	mainMenu.DoModal();
}
