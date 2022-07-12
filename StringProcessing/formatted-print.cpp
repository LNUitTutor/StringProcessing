#include "process-procedures.h"
#include <exception>
#include <string>

// ������� ���� ����� - ����� ����� num � ������ � ������� radix
//   ������� ����� �� ����� �� width
char* RadixFormStr(int number, unsigned radix, bool upcase, unsigned width)
{
	if (radix < 2 || radix > 36)
		throw std::invalid_argument("Wrong radix value");
	// ���� - ��������� �������, � ��� �������� ���������� �������� 
	if (number == 0)
	{
		char* str;
		if (width > 1)
		{
			str = new char[width + 1];
			str[width] = '\0';
			str[--width] = '0';
			while (width > 0) str[--width] = ' ';
		}
		else str = new char[2]{ '0', '\0' };
		return str;
	}
	// ������ �� 0 ����� - ������������ ����
	bool sign;
	if (number > 0) sign = false;
	else
	{
		sign = true;
		number = -number;
	}
	// ����� ��'������ ����� ������ '-', ���� �� 1 ����� ������
	int length = std::log(double(number)) / std::log(radix) + 1 + sign;
	// ������ ���� ��� ������
	if (width >= length)
	{
		width -= length;
		length += width;
	}
	char* str = new char[length + 1];
	str[length] = '\0';
	// ����� �������������� � ��������
	while (width > 0) str[--width] = ' ';
	const char digit = upcase ? 'A' - 10 : 'a' - 10;
	while (number > 0)
	{	                       // ������ ������������ ����
		--length;
		unsigned rightmost_digit = number % radix;  // ������� ����� �����
		if (rightmost_digit < 10)
			str[length] = '0' + rightmost_digit;  // �������� �����
		else str[length] = digit + rightmost_digit; // ������ �����-�����
		number /= radix;
	}
	if (sign) str[--length] = '-';
	return str;
}

void FormattedPrint(const char* format, int number)
{
	char specification;
	while (*format != '\0')
	{
		if (*format != '%') // �������� �����
		{
			cout << *format++;
		}
		else // �������, �� ������� ������������
		{
			++format;           // ��������� �������� �����
			if (*format == '%') // ����� ������ ����� �������
			{
				cout << *format++;
			}
			else // ������� ������������
			{
				specification = *format++;
				break;
			}
		}
	}
	if (*format == '\0') throw std::invalid_argument("No format specification found");
	unsigned radix = 10;
	bool upcase = false;
	switch (specification) // ������������ ������ ������� ��������
	{
	case 'b': case 'B': radix = 2;  break;
	case 'd': case 'D': break;
	case 'o': case 'O': radix = 8; break;
	case 'h': radix = 16; break;
	case 'H': radix = 16; upcase = true; break;
	default: throw std::invalid_argument("Unknown format specification found");
	}
	// ������������ ������ ���� ���������
	int pos;
	int width = RecognizeInteger(format, pos);
	if (width < 0) throw std::invalid_argument("Invalid width specification found");
	// �������� ������ ����� �������� �� �������� �������
	char* str = RadixFormStr(number, radix, upcase, width);
	cout << str;  delete[] str;        // ������� ����� � ��������� ���'���
	if (pos == -1) return;             // ����� ������� ��������� ������
	// ����������� ������� ������
	if (pos > 0) format += pos;
	while (*format != '\0')
	{
		if (*format != '%') // �������� �����
			cout << *format++;
		else if (*++format != '%') throw std::invalid_argument("Extra format specification found");
		else                // ������� � �����
			cout << *format++;
	}
}

std::string FormattedString(const char* format, int num)
{
	std::string result;
	char spec;
	while (*format != '\0')
	{
		if (*format != '%') // �������� �����
			result += *format++;
		else // �������, �� ������� ������������
		{
			++format;           // ��������� �������� �����
			if (*format == '%') // ����� ������ ����� �������
				result += *format++;
			else // ������� ������������
			{
				spec = *format++;
				break;
			}
		}
	}
	if (*format == '\0') throw std::invalid_argument("No format specification found");
	unsigned radix = 10;
	bool upcase = false;
	switch (spec) // ������������ ������ ������� ��������
	{
	case 'b': case 'B': radix = 2;  break;
	case 'd': case 'D': break;
	case 'o': case 'O': radix = 8; break;
	case 'h': radix = 16; break;
	case 'H': radix = 16; upcase = true; break;
	default: throw std::invalid_argument("Unknown format specification found");
	}
	// ������������ ������ ���� ���������
	int pos;
	int width = RecognizeInteger(format, pos);
	if (width < 0) throw std::invalid_argument("Invalid width specification found");
	// �������� ������ ����� �������� �� �������� �������
	char* str = RadixFormStr(num, radix, upcase, width);
	result += str;  delete[] str;      // �������� ����� � ��������� ���'���
	if (pos == -1) return result;      // ����� ������� ��������� ������
	// ����������� ������� ������
	if (pos > 0) format += pos;
	while (*format != '\0')
	{
		if (*format != '%') // �������� �����
			result += *format++;
		else if (*++format != '%') throw std::invalid_argument("Extra format specification found");
		else                // ������� � �����
			result += *format++;
	}
	return result;
}

void TryFprint()
{
	cout << "\n *��������� ������ ����� �� ���� �������� �� �������, �������� ������*\n";
	cout << " --- ������ ��������\n";
	FormattedPrint("Zero%D2 is equal to 0\n", 0);
	FormattedPrint("Number(10) =%d10\n", -1023);
	FormattedPrint("Number(8) = %o1\n", -1023);
	FormattedPrint("Number(16) = %h8\n", 1023);
	FormattedPrint("Number(16) = %H\n", 1023);
	FormattedPrint("Number(2) = %b1\n", 1023);
	cout << " --- ����������� ��������� �����\n";
	int percentage = 75;
	FormattedPrint("����� ��������� ��������� %d%%\n", percentage);
	cout << " --- ����������� ��������� �����������\n";
	int a[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256 };
	cout << "������� 2 {";
	for (int i = 0; i < 9; ++i) FormattedPrint("%H5", a[i]);
	cout << " }(16)\n";
	try
	{
		FormattedPrint("Number = 1024", 0);
	}
	catch (std::invalid_argument& ex)
	{
		cout << "\n\n" << ex.what() << '\n';
	}
	cout << FormattedString("Number =%D10\n", -1023) << '\n';
}