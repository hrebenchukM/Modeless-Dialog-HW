#include "ModelessDlg.h"
#include <fstream>
#include<iostream>
#include <string>

CModelessDialog* CModelessDialog::ptr = NULL;
HWND CModelessDialog::hAddDialog = NULL;


using namespace std;


CModelessDialog::CModelessDialog(void)
{
	ptr = this;
}

CModelessDialog::~CModelessDialog(void)
{

}

void CModelessDialog::Cls_OnClose(HWND hwnd)
{
	// ��������� ����������� ���������� ����
	DestroyWindow(hwnd);
	hAddDialog = NULL;
}





void CModelessDialog::SetText(LPCTSTR str)
{
	/*TCHAR text[100];
	_tcscpy(text, str);
	SetWindowText(hStatic,text);*/
	SetWindowText(hStatic, str);
}




BOOL CModelessDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);
	SetWindowText(hwnd, TEXT("�������������� ����������� ������"));
	//SetWindowText(GetDlgItem(hwnd, IDC_EDIT1), TEXT("�������� ������ �������� �������!"));
	return TRUE;
}


void CModelessDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	// ������� ���� ��� ������
	ofstream file("file.txt", std::ios::app);

	switch (id)
	{

	case IDSAVE:
	{
		// �������� ��������� ������
		TCHAR login[100], password[100], name[100], age[10];
		GetDlgItemText(hwnd, IDC_EDIT1LOGIN, login, 100);
		GetDlgItemText(hwnd, IDC_EDIT2CODE, password, 100);
		GetDlgItemText(hwnd, IDC_EDIT3NAME, name, 100);
		GetDlgItemText(hwnd, IDC_EDIT4AGE, age, 10);


		ofstream file("file.txt", std::ios::app);
		if (file.is_open())
		{

			file << login << " " << password << " " << name << " " << age << std::endl;

			file.close();
			MessageBox(hwnd, TEXT("������ ���������"), TEXT("�����"), MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			MessageBox(hwnd, TEXT("������ ��� ���������� ������"), TEXT("������"), MB_OK | MB_ICONERROR);
		}
		EndDialog(hwnd, 0);
	}
	break;




	case IDOK:
	{
		TCHAR login[100], password[100];
		GetDlgItemText(hwnd, IDC_EDIT1LOGIN, login, 100);
		GetDlgItemText(hwnd, IDC_EDIT2CODE, password, 100);

		// ����������� TCHAR � std::wstring
		wstring w_login(login);
		wstring w_password(password);

		// ��������� ���� ��� ������
		ifstream file("file.txt");
		if (file.is_open())
		{
			bool found = false;
			string line;
			while (getline(file, line))
			{
				size_t pos = line.find(' ');
				if (pos != string::npos)
				{
					string stored_login = line.substr(0, pos);
					string stored_password = line.substr(pos + 1);


					// ����������� stored_login � stored_password � wstring
					wstring w_stored_login(stored_login.begin(), stored_login.end());
					wstring w_stored_password(stored_password.begin(), stored_password.end());
					if (w_stored_login == w_login && w_stored_password == w_password)
					{
						found = true;
						break;
					}
				}
			}
			file.close();

			if (found)
			{
				MessageBox(hwnd, TEXT("����� ����������"), TEXT("�����"), MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hwnd, TEXT("�������� ����� ��� ������"), TEXT("������"), MB_OK | MB_ICONERROR);
			}
		}
		else
		{
			MessageBox(hwnd, TEXT("������ ��� �������� �����"), TEXT("������"), MB_OK | MB_ICONERROR);
		}
		EndDialog(hwnd, 0);
	}
	break;
	}
}

BOOL CALLBACK CModelessDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
