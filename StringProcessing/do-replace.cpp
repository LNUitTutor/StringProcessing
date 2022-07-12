#include "process-procedures.h"

char* Replace(char* source, char what, const char* by)
{
	// ��������, ������ ���� ����������� ������ �����
	// �������� �������� ������� �����
	unsigned counter = 0;
	unsigned length = 0;
	while (source[length] != '\0')
	{
		if (source[length] == what) ++counter;
		++length;
	}
	// ������� ��������� ���� ��� ������ �����
	unsigned by_len = strlen(by);
	char* new_line = new char[length + 1 + (by_len - 1) * counter];
	unsigned dest = 0;
	for (unsigned i = 0; i < length; ++i)  // � �������� �����
	{
		if (source[i] != what) new_line[dest++] = source[i];
		else
		{
			for (unsigned j = 0; j < by_len; ++j) new_line[dest++] = by[j];
		}
	}
	new_line[dest] = '\0';   // ���������� �����
	return new_line;
}

void DoReplace()
{
	cout << "\n *����� ����� '+' � ����� ������ ���� ' plus'*\n\n";
	char cpp[] = "I like C++";
	cout << "���������� �����: " << cpp << '\n';
	char* res = Replace(cpp, '+', " plus");
	cout << "����� ���� ����������: " << res << '\n';
	delete[] res;
	return;
}
