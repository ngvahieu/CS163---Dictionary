// searchByDef.cpp : implementation file
//

#include "pch.h"
#include "dictionaryGUI.h"
#include "afxdialogex.h"
#include "searchByDef.h"


// searchByDef dialog

IMPLEMENT_DYNAMIC(searchByDef, CDialogEx)

searchByDef::searchByDef(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

searchByDef::~searchByDef()
{
}

void searchByDef::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, idc_def);
	DDX_Control(pDX, IDC_SEARCH, btn_search);
	DDX_Control(pDX, IDC_COMBO_TYPE, comboBox_type);
	DDX_Control(pDX, IDC_EDIT_CHOSEN_TYPE, idc_chosen);
	DDX_Control(pDX, IDC_BUTTON_CHOOSE, btn_choose);
	DDX_Control(pDX, IDC_LIST1, list_ctrl_key);
}


BEGIN_MESSAGE_MAP(searchByDef, CDialogEx)

	ON_BN_CLICKED(IDC_SEARCH, &searchByDef::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE, &searchByDef::OnBnClickedButtonChoose)
	ON_BN_CLICKED(IDCANCEL, &searchByDef::OnBnClickedCancel)
END_MESSAGE_MAP()


// searchByDef message handlers




void searchByDef::OnBnClickedSearch()
{
	// TODO: Add your control notification handler code here
	list_ctrl_key.DeleteAllItems();

	UpdateData(TRUE);
	CString check;
	GetDlgItemText(IDC_EDIT_CHOSEN_TYPE, check);
	if (check.GetLength() < 1) {
		AfxMessageBox(_T("Choose the type of dictionary !"));
	}
	else {
		CString def;
		GetDlgItemText(IDC_EDIT1, def);
		CT2CA pszConvertedAnsiString(def);
		string d(pszConvertedAnsiString);
		vector<string> ans; vector<int> positionInDefList;
		if (!dict.searchByDef(d, dict.tree[type], ans, positionInDefList)) {
			MessageBox(_T("The definition does not exist !"));
		}
		else {
			for (int i = 0; i < ans.size(); i++) {
				CString index;
				index.Format(_T("%d"), i + 1);
				list_ctrl_key.InsertItem(i, index);
				CString key(ans[i].c_str());
				list_ctrl_key.SetItemText(i, 1, key);
			}
		}
	}
}


void searchByDef::OnBnClickedButtonChoose()
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
	list_ctrl_key.DeleteAllItems();
	list_ctrl_key.DeleteColumn(0);
	list_ctrl_key.DeleteColumn(0);
	list_ctrl_key.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	list_ctrl_key.InsertColumn(0, _T("Keyword"), LVCFMT_LEFT, 3000);
	list_ctrl_key.InsertColumn(0, _T("Number"), LVCFMT_LEFT, 100);
}


void searchByDef::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//for (int i = 0; i < 5; i++) deleteTree(dict.tree[i]);
	CDialogEx::OnCancel();
	CdictionaryGUIDlg mainMenu;
	mainMenu.DoModal();
}
