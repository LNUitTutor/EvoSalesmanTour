#pragma once
#include <set>
#include <functional>
#include "Tour.h"

class Solver
{
private:
	// координати міст, які треба відвідати
	CPoint* m_towns;
	int m_towns_count;

	// Розмір популяції (найпристосованіших)
	int m_population_size;
	// Кількість простих мутацій
	int m_mutation_number;
	// Кількість мутацій напрямку
	int m_rotation_number;
	// Максимальна кількість поколінь
	int m_generations_limit;
	// Усе потомство автоматично сортуватиметься за зростанням довжини туру
	std::multiset<Tour> m_population;
	// Популяція найпристосованіших
	Tour* m_top_tours;
	// генерування початкової популяції - масиву випадкових перестановок номерів міст
	void StartPopulation();
	// генерування нового покоління
	void NextGeneration();
	// Природній відбір
	void Survive();
public:
	// інформування про хід обчислень
	std::function<void(int, double)> m_show;
	Solver(CPoint* map, int size);
	Solver(CPoint* map, int size, int population_size, int mutations, int turns, int max_generation);
	~Solver() { delete[] m_top_tours; }
	// запуск обчислень
	int Solve(const bool& stopRequired);
	// знайдений розв'язок
	Tour& Best() const { return m_top_tours[0]; }
};

