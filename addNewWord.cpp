// addNewWord.cpp : implementation file
//

#include "pch.h"
#include "dictionaryGUI.h"
#include "afxdialogex.h"
#include "addNewWord.h"


// addNewWord dialog

IMPLEMENT_DYNAMIC(addNewWord, CDialogEx)

addNewWord::addNewWord(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

addNewWord::~addNewWord()
{
}

void addNewWord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, idc_key);
	DDX_Control(pDX, IDC_EDIT2, idc_def);
	DDX_Control(pDX, IDC_COMBO_TYPE, comboBox_type);
	DDX_Control(pDX, IDC_EDIT_CHOSEN_TYPE, idc_chosen);
}


BEGIN_MESSAGE_MAP(addNewWord, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &addNewWord::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &addNewWord::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE, &addNewWord::OnBnClickedButtonChoose)
END_MESSAGE_MAP()


// addNewWord message handlers


void addNewWord::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
	CdictionaryGUIDlg mainMenu;
	mainMenu.DoModal();
}


void addNewWord::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString check;
	GetDlgItemText(IDC_EDIT_CHOSEN_TYPE, check);
	if(check.GetLength() < 1) AfxMessageBox(_T("Choose the type of dictionary !"));
	else {
		CString key;
		GetDlgItemText(IDC_EDIT1, key);
		CT2CA pszConvertedAnsiString1(key);
		string k(pszConvertedAnsiString1);
		CString def;
		GetDlgItemText(IDC_EDIT2, def);
		CT2CA pszConvertedAnsiString2(def);
		string d(pszConvertedAnsiString2);
		Word newWord;
		newWord.key = k; newWord.def = d;
		if (!dict.addNewWord(newWord, dict, type)) {
			MessageBox(_T("The new word already existed !"));
		}
		else {
			MessageBox(_T("The new word is added successfully !"));
		}
	}
	
}


void addNewWord::OnBnClickedButtonChoose()
{
	// TODO: Add your control notification handler code here
	int comboBox1SelectedItem = comboBox_type.GetCurSel();
	CString str;
	if (comboBox1SelectedItem != LB_ERR) {
		comboBox_type.GetLBText(comboBox1SelectedItem, str);
	}
	if (str == _T("Emotional")) type = 0;
	if (str == _T("Slang")) type = 1;
	if (str == _T("English to English")) type = 2;
	if (str == _T("English to Vietnamese")) type = 3;
	if (str == _T("Vietnamese to English")) type = 4;

	SetDlgItemText(IDC_EDIT_CHOSEN_TYPE, str);
}
