#include "process-procedures.h"
#include <string>
#include <sstream>

using std::string;

void LongestByArray()
{
	const int text_size = 256;
	char text[text_size] = { 0 }; // місце для майбутнього тексту
	cout << "Введіть текст (до 255 літер): ";
	cin.getline(text, text_size);
	if (cin.failbit > 0)
	{
		// текст завеликий очищаємо потік від залишку рядка
		cin.clear();
		while (cin.get() != '\n') continue;
	}
	cout << "\nВи ввели: " << text << '\n';
	// політерне опрацювання
	int start = 0;             // початок найдовшого слова
	int max_length = 0;            // його довжина
	int curr = 0;              // початок тексту
	while (text[curr] != '\0') // опрацювання до термінального символу
	{
		int pos = curr;        // початок чергового слова
		while (text[curr] != '\0' && text[curr] != ' ')	++curr; // шукаємо його закінчення
		int length = curr - pos;  // довжина чергового слова
		if (length > max_length)
		{                      // знайшли довше
			max_length = length;
			start = pos;
		}
		while (text[curr] != '\0' && text[curr] == ' ') ++curr; // шукаємо наступне слово
	}
	// новий рядок міститиме найдовше слово
	char * longestWord = new char[max_length + 1];
	for (int i = 0; i < max_length; ++i) longestWord[i] = text[start + i];
	longestWord[max_length] = '\0';
	cout << "Найдовше слово: " << longestWord << '\n';
	delete[] longestWord;
}

void LongestByString()
{
	string text;
	cout << "Введіть текст: ";
	getline(cin, text);
	cout << "\nВи ввели: " << text << '\n';
	// опрацювання за допомогою потоку літер
	std::istringstream stream(text);
	string word, max_word;
	int max_length = 0;
	while (stream >> word) // оператор введення розпізнає пропуски
	{
		int length = word.length();
		if (length > max_length)
		{
			max_length = length;
			max_word = word;
		}
	}
	cout << "Найдовше слово: " << max_word << '\n';
}

void PrintLongest()
{
	cout << "\n *Відшукання найдовшого в тексті слова*\n";
	cout << "\n-З використанням рядка в стилі С-\n";
	LongestByArray();
	cout << "\n-З використанням рядка-контейнера-\n";
	LongestByString();
}