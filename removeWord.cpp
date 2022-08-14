// removeWord.cpp : implementation file
//

#include "pch.h"
#include "dictionaryGUI.h"
#include "afxdialogex.h"
#include "removeWord.h"


// removeWord dialog

IMPLEMENT_DYNAMIC(removeWord, CDialogEx)

removeWord::removeWord(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{

}

removeWord::~removeWord()
{
}

void removeWord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, idc_key);
	DDX_Control(pDX, IDC_COMBO_TYPE, comboBox_type);
	DDX_Control(pDX, IDC_EDIT_CHOSEN_TYPE, idc_chosen);
	DDX_Control(pDX, IDC_LIST2, list_ctrl_def);
	DDX_Control(pDX, IDC_EDIT2, idc_order);
}


BEGIN_MESSAGE_MAP(removeWord, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &removeWord::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDCANCEL, &removeWord::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SEARCH, &removeWord::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE2, &removeWord::OnBnClickedButtonChoose2)
END_MESSAGE_MAP()


// removeWord message handlers


void removeWord::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here

	CString order;
	idc_order.GetWindowText(order);
	int ord = _tstof(order);
	if (ord < 1 || ord > oldDef.size()) {
		AfxMessageBox(_T("Invalid order !"));
	}
	else {
		dict.removeWord(dict, type, keyword, ord);
		MessageBox(_T("Removing successfully !"));
	}
}


void removeWord::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
	CdictionaryGUIDlg mainMenu;
	mainMenu.DoModal();
}


void removeWord::OnBnClickedSearch()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString check;
	GetDlgItemText(IDC_EDIT_CHOSEN_TYPE, check);
	if (check.GetLength() < 1) AfxMessageBox(_T("Choose the type of dictionary !"));
	else {
		list_ctrl_def.DeleteAllItems();

		CString key;
		GetDlgItemText(IDC_EDIT1, key);
		CT2CA pszConvertedAnsiString(key);
		string k(pszConvertedAnsiString);
		Node* lastChar = dict.searchByKey(dict.tree[type], k);
		if (!lastChar || !lastChar->isLastChar) {
			MessageBox(_T("The keyword does not exist !"));
		}
		else {
			oldDef = lastChar->def;  keyword = k;
			for (int i = 0; i < lastChar->def.size(); i++) {
				CString index;
				index.Format(_T("%d"), i + 1);
				list_ctrl_def.InsertItem(i, index);
				CString def(lastChar->def[i].c_str());
				list_ctrl_def.SetItemText(i, 1, def);
			}
		}
	}
}


void removeWord::OnBnClickedButtonChoose2()
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
	list_ctrl_def.DeleteAllItems();
	list_ctrl_def.DeleteColumn(0);
	list_ctrl_def.DeleteColumn(0);
	list_ctrl_def.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	list_ctrl_def.InsertColumn(0, _T("Definition"), LVCFMT_LEFT, 3000);
	list_ctrl_def.InsertColumn(0, _T("Number"), LVCFMT_LEFT, 100);
}
