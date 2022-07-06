#include "stdafx.h"
#include "Tour.h"
#include <algorithm>
#include <random>
#include <stdexcept>

CPoint* Tour::m_towns = nullptr;
int Tour::m_towns_count = 0;

// Довжина маршруту - сума довжин прямолінійних відрізків між сусідніми містами маршруту.
// Довжина відрізку - відстань між точками на координатній площині.
void Tour::CalcLength()
{
	if (m_towns == nullptr || m_towns_count == 0)
	{
		m_length = 0.0;
		throw std::runtime_error(
			"The static members of Tour class are not initialized properly");
	}
	m_length = sqrt(pow(m_towns[m_order[m_towns_count - 1]].x - m_towns[m_order[0]].x, 2)
		+ pow(m_towns[m_order[m_towns_count - 1]].y - m_towns[m_order[0]].y, 2));
	for (int i = 1; i < m_towns_count; ++i)
		m_length += sqrt(pow(m_towns[m_order[i - 1]].x - m_towns[m_order[i]].x, 2)
		    + pow(m_towns[m_order[i - 1]].y - m_towns[m_order[i]].y, 2));
}

// За замовчуванням міста відвідують послідовно від першого до останнього
// або Випадкова перестановка послідовності міст
Tour::Tour(bool permuted)
{
	m_order = new int[m_towns_count];
	for (int i = 0; i < m_towns_count; ++i) m_order[i] = i;
	if (permuted) std::random_shuffle(m_order, m_order + m_towns_count);
	CalcLength();
}

Tour::Tour(const Tour& T) :m_length(T.m_length)
{
	m_order = new int[m_towns_count];
	for (int i = 0; i < m_towns_count; ++i) m_order[i] = T.m_order[i];
}

Tour& Tour::operator=(const Tour& T)
{
	if (this != &T)
	{
		for (int i = 0; i < m_towns_count; ++i) m_order[i] = T.m_order[i];
		m_length = T.m_length;
	}
	return *this;
}

// Проста мутація: обмін місцями двох випадкових міст у послідовності
Tour Tour::Mutate()
{
	int* ord = new int[m_towns_count];
	for (int i = 0; i < m_towns_count; ++i) ord[i] = m_order[i];
	int k = std::rand() % m_towns_count;
	int n = std::rand() % m_towns_count;
	int toSwap = ord[k];
	ord[k] = ord[n];
	ord[n] = toSwap;
	return Tour(ord);
}

// Мутація напрямку: змінює на протилежний напрям руху між двома випадковими містами
Tour Tour::Rotate()
{
	int* ord = new int[m_towns_count];
	for (int i = 0; i < m_towns_count; ++i) ord[i] = m_order[i];
	int k = std::rand() % m_towns_count;
	int n = std::rand() % m_towns_count;
	if (k == n) return Tour(true);
	while (k > n)
	{
		int toSwap = ord[k];
		ord[k] = ord[n];
		ord[n] = toSwap;
		++k; k %= m_towns_count;
		--n; n = (n < 0) ? m_towns_count - 1 : n;
	}
	while (k < n)
	{
		int toSwap = ord[k];
		ord[k] = ord[n];
		ord[n] = toSwap;
		++k; --n;
	}
	return Tour(ord);
}

CPoint* Tour::Route() const
{
	CPoint* R = new CPoint[m_towns_count + 1];
	for (int i = 0; i < m_towns_count; ++i)
		R[i] = m_towns[m_order[i]];
	R[m_towns_count] = R[0];
	return R;
}
