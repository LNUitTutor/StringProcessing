#include "process-procedures.h"
#include <string>
#include <sstream>

void StringToNumber()
{
	cout << "\n *������������ ����� - ������ ���� �� �����-���������� - �� �����*\n";

	cout << "\n-����� � ���� �-\n";
	const unsigned size = 256;    // ������� ������ ����� ������ ����
	char c_line[size] = { '\0' }; // ����� ���������� ������� � ����� 0
	cout << "������ ����������� ����, �� ������ �����:\n";
	cin.getline(c_line, size);    // �������� ����� ��������� ������� ������

	cout << "\n   ������������ ������� ��������\n";
	int error_code;
	int number = RecognizeInteger(c_line, error_code);
	if (error_code == -1)
		cout << "������� �����: " << number << '\n';
	else
		cout << "����� ������ ������� � ������� " << error_code
		<< " ������� ��������� " << number << '\n';

	cout << "\n   ������������ ����������� ��������\n";
	number = std::atoi(c_line);
	if (errno == ERANGE) cout << "�������: ������� ������������\n";
	cout << "������� �����: " << number << "  ��� ������� " << errno << '\n';
	errno = 0;

	cout << "\n   ������������ ������, ����������� �� �����\n";
	std::string line(c_line);
	std::istringstream stream(line);
	stream >> number;           // ������������ ������ �������� ��������
	cout << "������� �����: " << number << '\n';
	return;
}

void IntSuccession()
{
	cout << "\n *���������� ���� ����� �����, ��������� � �����*\n";
	char* succ = "25 -32 777 12 -98 -5 2018";
	cout << "������ �����������:\n" << succ << '\n';
	int sum = 0;
	int pos = 0;
	cout << "����� �����������:\n";
	do
	{
		int term = RecognizeInteger(succ += pos, pos);
		cout << term << '\n';
		sum += term;
	} while (pos != -1);
	cout << " ���� = " << sum << '\n';
}

int RecognizeInteger(const char* line, int& pos)
{
	const int max = INT_MAX / 10;
	const char* curr = line;
	int result = 0;                  // �����, ��� ����� ����������
	pos = -1;
	while (*curr == ' ' || *curr == '\t') ++curr;  // ���������� ��������
	bool sign = false;               // sign ���'��� ��� �������� �����
	if (*curr == '+') ++curr;        // ���� ����� ����������,
	if (*curr == '-')                // � ���� ����� �����'�����
	{
		sign = true;
		++curr;
	}
	while (*curr != '\0')            // ����������� ���� �����
	{
		if (*curr >= '0' && *curr <= '9')
		{                            // �������� ����� ������������ �� �����
			int digit = *curr - '0'; // �� �� ������� ������������?
			if (max < result || max == result && digit  > 7)
			{                        // ���� ���, �� ���������� ����������
				pos = curr - line;
				break;
			}
			result = result * 10 + digit; // ������ ���� ����� �� ����������
			++curr;
		}
		else
		{                            // ������� ������� ����������� �������
			pos = curr - line;
			break;
		}
	}
	return sign ? -result : result;
}