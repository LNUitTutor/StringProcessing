#include <Windows.h>
#include "process-procedures.h"

int main()
{
	// Опрацювання текстової інформації

	SetConsoleOutputCP(1251); // налаштуємо виведення кирилицею
	SetConsoleCP(1251);
	int answer;
	do
	{
		system("cls");
		cout << "Виберіть алгоритм для виконання:\n\n 1 - Обчислення кількості цифр (посимвольно)\n"
			<< " 2 - Обчислення кількості цифр у рядку\n 3 - Перетворення рядка на число\n"
			<< " 4 - Сума послідовності чисел\n 5 - Підстановки в рядку\n"
			<< " 6 - Форматоване виведення цілих чисел\n 7 - Відшукання найдовшого слова\n"
			<< " 8 - Завершення роботи\n>>>> ";
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
		default: cout << "До побачення!\n";
		}
		system("pause");
	}
	while (answer > 0 && answer < 8);
	return 0;
}