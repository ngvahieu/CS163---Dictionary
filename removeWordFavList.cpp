// removeWordFavList.cpp : implementation file
//

#include "pch.h"
#include "dictionaryGUI.h"
#include "afxdialogex.h"
#include "removeWordFavList.h"


// removeWordFavList dialog

IMPLEMENT_DYNAMIC(removeWordFavList, CDialogEx)

removeWordFavList::removeWordFavList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG10, pParent)
{

}

removeWordFavList::~removeWordFavList()
{
}

void removeWordFavList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, comboBox_type);
	DDX_Control(pDX, IDC_EDIT_CHOSEN_TYPE, idc_chosen);
	DDX_Control(pDX, IDC_LIST1, list_ctrl_def);
	DDX_Control(pDX, IDC_EDIT2, idc_order);
}


BEGIN_MESSAGE_MAP(removeWordFavList, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE2, &removeWordFavList::OnBnClickedButtonChoose2)
	ON_BN_CLICKED(IDOK, &removeWordFavList::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &removeWordFavList::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &removeWordFavList::OnBnClickedButton1)
END_MESSAGE_MAP()


// removeWordFavList message handlers


void removeWordFavList::OnBnClickedButtonChoose2()
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
	list_ctrl_def.DeleteColumn(0);
	list_ctrl_def.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	list_ctrl_def.InsertColumn(0, _T("Definition"), LVCFMT_LEFT, 3000);
	list_ctrl_def.InsertColumn(0, _T("Keyword"), LVCFMT_LEFT, 100);
	list_ctrl_def.InsertColumn(0, _T("Number"), LVCFMT_LEFT, 100);
}


void removeWordFavList::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString check;
	GetDlgItemText(IDC_EDIT_CHOSEN_TYPE, check);
	if (check.GetLength() < 1) {
		AfxMessageBox(_T("Choose the type of dictionary !"));
	}
	else {
		string path;
		vector<Word> wordList;
		dict.viewFavWord(type, path, wordList);
		list = wordList;
		if (wordList.size() == 1) MessageBox(_T("The favourite list is empty !"));
		else {
			list_ctrl_def.DeleteAllItems();
			list_ctrl_def.DeleteColumn(0);
			list_ctrl_def.DeleteColumn(0);
			list_ctrl_def.DeleteColumn(0);
			list_ctrl_def.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			list_ctrl_def.InsertColumn(0, _T("Definition"), LVCFMT_LEFT, 3000);
			list_ctrl_def.InsertColumn(0, _T("Keyword"), LVCFMT_LEFT, 100);
			list_ctrl_def.InsertColumn(0, _T("Number"), LVCFMT_LEFT, 100);
			for (int i = 0; i < wordList.size() - 1; i++) {
				CString index;
				index.Format(_T("%d"), i + 1);
				list_ctrl_def.InsertItem(i, index);
				CString key(wordList[i].key.c_str());
				list_ctrl_def.SetItemText(i, 1, key);
				CString def(wordList[i].def.c_str());
				list_ctrl_def.SetItemText(i, 2, def);
			}
		}
	}
}

void removeWordFavList::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString check;
	GetDlgItemText(IDC_EDIT_CHOSEN_TYPE, check);
	if (check.GetLength() < 1) {
		AfxMessageBox(_T("Choose the type of dictionary !")); return;
	}
	GetDlgItemText(IDC_EDIT2, check);
	int ord = _tstof(check);
	if (check.GetLength() < 1) {
		AfxMessageBox(_T("Input the order !"));
	}
	else if (ord < 1 || ord > list.size() - 1) {
		AfxMessageBox(_T("Invalid order !"));
	}
	else {
		dict.removeFavWord(type, ord);
		MessageBox(_T("Removing successfully !"));
	}
}


void removeWordFavList::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
	CdictionaryGUIDlg mainMenu;
	mainMenu.DoModal();
}


