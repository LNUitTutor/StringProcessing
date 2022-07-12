#include "process-procedures.h"
#include <string>
#include <sstream>

using std::string;

void LongestByArray()
{
	const int text_size = 256;
	char text[text_size] = { 0 }; // ���� ��� ����������� ������
	cout << "������ ����� (�� 255 ����): ";
	cin.getline(text, text_size);
	if (cin.failbit > 0)
	{
		// ����� ��������� ������� ���� �� ������� �����
		cin.clear();
		while (cin.get() != '\n') continue;
	}
	cout << "\n�� �����: " << text << '\n';
	// �������� �����������
	int start = 0;             // ������� ���������� �����
	int max_length = 0;            // ���� �������
	int curr = 0;              // ������� ������
	while (text[curr] != '\0') // ����������� �� ������������ �������
	{
		int pos = curr;        // ������� ��������� �����
		while (text[curr] != '\0' && text[curr] != ' ')	++curr; // ������ ���� ���������
		int length = curr - pos;  // ������� ��������� �����
		if (length > max_length)
		{                      // ������� �����
			max_length = length;
			start = pos;
		}
		while (text[curr] != '\0' && text[curr] == ' ') ++curr; // ������ �������� �����
	}
	// ����� ����� �������� �������� �����
	char * longestWord = new char[max_length + 1];
	for (int i = 0; i < max_length; ++i) longestWord[i] = text[start + i];
	longestWord[max_length] = '\0';
	cout << "�������� �����: " << longestWord << '\n';
	delete[] longestWord;
}

void LongestByString()
{
	string text;
	cout << "������ �����: ";
	getline(cin, text);
	cout << "\n�� �����: " << text << '\n';
	// ����������� �� ��������� ������ ����
	std::istringstream stream(text);
	string word, max_word;
	int max_length = 0;
	while (stream >> word) // �������� �������� ������� ��������
	{
		int length = word.length();
		if (length > max_length)
		{
			max_length = length;
			max_word = word;
		}
	}
	cout << "�������� �����: " << max_word << '\n';
}

void PrintLongest()
{
	cout << "\n *³�������� ���������� � ����� �����*\n";
	cout << "\n-� ������������� ����� � ���� �-\n";
	LongestByArray();
	cout << "\n-� ������������� �����-����������-\n";
	LongestByString();
}