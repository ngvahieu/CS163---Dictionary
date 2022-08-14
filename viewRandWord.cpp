// viewRandWord.cpp : implementation file
//

#include "pch.h"
#include "dictionaryGUI.h"
#include "afxdialogex.h"
#include "viewRandWord.h"


// viewRandWord dialog

IMPLEMENT_DYNAMIC(viewRandWord, CDialogEx)

viewRandWord::viewRandWord(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG8, pParent)
{

}

viewRandWord::~viewRandWord()
{
}

void viewRandWord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, idc_ranKey);
	DDX_Control(pDX, IDC_EDIT2, ranDef);
	DDX_Control(pDX, IDC_COMBO_TYPE, comboBox_type);
	DDX_Control(pDX, IDC_EDIT_CHOSEN_TYPE, idc_chosen);
}


BEGIN_MESSAGE_MAP(viewRandWord, CDialogEx)
	ON_BN_CLICKED(IDOK, &viewRandWord::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &viewRandWord::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE2, &viewRandWord::OnBnClickedButtonChoose2)
END_MESSAGE_MAP()


// viewRandWord message handlers


void viewRandWord::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString check;
	GetDlgItemText(IDC_EDIT_CHOSEN_TYPE, check);
	if (check.GetLength() < 1) AfxMessageBox(_T("Choose the type of dictionary !"));
	else {
		Word randWord = dict.findRanWord(dict, type);
		CString key(randWord.key.c_str());
		CString def(randWord.def.c_str());

		idc_ranKey.SetWindowTextW(key);
		ranDef.SetWindowTextW(def);
	}
}


void viewRandWord::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
	CdictionaryGUIDlg mainMenu;
	mainMenu.DoModal();
}


void viewRandWord::OnBnClickedButtonChoose2()
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
