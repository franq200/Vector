#pragma once
#include <stdexcept>
#include <limits>

using VectorSize = size_t;

template <typename T> class Vector final
{
public:
	struct Iterator
	{
		Iterator& operator ++();
		Iterator& operator --();
		T& operator*();
	private:
		T* m_value;
	};
	Vector() = default;
	Vector(const Vector<T>& other);
	Vector(Vector&& other);
	~Vector();
	void PushBack(const T& value);
	void Reserve(VectorSize newCap);
	void Resize(VectorSize newSize);
	void ShrinkToFit();
	VectorSize Capacity() const;
	VectorSize Size() const;
	T* Erase(T* pos);
	T& At(VectorSize pos);
	const T& At(VectorSize pos) const;
	T* Begin() const;
	T* End() const;

	T& operator[](VectorSize pos);
	const T& operator[](VectorSize pos) const;
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);
	bool operator==(const Vector<T>& other) const;
private:
	T* m_data = nullptr;
	VectorSize m_size = 0;
	VectorSize m_capacity = 0;
	VectorSize m_maxSize = std::numeric_limits<VectorSize>::max();
};

template<typename T>
inline Vector<T>::Vector(const Vector<T>& other)
{
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	m_data = new T[m_capacity];

	for (VectorSize i = 0; i < m_size; ++i)
	{
		m_data[i] = other.m_data[i];
	}
}

template<typename T>
inline Vector<T>::Vector(Vector&& other)
{
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	m_data = other.m_data;
	other.m_data = nullptr;
}

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
inline void Vector<T>::Reserve(VectorSize newCap)
{
	if (newCap > m_maxSize)
	{
		throw std::length_error("new capacity is bigger than max size of vector");
	}
	if (newCap > m_capacity)
	{
		T* new_data = new T[newCap];
		for (VectorSize i = 0; i < m_size; ++i)
		{
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = newCap;
	}
}

template<typename T>
inline void Vector<T>::Resize(VectorSize newSize)
{
	if (newSize > m_maxSize)
	{
		throw std::length_error("new capacity is bigger than max size of vector");
	}
	if (newSize < m_size)
	{
		m_size = newSize;
		T* new_data = new T[m_size]; // skopiowane z reserve
		for (VectorSize i = 0; i < m_size; ++i)
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
		for (VectorSize i = m_size; i < newSize; ++i)
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
		for (VectorSize i = 0; i < m_size; ++i)
		{
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = m_size;
	}
}

template<typename T>
inline VectorSize Vector<T>::Capacity() const
{
	return m_capacity;
}

template<typename T>
inline VectorSize Vector<T>::Size() const
{
	return m_size;
}

template<typename T>
inline T* Vector<T>::Erase(T* pos)
{
	VectorSize index = pos - m_data;
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}

	for (VectorSize i = index; i < m_size - 1; ++i)
	{
		m_data[i] = m_data[i + 1];
	}
	m_size--;
	return m_data + index;
}

template<typename T>
inline T& Vector<T>::At(VectorSize pos)
{
	if (pos >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[pos];
}

template<typename T>
inline const T& Vector<T>::At(VectorSize pos) const
{
	if (pos >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[pos];
}

template<typename T>
inline T* Vector<T>::Begin() const
{
	return m_data;
}

template<typename T>
inline T* Vector<T>::End() const
{
	return m_data + m_size;
}

template<typename T>
inline T& Vector<T>::operator[](VectorSize pos)
{
	return m_data[pos];
}

template<typename T>
inline const T& Vector<T>::operator[](VectorSize pos) const
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

		for (VectorSize i = 0; i < m_size; ++i)
		{
			m_data[i] = other.m_data[i];
		}
	}
	return *this;
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
	if (this != &other)
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;
		other.m_data = nullptr;
	}
	return *this;
}

template<typename T>
inline bool Vector<T>::operator==(const Vector<T>& other) const
{
	if (m_size != other.m_size)
	{
		return false;
	}
	for (VectorSize i = 0; i < m_size; ++i)
	{
		if (m_data[i] != other.m_data[i])
		{
			return false;
		}
	}
	return true;
}

template<typename T>
inline Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
	// TODO: insert return statement here
}

template<typename T>
inline Vector<T>::Iterator& Vector<T>::Iterator::operator--()
{
	// TODO: insert return statement here
}

template<typename T>
inline T& Vector<T>::Iterator::operator*()
{
	return 
}
