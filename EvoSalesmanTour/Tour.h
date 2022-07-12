#pragma once
#include <atltypes.h>

// Клас інкапсулює послідовність m_order відвідання міст, координати m_towns яких задано зовні.
// Має методи "мутування" для створення нових турів, вміє обчислити і зберігає довжину маршруту.
// Тури порівнюють за довжиною.

class Tour
{
private:
	static CPoint* m_towns;// координати міст
	static int m_towns_count;

	int* m_order;          // перестановка номерів
	double m_length;          // відповідна довжина
	void CalcLength();     // метод обчислення довжини
	// новий тур містить перестановку, обчислену зовні
	Tour(int* perm) :m_order(perm) { CalcLength(); }
public:
	// метод викликають перед початком використання класу
	static void InitTowns(CPoint* T, int n)
	{
		m_towns = T; m_towns_count = n;
	}
	~Tour() { delete[] m_order; }
	// за замовчуванням порядок відвідання - послідовний: m_order[i] = i
	// за бажання можна перемішати порядок відвідання випадково
	Tour(bool permuted = false);
	// копіювання та присвоєння потрібні для роботи з контейнерами
	Tour(const Tour& T);
	Tour& operator=(const Tour& T);
	// метод отримання довжини повідомляє вже обчислене значення
	double Length() const { return m_length; }
	// методи мутації турів: обмін і поворот
	Tour Mutate();
	Tour Rotate();
	// оператори полегшують використання екземплярів класу
	bool operator<(const Tour& other) const { return this->m_length < other.m_length; }

	// Результат - побудована послідовність міст
	CPoint* Route() const;
};
