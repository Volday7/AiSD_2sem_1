#include <iostream>
#include "Header.h"
#include <Windows.h>
#include <conio.h>

using namespace std;

bool control(char* xn)
{
	int zap_p = 0;
	char mask[12] = { '1','2','3','4','5','6','7','8','9','0', '-' };
	int checker = 0;
	for (int i = 0; i < strlen(xn); i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (xn[i] == mask[j]) checker++;
		}
	}
	if (checker != strlen(xn)) return false;
	if (checker == 0) return false;
	checker = 0;

	char check;
	for (size_t i = 0; i < strlen(xn); i++) {
		if (xn[0] == '-' && xn[1] == '\0') {
			return false;
		}
		if (xn[0] == ',') return false;
		if (xn[i] == ',') {
			zap_p++;
		}
		if ((xn[i + 1] == '-') || (xn[i] == '\0'))
		{
			return false;
		}
		if (zap_p > 1) return false;
	}
	return true;
}

float checker() {
	char n_data[64];
	while (true) {
		gets_s(n_data);
		bool check = control(n_data);
		if (check == true) break;
		else {
			printf("Неправильный формат данных:( \n");
			printf("[Исправленный вариант]: ");
		}
	}
	int data = (float)atoi(n_data);
	return data;
}

int GetKey() noexcept {
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
}

int Ent() noexcept {
	while (true) {
		int key = GetKey();
		if (key == 13) return key;
	}
}

void menu(Set set) {
	while (true) {
		system("cls");
		set.Print();
		cout << "1 - Insert\n";
		cout << "2 - Find\n";
		cout << "3 - Erase\n";
		cout << "4 - Exit\n";
		int m = GetKey();
		if (m == 49) {
			system("cls");
			cout << "Enter number: ";
			int real_num = checker();
			if (set.Insert(real_num) == true) cout << "\nSuccess!";
			else cout << "\nYour number is already in Set!";
			cout << "\nPress Enter to continue...";
			Ent();
		}
		if (m == 50) {
			system("cls");
			cout << "Enter number: ";
			int real_num = checker();
			if (set.Find(set.GetNode(), real_num) == true) cout << "\nSuccess!";
			else cout << "\nNope :(";
			cout << "\nPress Enter to continue...";
			Ent();
		}
		if (m == 51) {
			system("cls");
			cout << "Enter number: ";
			int real_num = checker();
			if (set.Erase(real_num) == true) cout << "\nSuccess!";
			cout << "\nPress Enter to continue...";
			Ent();
		}
		if (m == 52) {
			break;
		}
	}
}

int main() {
	Set a;
	menu(a);
	return 0;
}