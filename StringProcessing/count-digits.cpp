#include "process-procedures.h"
#include <string>

void CountCharByChar()
{
	cout << "\n *Кількість цифр у рядку літер, посимвольне введення*\n\n"
		<< "Введіть послідовність літер, що закінчується крапкою:\n";
	unsigned digits_quantity = 0;     // лічильник цифр
	char letter;
	do
	{
		letter = cin.get();  // отримання з потоку чергової літери
		if (letter >= '0' && letter <= '9') ++digits_quantity;
	} while (letter != '.'); // опрацювання триває до першої крапки
	cout << "Послідовність містить " << digits_quantity << " цифр\n";
	return;
}

void CountInString()
{
	cout << "\n *Кількість цифр у рядку - масиві літер та в контейнері*\n";

	cout << "\n-Рядок в стилі С-\n";
	const unsigned size = 256;    // потрібно задати розмір масиву літер
	char c_line[size] = { '\0' }; // масив ініціалізуємо літерами з кодом 0
	cout << "Введіть послідовність літер, що містить цифри:\n";
	cin.get(c_line, size);        // введений рядок обмежений розміром масиву
	while (cin.get() != '\n')     // очищаємо потік від можливого залишку рядка
		continue;
	unsigned digits_quantity = 0;        // лічильник цифр
	for (unsigned i = 0; c_line[i] != '\0'; ++i)
	{
		if (c_line[i] >= '0' && c_line[i] <= '9') ++digits_quantity;
	}
	cout << "Послідовність містить " << digits_quantity << " цифр\n";

	cout << "\n-Рядок бібліотеки std-\n";
	std::string line;         // контейнер змінного розміру
	cout << "Введіть послідовність літер, що містить цифри:\n";
	getline(cin, line);       // будуть прочитані всі літери до кінця рядка '\n'
	digits_quantity = 0;      // лічильник цифр використаємо той самий
	for (unsigned i = 0; i < line.length(); ++i)
	{
		if (line[i] >= '0' && line[i] <= '9') ++digits_quantity;
	}
	cout << "Послідовність містить " << digits_quantity << " цифр\n";
	return;
}
