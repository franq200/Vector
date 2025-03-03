#pragma once
#include <stdexcept>
#include <limits>

using vectorSize = size_t;

template <typename T> class Vector
{
public:
	~Vector();
	void PushBack(const T& value);
	void Reserve(vectorSize newCap);
	void Resize(vectorSize newSize);
	void ShrinkToFit();
	vectorSize Capacity() const;
	vectorSize Size() const;
	T* Erase(T* pos);
	T& At(vectorSize pos);
	T* Begin();
	T* End();

	T& operator[](vectorSize pos);
	Vector<T>& operator=(const Vector<T>& other);
	bool operator==(const Vector<T>& other);
private:
	T* m_data = nullptr;
	vectorSize m_size = 0;
	vectorSize m_capacity = 0;
	vectorSize m_maxSize = std::numeric_limits<vectorSize>::max();
};

template<typename T>
inline Vector<T>::~Vector()
{
	delete[] m_data;
}

template<typename T>
inline void Vector<T>::PushBack(const T& value)
{
	if (m_size == m_capacity)
	{
		Reserve(m_capacity == 0 ? 1 : m_capacity * 2);
	}
	m_data[m_size++] = value;
}

template<typename T>
inline void Vector<T>::Reserve(vectorSize newCap)
{
	if (newCap > m_maxSize)
	{
		throw std::length_error("new capacity is bigger than max size of vector");
	}
	if (newCap > m_capacity)
	{
		T* new_data = new T[newCap];
		for (vectorSize i = 0; i < m_size; ++i)
		{
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = newCap;
	}
}

template<typename T>
inline void Vector<T>::Resize(vectorSize newSize)
{
	if (newSize > m_maxSize)
	{
		throw std::length_error("new capacity is bigger than max size of vector");
	}
	if (newSize < m_size)
	{
		m_size = newSize;
		T* new_data = new T[m_size]; // skopiowane z reserve
		for (vectorSize i = 0; i < m_size; ++i)
		{
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
	}
	else if (newSize > m_size)
	{
		if (newSize > m_capacity)
		{
			Reserve(newSize);
		}
		for (vectorSize i = m_size; i < newSize; ++i)
		{
			m_data[i] = T();
		}
		m_size = newSize;
	}
}

template<typename T>
inline void Vector<T>::ShrinkToFit()
{
	if (m_size < m_capacity)
	{
		T* new_data = new T[m_size]; // skopiowane z reserve
		for (vectorSize i = 0; i < m_size; ++i)
		{
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = m_size;
	}
}

template<typename T>
inline vectorSize Vector<T>::Capacity() const
{
	return m_capacity;
}

template<typename T>
inline vectorSize Vector<T>::Size() const
{
	return m_size;
}

template<typename T>
inline T* Vector<T>::Erase(T* pos)
{
	vectorSize index = pos - m_data;
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}

	for (vectorSize i = index; i < m_size - 1; ++i)
	{
		m_data[i] = m_data[i + 1];
	}
	m_size = index;
	m_capacity = m_size;
	return m_data + index;
}

template<typename T>
inline T& Vector<T>::At(vectorSize pos)
{
	if (pos >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[pos];
}

template<typename T>
inline T* Vector<T>::Begin()
{
	return m_data;
}

template<typename T>
inline T* Vector<T>::End()
{
	return m_data + m_size;
}

template<typename T>
inline T& Vector<T>::operator[](vectorSize pos)
{
	return m_data[pos];
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		delete[] m_data;

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = new T[m_capacity];

		for (vectorSize i = 0; i < m_size; ++i)
		{
			m_data[i] = other.m_data[i];
		}
	}
	return *this;
}

template<typename T>
inline bool Vector<T>::operator==(const Vector<T>& other)
{
	if (m_size != other.m_size)
	{
		return false;
	}
	for (vectorSize i = 0; i < m_size; ++i)
	{
		if (m_data[i] != other.m_data[i])
		{
			return false;
		}
	}
	return true;
}
