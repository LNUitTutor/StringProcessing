#include <Windows.h>
#include "process-procedures.h"

int main()
{
	// ����������� �������� ����������

	SetConsoleOutputCP(1251); // ��������� ��������� ���������
	SetConsoleCP(1251);
	int answer;
	do
	{
		system("cls");
		cout << "������� �������� ��� ���������:\n\n 1 - ���������� ������� ���� (�����������)\n"
			<< " 2 - ���������� ������� ���� � �����\n 3 - ������������ ����� �� �����\n"
			<< " 4 - ���� ����������� �����\n 5 - ϳ��������� � �����\n"
			<< " 6 - ����������� ��������� ����� �����\n 7 - ³�������� ���������� �����\n"
			<< " 8 - ���������� ������\n>>>> ";
		cin >> answer; cin.get();
		system("cls");
		switch (answer)
		{
		case 1: CountCharByChar(); break;
		case 2: CountInString(); break;
		case 3: StringToNumber(); break;
		case 4: IntSuccession(); break;
		case 5: DoReplace(); break;
		case 6: TryFprint(); break;
		case 7: PrintLongest(); break;
		default: cout << "�� ���������!\n";
		}
		system("pause");
	}
	while (answer > 0 && answer < 8);
	return 0;
}