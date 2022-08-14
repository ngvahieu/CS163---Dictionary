// resetDict.cpp : implementation file
//

#include "pch.h"
#include "dictionaryGUI.h"
#include "afxdialogex.h"
#include "resetDict.h"


// resetDict dialog

IMPLEMENT_DYNAMIC(resetDict, CDialogEx)

resetDict::resetDict(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{

}

resetDict::~resetDict()
{
}

void resetDict::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, comboBox_type);
	DDX_Control(pDX, IDC_EDIT_CHOSEN_TYPE, idc_chosen);
}


BEGIN_MESSAGE_MAP(resetDict, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE2, &resetDict::OnBnClickedButtonChoose2)
	ON_BN_CLICKED(IDOK, &resetDict::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &resetDict::OnBnClickedCancel)
END_MESSAGE_MAP()


// resetDict message handlers


void resetDict::OnBnClickedButtonChoose2()
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


void resetDict::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString check;
	GetDlgItemText(IDC_EDIT_CHOSEN_TYPE, check);
	if (check.GetLength() < 1) AfxMessageBox(_T("Choose the type of dictionary !"));
	else {
		dict.resetDictionary(dict, type);
		MessageBox(_T("Reset successfully !"));
	}
}


void resetDict::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
	CdictionaryGUIDlg mainMenu;
	mainMenu.DoModal();
}
