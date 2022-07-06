#include "process-procedures.h"
#include <string>

void CountCharByChar()
{
	cout << "\n *ʳ������ ���� � ����� ����, ����������� ��������*\n\n"
		<< "������ ����������� ����, �� ���������� �������:\n";
	unsigned digits_quantity = 0;     // �������� ����
	char letter;
	do
	{
		letter = cin.get();  // ��������� � ������ ������� �����
		if (letter >= '0' && letter <= '9') ++digits_quantity;
	} while (letter != '.'); // ����������� ����� �� ����� ������
	cout << "����������� ������ " << digits_quantity << " ����\n";
	return;
}

void CountInString()
{
	cout << "\n *ʳ������ ���� � ����� - ����� ���� �� � ���������*\n";

	cout << "\n-����� � ���� �-\n";
	const unsigned size = 256;    // ������� ������ ����� ������ ����
	char c_line[size] = { '\0' }; // ����� ���������� ������� � ����� 0
	cout << "������ ����������� ����, �� ������ �����:\n";
	cin.get(c_line, size);        // �������� ����� ��������� ������� ������
	while (cin.get() != '\n')     // ������� ���� �� ��������� ������� �����
		continue;
	unsigned digits_quantity = 0;        // �������� ����
	for (unsigned i = 0; c_line[i] != '\0'; ++i)
	{
		if (c_line[i] >= '0' && c_line[i] <= '9') ++digits_quantity;
	}
	cout << "����������� ������ " << digits_quantity << " ����\n";

	cout << "\n-����� �������� std-\n";
	std::string line;         // ��������� ������� ������
	cout << "������ ����������� ����, �� ������ �����:\n";
	getline(cin, line);       // ������ �������� �� ����� �� ���� ����� '\n'
	digits_quantity = 0;      // �������� ���� ����������� ��� �����
	for (unsigned i = 0; i < line.length(); ++i)
	{
		if (line[i] >= '0' && line[i] <= '9') ++digits_quantity;
	}
	cout << "����������� ������ " << digits_quantity << " ����\n";
	return;
}
