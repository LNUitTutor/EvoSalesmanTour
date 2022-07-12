#pragma once
#include <atltypes.h>

// ���� ���������� ����������� m_order �������� ���, ���������� m_towns ���� ������ ����.
// �� ������ "���������" ��� ��������� ����� ����, �쳺 ��������� � ������ ������� ��������.
// ���� ��������� �� ��������.

class Tour
{
private:
	static CPoint* m_towns;// ���������� ���
	static int m_towns_count;

	int* m_order;          // ������������ ������
	double m_length;          // �������� �������
	void CalcLength();     // ����� ���������� �������
	// ����� ��� ������ ������������, ��������� ����
	Tour(int* perm) :m_order(perm) { CalcLength(); }
public:
	// ����� ���������� ����� �������� ������������ �����
	static void InitTowns(CPoint* T, int n)
	{
		m_towns = T; m_towns_count = n;
	}
	~Tour() { delete[] m_order; }
	// �� ������������� ������� �������� - ����������: m_order[i] = i
	// �� ������� ����� ��������� ������� �������� ���������
	Tour(bool permuted = false);
	// ��������� �� ��������� ������ ��� ������ � ������������
	Tour(const Tour& T);
	Tour& operator=(const Tour& T);
	// ����� ��������� ������� ��������� ��� ��������� ��������
	double Length() const { return m_length; }
	// ������ ������� ����: ���� � �������
	Tour Mutate();
	Tour Rotate();
	// ��������� ���������� ������������ ���������� �����
	bool operator<(const Tour& other) const { return this->m_length < other.m_length; }

	// ��������� - ���������� ����������� ���
	CPoint* Route() const;
};
