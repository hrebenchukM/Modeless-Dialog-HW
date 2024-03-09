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
	// Разрушаем немодальное диалоговое окно
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
	SetWindowText(hwnd, TEXT("Дополнительный немодальный диалог"));
	//SetWindowText(GetDlgItem(hwnd, IDC_EDIT1), TEXT("Передача данных главному диалогу!"));
	return TRUE;
}


void CModelessDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{


	switch (id)
	{

	case IDSAVE:
	{




		// Получаем введенные данные
		TCHAR login[100], password[100], name[100], age[10];
		GetDlgItemText(hwnd, IDC_EDIT1LOGIN, login, 100);
		GetDlgItemText(hwnd, IDC_EDIT2CODE, password, 100);
		GetDlgItemText(hwnd, IDC_EDIT3NAME, name, 100);
		GetDlgItemText(hwnd, IDC_EDIT4AGE, age, 10);


		std::wofstream file("users.txt", std::ios::out);

		if (file.is_open())
		{

			file << login << " " << password << " " << name << " " << age << endl;

			file.close();
			MessageBox(hwnd, TEXT("Данные сохранены"), TEXT("Успех"), MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			MessageBox(hwnd, TEXT("Ошибка при сохранении данных"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		}
		EndDialog(hwnd, 0);
	}
	break;







	case IDOK:
	{
		char login[100], password[100];
		GetDlgItemTextA(hwnd, IDC_EDIT1LOGIN, login, 100);
		GetDlgItemTextA(hwnd, IDC_EDIT2CODE, password, 100);

		bool found = false;

		std::ifstream file("users.txt");
		if (file.is_open())
		{
			char stored_login[100], stored_password[100];
			while (file >> stored_login >> stored_password)
			{
				// Проверяем совпадение введенного логина и пароля с данными из файла
				if (strcmp(stored_login, login) == 0 && strcmp(stored_password, password) == 0)
				{
					found = true;
					break; 
				}
			}
			file.close();

			if (found)
			{
				MessageBox(hwnd, TEXT("Добро пожаловать"), TEXT("Успех"), MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hwnd, TEXT("Неверный логин или пароль"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
			}
		}

		else
		{
			MessageBox(hwnd, TEXT("Ошибка при открытии файла"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
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
