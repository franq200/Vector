#pragma once
#include <stdexcept>
#include <limits>
#include <iterator>

using VectorSize = size_t;

template <typename T> class Vector final
{
public:
	class const_Iterator;
	struct Iterator
	{
		using iterator_category = std::random_access_iterator_tag;
		using value_type        = T;
		using difference_type   = std::ptrdiff_t;
		using pointer           = T*;
		using reference         = T&;

		explicit Iterator(T* value) : m_value(value) {}
		Iterator operator ++(int);
		Iterator& operator ++();
		Iterator operator --(int);
		Iterator& operator --();
		VectorSize operator -(const Iterator& it) const;
		Iterator operator +(VectorSize pos) const;
		Iterator operator -(VectorSize pos) const;
		Iterator& operator+=(difference_type pos);
		Iterator& operator-=(difference_type pos);
		T& operator[](difference_type pos) const;
		bool operator<(const Iterator& it) const;
		bool operator>(const Iterator& it) const;
		bool operator<=(const Iterator& it) const;
		bool operator>=(const Iterator& it) const;
		bool operator !=(const Iterator& it) const;
		bool operator ==(const Iterator& it) const;
		T& operator*() const;
		T* operator->() const;
		operator const_Iterator() const { return const_Iterator(m_value); }

	private:
		T* m_value;
	};
	struct const_Iterator
	{
		using iterator_category = std::contiguous_iterator_tag;
		using value_type        = T;
		using difference_type   = VectorSize;
		using pointer           = T*;
		using reference         = T&;

		explicit const_Iterator(T* value) : m_value(value) {}
		const_Iterator operator ++(int);
		const_Iterator& operator ++();
		const_Iterator operator --(int);
		Iterator& operator --();
		VectorSize operator -(const const_Iterator& it) const;
		const_Iterator operator +(VectorSize pos) const;
		const_Iterator operator -(VectorSize pos) const;
		const_Iterator& operator+=(difference_type pos);
		const_Iterator& operator-=(difference_type pos);
		T& operator[](difference_type pos) const;
		bool operator<(const Iterator& it) const;
		bool operator>(const Iterator& it) const;
		bool operator<=(const Iterator& it) const;
		bool operator>=(const Iterator& it) const;
		bool operator !=(const const_Iterator& it) const;
		bool operator ==(const const_Iterator& it) const;
		const T& operator*() const;
		const T* operator->() const;

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
	Iterator Erase(Iterator pos);
	T& At(VectorSize pos);
	const T& At(VectorSize pos) const;
	Iterator begin() const;
	const_Iterator cbegin() const;
	Iterator end() const;
	const_Iterator cend() const;

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
typename Vector<T>::Iterator Vector<T>::Erase(Vector<T>::Iterator pos)
{
	VectorSize index = pos - begin();
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}

	for (VectorSize i = index; i < m_size - 1; ++i)
	{
		m_data[i] = m_data[i + 1];
	}
	m_size--;
	return Vector<T>::Iterator(m_data + index);
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
typename Vector<T>::Iterator Vector<T>::begin() const
{
	return Vector<T>::Iterator(m_data);
}

template<typename T>
typename Vector<T>::const_Iterator Vector<T>::cbegin() const
{
	return const_Iterator(begin());
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::end() const
{
	return Vector<T>::Iterator(m_data + m_size);
}

template<typename T>
typename Vector<T>::const_Iterator  Vector<T>::cend() const
{
	return const_Iterator(end());
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
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
{
	return Vector<T>::Iterator(m_value++);
}

template<typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
	m_value++;
	return *this;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int)
{
	return Vector<T>::Iterator(m_value--);
}

template<typename T>
inline Vector<T>::Iterator& Vector<T>::Iterator::operator--()
{
	m_value--;
	return *this;
}

template<typename T>
inline VectorSize Vector<T>::Iterator::operator-(const Iterator& it) const
{
	return m_value - it.m_value;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator+(VectorSize pos) const
{
	return Vector<T>::Iterator(m_value+pos);
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator-(VectorSize pos) const
{
	return Vector<T>::Iterator(m_value - pos);
}

template<typename T>
inline Vector<T>::Iterator& Vector<T>::Iterator::operator+=(difference_type pos)
{
	m_value += pos;
	return *this;
}

template<typename T>
inline Vector<T>::Iterator& Vector<T>::Iterator::operator-=(difference_type pos)
{
	m_value -= pos;
	return *this;
}

template<typename T>
inline T& Vector<T>::Iterator::operator[](difference_type pos) const
{
	return m_value[pos];
}

template<typename T>
inline bool Vector<T>::Iterator::operator<(const Iterator& it) const
{
	return m_value < it.m_value;
}

template<typename T>
inline bool Vector<T>::Iterator::operator>(const Iterator& it) const
{
	return m_value > it.m_value;
}

template<typename T>
inline bool Vector<T>::Iterator::operator<=(const Iterator& it) const
{
	return m_value <= it.m_value;
}

template<typename T>
inline bool Vector<T>::Iterator::operator>=(const Iterator& it) const
{
	return m_value >= it.m_value;
}

template<typename T>
inline bool Vector<T>::Iterator::operator!=(const Iterator& it) const
{
	return m_value != it.m_value;
}

template<typename T>
inline bool Vector<T>::Iterator::operator==(const Iterator& it) const
{
	return m_value == it.m_value;
}

template<typename T>
inline T& Vector<T>::Iterator::operator*() const
{
	return *m_value;
}

template<typename T>
inline T* Vector<T>::Iterator::operator->() const
{
	return m_value;
}


template<typename T>
typename Vector<T>::const_Iterator Vector<T>::const_Iterator::operator++(int)
{
	return Vector<T>::const_Iterator(m_value++);
}

template<typename T>
typename Vector<T>::const_Iterator& Vector<T>::const_Iterator::operator++()
{
	m_value++;
	return *this;
}

template<typename T>
typename Vector<T>::const_Iterator Vector<T>::const_Iterator::operator--(int)
{
	return Vector<T>::const_Iterator(m_value--);
}

template<typename T>
inline Vector<T>::Iterator& Vector<T>::const_Iterator::operator--()
{
	m_value--;
	return *this;
}

template<typename T>
inline VectorSize Vector<T>::const_Iterator::operator-(const const_Iterator& it) const
{
	return m_value - it.m_value;
}

template<typename T>
typename Vector<T>::const_Iterator Vector<T>::const_Iterator::operator+(VectorSize pos) const
{
	return Vector<T>::const_Iterator(m_value + pos);
}

template<typename T>
typename Vector<T>::const_Iterator Vector<T>::const_Iterator::operator-(VectorSize pos) const
{
	return Vector<T>::const_Iterator(m_value - pos);
}

template<typename T>
inline Vector<T>::const_Iterator& Vector<T>::const_Iterator::operator+=(difference_type pos)
{
	m_value += pos;
	return *this;
}

template<typename T>
inline Vector<T>::const_Iterator& Vector<T>::const_Iterator::operator-=(difference_type pos)
{
	m_value -= pos;
	return *this;
}

template<typename T>
inline T& Vector<T>::const_Iterator::operator[](difference_type pos) const
{
	return m_value[pos];
}

template<typename T>
inline bool Vector<T>::const_Iterator::operator<(const Iterator& it) const
{
	return m_value < it.m_value;
}

template<typename T>
inline bool Vector<T>::const_Iterator::operator>(const Iterator& it) const
{
	return m_value > it.m_value;
}

template<typename T>
inline bool Vector<T>::const_Iterator::operator<=(const Iterator& it) const
{
	return m_value <= it.m_value;
}

template<typename T>
inline bool Vector<T>::const_Iterator::operator>=(const Iterator& it) const
{
	return m_value >= it.m_value;
}

template<typename T>
inline bool Vector<T>::const_Iterator::operator!=(const const_Iterator& it) const
{
	return m_value != it.m_value;
}

template<typename T>
inline bool Vector<T>::const_Iterator::operator==(const const_Iterator& it) const
{
	return m_value == it.m_value;
}

template<typename T>
inline const T& Vector<T>::const_Iterator::operator*() const
{
	return *m_value;
}

template<typename T>
inline const T* Vector<T>::const_Iterator::operator->() const
{
	return m_value;
}
