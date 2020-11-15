////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 3: Source file
// 1. Complete the implementation of Ordered
// 2. Add a new class, OrderedSet, using class inheritance
////////////////////////////////////////////////////////////////////////////////
#include "hw3.h"

#include <iostream>
#include <limits>

Ordered::Ordered() {
	ordered_list = nullptr;
}

Ordered::~Ordered() {
	delete[] ordered_list;
}

void Ordered::add(int v) {
	if (m_size == 0) {
		ordered_list = new int[1]{ v };
		m_size += 1;
		return;
	}

	int* temp_list = new int[m_size];
	for (int i = 0; i < m_size; i++) {
		temp_list[i] = ordered_list[i];
	}
	delete[] ordered_list;
	ordered_list = new int[m_size + 1];
	bool is_inserted = false;
	int index{ 0 };
	while (index < m_size + 1) {
		if (!is_inserted && v < temp_list[index]) {
			ordered_list[index] = v;
			is_inserted = true;
		}
		else if (!is_inserted && index == m_size) {
			ordered_list[index] = v;
			is_inserted = true;
		}
		else {
			(is_inserted) ? ordered_list[index] = temp_list[index - 1] : ordered_list[index] = temp_list[index];
		}
		index++;
	}
	delete[] temp_list;
	m_size++;
}

void Ordered::remove(int index) {
	int* temp_list = new int[m_size];
	for (int i = 0; i < m_size; i++) {
		temp_list[i] = ordered_list[i];
	}
	delete[] ordered_list;
	ordered_list = new int[m_size - 1];
	bool is_removed = false;
	for (int i = 0; i < m_size; i++) {
		if (i == index) {
			is_removed = true;
			continue;
		}
		(is_removed) ? ordered_list[i - 1] = temp_list[i] : ordered_list[i] = temp_list[i];
	}
	delete[] temp_list;
	m_size--;
}

void Ordered::add(int* arr, int size) {
	int* temp_list = new int[m_size];
	for (int i = 0; i < m_size; i++) {
		temp_list[i] = ordered_list[i];
	}
	delete[] ordered_list;
	ordered_list = new int[m_size + size];

	for (int i = 0; i < size; i++) {		// arr 리스트 정렬
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		if (min != i) {
			int temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}

	int add_index = 0;
	int cur_add_index = 0;
	int index = 0;
	while (index < m_size) {
		cur_add_index = 0;
		for (int temp_i = add_index; temp_i < size; temp_i++) {
			if (arr[temp_i] > temp_list[index]) {
				break;
			}
			cur_add_index++;
		}
		for (int i = 0; i < cur_add_index; i++) {
			ordered_list[index + add_index + i] = arr[add_index + i];
		}
		add_index += cur_add_index;
		ordered_list[index + add_index] = temp_list[index];
		index++;
	}
	if (add_index < size) {
		int rest = size - add_index;
		for (int i = 0; i < rest; i++) {
			ordered_list[m_size + add_index + i] = arr[add_index + i];
		}
	}
	m_size += size;
	delete[] temp_list;
}

int Ordered::operator[](int index) {
	return ordered_list[index];
}

bool Ordered::operator>>(int v) {
	bool is_in = false;
	for (int i = 0; i < m_size; i++) {
		if (ordered_list[i] == v) {
			is_in = true;
			break;
		}
	}
	return is_in;
}

//////////////////// OrderedSet ////////////////////

void OrderedSet::add(int v) {
	if (m_size == 0) {
		ordered_list = new int[1]{ v };
		m_size += 1;
		return;
	}

	int* temp_list = new int[m_size];
	for (int i = 0; i < m_size; i++) {
		if (ordered_list[i] == v) {
			delete[] temp_list;
			return;
		}
		temp_list[i] = ordered_list[i];
	}
	delete[] ordered_list;
	ordered_list = new int[m_size + 1];
	bool is_inserted = false;
	int index{ 0 };
	while (index < m_size + 1) {
		if (!is_inserted && v < temp_list[index]) {
			ordered_list[index] = v;
			is_inserted = true;
		}
		else if (!is_inserted && index == m_size) {
			ordered_list[index] = v;
			is_inserted = true;
		}
		else {
			(is_inserted) ? ordered_list[index] = temp_list[index - 1] : ordered_list[index] = temp_list[index];
		}
		index++;
	}
	delete[] temp_list;
	m_size++;
}

void OrderedSet::add(int* arr, int size) {
	for (int i = 0; i < size; i++) {		// arr 리스트 정렬
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		if (min != i) {
			int temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}

	int* temp_list = new int[m_size];
	for (int i = 0; i < m_size; i++) {
		temp_list[i] = ordered_list[i];
	}
	delete[] ordered_list;
	ordered_list = new int[m_size + size];

	int add_index = 0;
	int cur_add_index = 0;
	int index = 0;
	while (index < m_size) {
		cur_add_index = 0;
		for (int temp_i = add_index; temp_i < size; temp_i++) {
			if (arr[temp_i] > temp_list[index]) {
				break;
			}
			cur_add_index++;
		}
		for (int i = 0; i < cur_add_index; i++) {
			ordered_list[index + add_index + i] = arr[add_index + i];
		}
		add_index += cur_add_index;
		ordered_list[index + add_index] = temp_list[index];
		index++;
	}
	if (add_index < size) {
		int rest = size - add_index;
		for (int i = 0; i < rest; i++) {
			ordered_list[m_size + add_index + i] = arr[add_index + i];
		}
	}

	// 중복 원소 제거
	int duplicated = 0;
	delete[] temp_list;
	temp_list = new int[m_size + size];
	for (int i = 0; i < m_size + size; i++) {
		if (i == 0) {
			temp_list[i] = ordered_list[i];
			continue;
		}
		if (ordered_list[i] == ordered_list[i - 1]) {
			duplicated++;
		}
		else {
			temp_list[i - duplicated] = ordered_list[i];
		}
	}

	m_size += size - duplicated;
	delete[] ordered_list;
	ordered_list = new int[m_size];
	for (int i = 0; i < m_size; i++) {
		ordered_list[i] = temp_list[i];
	}
	delete[] temp_list;
}