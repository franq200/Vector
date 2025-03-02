#pragma once
#include <stdexcept>

template <typename T> class Vector
{
public:
	~Vector();
	void PushBack(const T& value);
	void Reserve(size_t newCap);
	void Resize(size_t newSize);
	void ShrinkToFit();
	size_t Capacity() const;
	size_t Size() const;
	T* Erase(T* pos);
	T& At(size_t pos);
	T* Begin();
	T* End();

	T& operator[](size_t pos);
	Vector<T>& operator=(const Vector<T>& other);
	bool operator==(const Vector<T>& other);
private:
	T* m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
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
inline void Vector<T>::Reserve(size_t newCap)
{
	if (newCap > m_capacity)
	{
		T* new_data = new T[newCap];
		for (size_t i = 0; i < m_size; ++i)
		{
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = newCap;
	}
}

template<typename T>
inline void Vector<T>::Resize(size_t newSize)
{
	if (newSize < m_size)
	{
		m_size = newSize;
		T* new_data = new T[m_size]; // skopiowane z reserve
		for (size_t i = 0; i < m_size; ++i)
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
		for (size_t i = m_size; i < newSize; ++i)
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
		for (size_t i = 0; i < m_size; ++i)
		{
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = m_size;
	}
}

template<typename T>
inline size_t Vector<T>::Capacity() const
{
	return m_capacity;
}

template<typename T>
inline size_t Vector<T>::Size() const
{
	return m_size;
}

template<typename T>
inline T* Vector<T>::Erase(T* pos)
{
	size_t index = pos - m_data;
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}

	for (size_t i = index; i < m_size - 1; ++i)
	{
		m_data[i] = m_data[i + 1];
	}
	m_size = index;
	m_capacity = m_size;
	return m_data + index;
}

template<typename T>
inline T& Vector<T>::At(size_t pos)
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
inline T& Vector<T>::operator[](size_t pos)
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

		for (size_t i = 0; i < m_size; ++i)
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
	for (size_t i = 0; i < m_size; ++i)
	{
		if (m_data[i] != other.m_data[i])
		{
			return false;
		}
	}
	return true;
}
