#include "process-procedures.h"
#include <string>
#include <sstream>

void StringToNumber()
{
	cout << "\n *Перетворення рядка - масиву літер та рядка-контейнера - на число*\n";

	cout << "\n-Рядок в стилі С-\n";
	const unsigned size = 256;    // потрібно задати розмір масиву літер
	char c_line[size] = { '\0' }; // масив ініціалізуємо літерами з кодом 0
	cout << "Введіть послідовність літер, що містить цифри:\n";
	cin.getline(c_line, size);    // введений рядок обмежений розміром масиву

	cout << "\n   Перетворення власною функцією\n";
	int error_code;
	int number = RecognizeInteger(c_line, error_code);
	if (error_code == -1)
		cout << "Введене число: " << number << '\n';
	else
		cout << "Рядок містить помилку в позиції " << error_code
		<< " Вдалося прочитати " << number << '\n';

	cout << "\n   Перетворення стандартною функцією\n";
	number = std::atoi(c_line);
	if (errno == ERANGE) cout << "Помилка: Сталося переповнення\n";
	cout << "Введене число: " << number << "  Код помилки " << errno << '\n';
	errno = 0;

	cout << "\n   Використання потоку, накладеного на рядок\n";
	std::string line(c_line);
	std::istringstream stream(line);
	stream >> number;           // перетворення виконує оператор введення
	cout << "Введене число: " << number << '\n';
	return;
}

void IntSuccession()
{
	cout << "\n *Обчислення суми цілих чисел, записаних у рядку*\n";
	char* succ = "25 -32 777 12 -98 -5 2018";
	cout << "Задана послідовність:\n" << succ << '\n';
	int sum = 0;
	int pos = 0;
	cout << "Члени послідовності:\n";
	do
	{
		int term = RecognizeInteger(succ += pos, pos);
		cout << term << '\n';
		sum += term;
	} while (pos != -1);
	cout << " Сума = " << sum << '\n';
}

int RecognizeInteger(const char* line, int& pos)
{
	const int max = INT_MAX / 10;
	const char* curr = line;
	int result = 0;                  // число, яке треба сформувати
	pos = -1;
	while (*curr == ' ' || *curr == '\t') ++curr;  // пропускаємо пропуски
	bool sign = false;               // sign пам'ятає про наявність мінуса
	if (*curr == '+') ++curr;        // плюс можна пропустити,
	if (*curr == '-')                // а мінус треба запам'ятати
	{
		sign = true;
		++curr;
	}
	while (*curr != '\0')            // переглядаємо весь рядок
	{
		if (*curr >= '0' && *curr <= '9')
		{                            // знайдену цифру перетворюємо на число
			int digit = *curr - '0'; // чи не загрожує переповнення?
			if (max < result || max == result && digit  > 7)
			{                        // якщо так, то перериваємо обчислення
				pos = curr - line;
				break;
			}
			result = result * 10 + digit; // додаємо нову цифру до результату
			++curr;
		}
		else
		{                            // фіксуємо позицію нечислового символу
			pos = curr - line;
			break;
		}
	}
	return sign ? -result : result;
}