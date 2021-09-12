#ifndef KNIGHTS_AND_MERCHANTS_ARRAY_H
#define KNIGHTS_AND_MERCHANTS_ARRAY_H

#include <cassert>
#include <cstdlib>
#include <memory>

#include "io/FileIo.h"

using std::unique_ptr;
using std::make_unique;

template<class T>
class Array {
protected:
	Array() {}
public:

	static const int INVALID_ID;

	Array(const int p0);
	Array(const int p0, const int p4, bool (*p8)(const T &), void (*p12)(T &));
	~Array();

	void reset();

	int addSlot();

	T & getElement(const int i);
	const T & getElement(const int i) const;

	void removeSlot(int id);

	bool read(knights_and_merchants::io::FileIo & fileIO);
	bool resetNRead(knights_and_merchants::io::FileIo & fileIO);

	void searchFreeSlot();

	int i0_capacity;
	int i4_elementCount;
	int i8_firstFreeID;
	int i12;
	int i16_elementSize;
	unique_ptr<T[]> i20;
	bool (*i24)(const T &);
	void (*i28)(T &);
};

template<class T>
const int Array<T>::INVALID_ID = -1;

template<class T>
Array<T>::Array(const int p0)
	: Array<T> { p0, sizeof(T), T::isUsed, T::setUnused }
{

}

template<class T>
Array<T>::Array(const int p0, const int p4, bool (*p8)(const T &), void (*p12)(T &))
{
	reset();

	i20 = make_unique<T[]>(p0);

	i0_capacity = p0;
	i16_elementSize = p4;
	i24 = p8;
	i28 = p12;

	if (i28 != nullptr)
		for (int i = 0; i < i0_capacity; ++i)
			i28(getElement(i));
}

template<class T>
Array<T>::~Array()
{
	reset();
}

template<class T>
void Array<T>::reset()
{
	i0_capacity = 0;
	i4_elementCount = 0;
	i8_firstFreeID = 0;
	i12 = 0;
	i16_elementSize = 0;
	i20 = nullptr;
	i24 = nullptr;
	i28 = nullptr;
}

template<class T>
T & Array<T>::getElement(const int i)
{
	assert(i >= 0 && i < i0_capacity);
	return i20[i];
}

template<class T>
const T & Array<T>::getElement(const int i) const
{
	assert(i >= 0 && i < i0_capacity);
	return i20[i];
}

template<class T>
void Array<T>::removeSlot(int id)
{
	i28(getElement(id));

	i4_elementCount--;

	if (id < i8_firstFreeID)
		i8_firstFreeID = id;

	if (i12 == id) {
		while (!i24(getElement(i12))) {
			if (i12 <= 0)
				break;

			i12--;
		}
	}
}

template<class T>
bool Array<T>::read(knights_and_merchants::io::FileIo & fileIO)
{
    fileIO.read(&i0_capacity, 4);
    fileIO.read(&i4_elementCount, 4);
    fileIO.read(&i8_firstFreeID, 4);
    fileIO.read(&i12, 4);
    fileIO.read(&i16_elementSize, 4);
	//if (!fileIO.read(&i0_capacity, 4) || !fileIO.read(&i4_elementCount, 4) || !fileIO.read(&i8_firstFreeID, 4) || !fileIO.read(&i12, 4) || !fileIO.read(&i16_elementSize, 4))
	//	return false;

	i20 = make_unique<T[]>(i0_capacity);

	for (int i = 0; i < i0_capacity; ++i)
		i20[i].read(fileIO);

	return true;
	//return fileIO.read(i20.get(), i0_capacity * i16_elementSize);
}

template<class T>
bool Array<T>::resetNRead(knights_and_merchants::io::FileIo & fileIO)
{
	reset();
	return read(fileIO);
}

template<class T>
int Array<T>::addSlot()
{
	if (i4_elementCount >= i0_capacity)
		return -1;

	if (i12 < i8_firstFreeID)
		i12 = i8_firstFreeID;

	int result { i8_firstFreeID };

	i8_firstFreeID++;
	i4_elementCount++;
	searchFreeSlot();

	return result;
}

template<class T>
void Array<T>::searchFreeSlot()
{
	if (i4_elementCount >= i0_capacity)
		return;

	while (i24(getElement(i8_firstFreeID))) {
		if (i8_firstFreeID >= i0_capacity - 1)
			break;

		i8_firstFreeID++;
	}
}

#endif