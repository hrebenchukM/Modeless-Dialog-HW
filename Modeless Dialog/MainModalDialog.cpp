#include "MainModalDialog.h"
#include "ModelessDlg.h"

#define MAX_DIALOGS 3
CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}

CMainModalDialog::~CMainModalDialog(void)
{

}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

void CModelessDialog::SetHWND(HWND hwnd)
{
	hDialog = hwnd;
}



BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hStatic1 = GetDlgItem(hwnd, IDC_STATIC1);
	return TRUE;
}






CModelessDialog* arrDialogs[MAX_DIALOGS]; 
int numDialogs = 0; 

void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_REGISTRATION )
	{
		if (numDialogs < MAX_DIALOGS)
		{
			CModelessDialog* ptrDlg = new CModelessDialog();

	
			HWND hNewDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CModelessDialog::DlgProc);
			ptrDlg->SetHWND(hNewDialog);



			
			ShowWindow(hNewDialog, SW_RESTORE);
			arrDialogs[numDialogs] = ptrDlg; 
			numDialogs++;
		}
	}
	if (id == IDC_AUTORISATION)
	{
		if (numDialogs < MAX_DIALOGS)
		{
			CModelessDialog* ptrDlg = new CModelessDialog();

		
			HWND hNewDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, CModelessDialog::DlgProc);
			ptrDlg->SetHWND(hNewDialog);



		
			ShowWindow(hNewDialog, SW_RESTORE);
			arrDialogs[numDialogs] = ptrDlg; 
			numDialogs++;
		}
	}



	//static CModelessDialog dlg;
	//if (id == IDC_BUTTON1)
	//{
	//	
	//	if (CModelessDialog::hAddDialog)
	//	{
	//	
	//		SetForegroundWindow(CModelessDialog::hAddDialog);	
	//		TCHAR buffer[200]; 
	//	
	//		GetWindowText(hEdit1, buffer, 200);
	//		
	//		// SetWindowText(dlg.hStatic, buffer);
	//		dlg.SetText(buffer);
	//		//MessageBox(0, buffer, NULL, MB_OK);

	//	
	//		
	//	ShowWindow(CModelessDialog::hAddDialog, SW_RESTORE);
	//	
	//	
	//	return;
	//	}
	//	else
	//	{
	//		//CModelessDialog dlg;
	//		
	//		CModelessDialog::hAddDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CModelessDialog::DlgProc);

	//		
	//		ShowWindow(CModelessDialog::hAddDialog, SW_RESTORE);

	//	
	//	}
	//	TCHAR buffer[200];
	//
	//	GetWindowText(hEdit1, buffer, 200);
	//	
	//	//SetWindowText(dlg.hStatic, buffer);
	//	dlg.SetText(buffer);
	//	return;
	//
	//}
}
void OnDestroy()
{
	for (int i = 0; i < numDialogs; i++)
	{
		delete arrDialogs[i];
	}
}









BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}