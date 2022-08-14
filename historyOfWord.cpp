// historyOfWord.cpp : implementation file
//

#include "pch.h"
#include "dictionaryGUI.h"
#include "afxdialogex.h"
#include "historyOfWord.h"


// historyOfWord dialog

IMPLEMENT_DYNAMIC(historyOfWord, CDialogEx)

historyOfWord::historyOfWord(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

historyOfWord::~historyOfWord()
{
}

void historyOfWord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list_ctrl_historyWord);
	DDX_Control(pDX, IDC_BUTTON1, btn_show);
}


BEGIN_MESSAGE_MAP(historyOfWord, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &historyOfWord::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &historyOfWord::OnBnClickedCancel)
END_MESSAGE_MAP()


// historyOfWord message handlers


void historyOfWord::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	list_ctrl_historyWord.DeleteAllItems();
	list_ctrl_historyWord.DeleteColumn(0);
	list_ctrl_historyWord.DeleteColumn(0);
	list_ctrl_historyWord.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	list_ctrl_historyWord.InsertColumn(0, _T("Definition"), LVCFMT_LEFT, 3000);
	list_ctrl_historyWord.InsertColumn(0, _T("Keyword"), LVCFMT_LEFT, 100);
	vector<Word> his;
	dict.getHistoryWords(his);
	for (int i = 0; i < his.size(); i++) {
		CString keyword(his[i].key.c_str());
		list_ctrl_historyWord.InsertItem(i,keyword);
		CString def(his[i].def.c_str());
		list_ctrl_historyWord.SetItemText(i, 1, def);
	}
}


void historyOfWord::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
	CdictionaryGUIDlg mainMenu;
	mainMenu.DoModal();
}
