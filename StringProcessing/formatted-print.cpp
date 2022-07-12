#include "process-procedures.h"
#include <exception>
#include <string>

// Функція будує рядок - запис числа num в системі з основою radix
//   довжина рядка не менша за width
char* RadixFormStr(int number, unsigned radix, bool upcase, unsigned width)
{
	if (radix < 2 || radix > 36)
		throw std::invalid_argument("Wrong radix value");
	// нуль - особливий випадок, у всіх системах записується однаково 
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
	// відмінне від 0 число - послідовність цифр
	bool sign;
	if (number > 0) sign = false;
	else
	{
		sign = true;
		number = -number;
	}
	// запис від'ємного числа містить '-', тому на 1 літеру довший
	int length = std::log(double(number)) / std::log(radix) + 1 + sign;
	// готуємо місце для запису
	if (width >= length)
	{
		width -= length;
		length += width;
	}
	char* str = new char[length + 1];
	str[length] = '\0';
	// запис починатиметься з пропусків
	while (width > 0) str[--width] = ' ';
	const char digit = upcase ? 'A' - 10 : 'a' - 10;
	while (number > 0)
	{	                       // будуємо послідовність цифр
		--length;
		unsigned rightmost_digit = number % radix;  // остання цифра числа
		if (rightmost_digit < 10)
			str[length] = '0' + rightmost_digit;  // звичайні цифри
		else str[length] = digit + rightmost_digit; // старші цифри-букви
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
		if (*format != '%') // звичайна літера
		{
			cout << *format++;
		}
		else // можливо, це початок специфікації
		{
			++format;           // перевіримо наступну літеру
			if (*format == '%') // рядок містить літеру відсоток
			{
				cout << *format++;
			}
			else // знайшли специфікацію
			{
				specification = *format++;
				break;
			}
		}
	}
	if (*format == '\0') throw std::invalid_argument("No format specification found");
	unsigned radix = 10;
	bool upcase = false;
	switch (specification) // розпізнавання основи системи числення
	{
	case 'b': case 'B': radix = 2;  break;
	case 'd': case 'D': break;
	case 'o': case 'O': radix = 8; break;
	case 'h': radix = 16; break;
	case 'H': radix = 16; upcase = true; break;
	default: throw std::invalid_argument("Unknown format specification found");
	}
	// розпізнавання ширини поля виведення
	int pos;
	int width = RecognizeInteger(format, pos);
	if (width < 0) throw std::invalid_argument("Invalid width specification found");
	// побудова запису числа відповідно до заданого формату
	char* str = RadixFormStr(number, radix, upcase, width);
	cout << str;  delete[] str;        // друкуємо число і звільняємо пам'ять
	if (pos == -1) return;             // рядок формату закінчився числом
	// опрацювання залишків тексту
	if (pos > 0) format += pos;
	while (*format != '\0')
	{
		if (*format != '%') // звичайна літера
			cout << *format++;
		else if (*++format != '%') throw std::invalid_argument("Extra format specification found");
		else                // відсоток в тексті
			cout << *format++;
	}
}

std::string FormattedString(const char* format, int num)
{
	std::string result;
	char spec;
	while (*format != '\0')
	{
		if (*format != '%') // звичайна літера
			result += *format++;
		else // можливо, це початок специфікації
		{
			++format;           // перевіримо наступну літеру
			if (*format == '%') // рядок містить літеру відсоток
				result += *format++;
			else // знайшли специфікацію
			{
				spec = *format++;
				break;
			}
		}
	}
	if (*format == '\0') throw std::invalid_argument("No format specification found");
	unsigned radix = 10;
	bool upcase = false;
	switch (spec) // розпізнавання основи системи числення
	{
	case 'b': case 'B': radix = 2;  break;
	case 'd': case 'D': break;
	case 'o': case 'O': radix = 8; break;
	case 'h': radix = 16; break;
	case 'H': radix = 16; upcase = true; break;
	default: throw std::invalid_argument("Unknown format specification found");
	}
	// розпізнавання ширини поля виведення
	int pos;
	int width = RecognizeInteger(format, pos);
	if (width < 0) throw std::invalid_argument("Invalid width specification found");
	// побудова запису числа відповідно до заданого формату
	char* str = RadixFormStr(num, radix, upcase, width);
	result += str;  delete[] str;      // дописуємо число і звільняємо пам'ять
	if (pos == -1) return result;      // рядок формату закінчився числом
	// опрацювання залишків тексту
	if (pos > 0) format += pos;
	while (*format != '\0')
	{
		if (*format != '%') // звичайна літера
			result += *format++;
		else if (*++format != '%') throw std::invalid_argument("Extra format specification found");
		else                // відсоток в тексті
			result += *format++;
	}
	return result;
}

void TryFprint()
{
	cout << "\n *Виведення цілого числа на друк відповідно до формату, заданого рядком*\n";
	cout << " --- Тестові приклади\n";
	FormattedPrint("Zero%D2 is equal to 0\n", 0);
	FormattedPrint("Number(10) =%d10\n", -1023);
	FormattedPrint("Number(8) = %o1\n", -1023);
	FormattedPrint("Number(16) = %h8\n", 1023);
	FormattedPrint("Number(16) = %H\n", 1023);
	FormattedPrint("Number(2) = %b1\n", 1023);
	cout << " --- Форматоване виведення числа\n";
	int percentage = 75;
	FormattedPrint("Якісна успішність становила %d%%\n", percentage);
	cout << " --- Форматоване виведення послідовності\n";
	int a[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256 };
	cout << "Степені 2 {";
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