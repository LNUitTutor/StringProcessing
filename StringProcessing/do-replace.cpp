#include "process-procedures.h"

char* Replace(char* source, char what, const char* by)
{
	// порахуємо, скільки разів трапляється шукана літера
	// водночас дізнаємося довжину рядка
	unsigned counter = 0;
	unsigned length = 0;
	while (source[length] != '\0')
	{
		if (source[length] == what) ++counter;
		++length;
	}
	// виділимо достатньо місця для нового рядка
	unsigned by_len = strlen(by);
	char* new_line = new char[length + 1 + (by_len - 1) * counter];
	unsigned dest = 0;
	for (unsigned i = 0; i < length; ++i)  // і виконаємо заміни
	{
		if (source[i] != what) new_line[dest++] = source[i];
		else
		{
			for (unsigned j = 0; j < by_len; ++j) new_line[dest++] = by[j];
		}
	}
	new_line[dest] = '\0';   // термінальна літера
	return new_line;
}

void DoReplace()
{
	cout << "\n *Заміна літери '+' в рядку групою літер ' plus'*\n\n";
	char cpp[] = "I like C++";
	cout << "Початковий рядок: " << cpp << '\n';
	char* res = Replace(cpp, '+', " plus");
	cout << "Рядок після підстановки: " << res << '\n';
	delete[] res;
	return;
}
