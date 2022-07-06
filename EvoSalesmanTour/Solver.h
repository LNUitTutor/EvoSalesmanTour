#pragma once
#include <set>
#include <functional>
#include "Tour.h"

class Solver
{
private:
	// ���������� ���, �� ����� �������
	CPoint* m_towns;
	int m_towns_count;

	// ����� ��������� (�����������������)
	int m_population_size;
	// ʳ������ ������� �������
	int m_mutation_number;
	// ʳ������ ������� ��������
	int m_rotation_number;
	// ����������� ������� �������
	int m_generations_limit;
	// ��� ��������� ����������� ��������������� �� ���������� ������� ����
	std::multiset<Tour> m_population;
	// ��������� �����������������
	Tour* m_top_tours;
	// ����������� ��������� ��������� - ������ ���������� ������������ ������ ���
	void StartPopulation();
	// ����������� ������ ��������
	void NextGeneration();
	// �������� ����
	void Survive();
public:
	// ������������ ��� ��� ���������
	std::function<void(int, double)> m_show;
	Solver(CPoint* map, int size);
	Solver(CPoint* map, int size, int population_size, int mutations, int turns, int max_generation);
	~Solver() { delete[] m_top_tours; }
	// ������ ���������
	int Solve(const bool& stopRequired);
	// ��������� ����'����
	Tour& Best() const { return m_top_tours[0]; }
};

