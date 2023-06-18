#pragma once
#include <iostream>

template <typename Type, int N>
class Container
{
public:
    struct Iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Type;
        using pointer = Type*;
        using reference = Type&;

        Iterator(Container::Iterator& o) : m_ptr(o.m_ptr) {}
        Iterator(Container::Iterator&& o) noexcept : m_ptr(std::move(o.m_ptr))
        {
            o.m_ptr = nullptr;
        }
        Iterator(pointer ptr) : m_ptr(ptr) {}
        ~Iterator() {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator& operator--() { m_ptr--; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
        friend bool operator< (const Iterator& a, const Iterator& b) { return a.m_ptr < b.m_ptr; };
        friend bool operator> (const Iterator& a, const Iterator& b) { return a.m_ptr > b.m_ptr; };
        friend bool operator>= (const Iterator& a, const Iterator& b) { return (a.m_ptr > b.m_ptr) || (a.m_ptr == b.m_ptr); };
        friend bool operator<= (const Iterator& a, const Iterator& b) { return (a.m_ptr < b.m_ptr) || (a.m_ptr == b.m_ptr); };

        Iterator& operator+(int n)
        {
            m_ptr = m_ptr + n;
            return *this;
        }
        Iterator& operator-(int n)
        {
            m_ptr = m_ptr - n;
            return *this;
        }
        Iterator& operator+=(int n)
        {
            m_ptr = m_ptr + n;
            return *this;
        }
        Iterator& operator-=(int n)
        {
            m_ptr = m_ptr - n;
            return *this;
        }


        // copy assignment
        Iterator& operator=(const Container::Iterator& other)
        {
            // Guard self assignment
            if (this == &other)
                return *this;

            *m_ptr = *other;
            return *this;
        }

        // move assignment
        Iterator& operator=(Iterator&& other) noexcept
        {
            // Guard self assignment
            if (this == &other)
                return *this;

            m_ptr = std::move(other.m_ptr);
            other.m_ptr = nullptr;

            return *this;
        }

        void swap(Iterator& other) {
            std::swap(*m_ptr, *other);
        }

    private:
        pointer m_ptr;
    };

    Container() { currIndex = 0; }
    Iterator begin() { return Iterator(&m_data[0]); }
    Iterator end() { return Iterator(&m_data[currIndex]); }
    void add(Type& value)
    {
        m_data[currIndex] = value;
        currIndex++;
    }

private:
    Type m_data[N];
    int currIndex;
};