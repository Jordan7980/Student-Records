/*
Program Name: Lab x
Programmer Name: Prof. Miller
Date Submitted: Not submitted
File Purpose: doubly linked node
Version: 20230305
Purpose for Update: n/a
Global Variable List: n/a (avoid these)
*/

#ifndef NODE_DLLI17_H_
#define NODE_DLLI17_H_

#include <iterator>
#include <cassert>

namespace DSDLLI17 {

    template <typename T>
    class node
    {
    public:
        typedef T value_type;

        struct iterator
        {
            typedef iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef int difference_type;

            iterator(node * ptr=nullptr) : m_ptr(ptr) {}
            T& operator*() const { return m_ptr->data(); }
            T* operator->() const { return &(m_ptr->data()); }
            self_type& operator++() { m_ptr = m_ptr->next(); return *this; }
            self_type operator++(int) { self_type tmp = *this; ++(*this); return tmp; }
            self_type& operator--() { m_ptr = m_ptr->prev(); return *this; }
            self_type operator--(int) { self_type tmp = *this; --(*this); return tmp; }
            bool operator==(const self_type& b) { return m_ptr == b.m_ptr; };
            bool operator!=(const self_type& b) { return m_ptr != b.m_ptr; };
        private:
            node *  m_ptr;
        };
        struct const_iterator
        {
            typedef const_iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef int difference_type;

            const_iterator(node * ptr=nullptr) : m_ptr(ptr) {}
            const T& operator*() const { return m_ptr->data(); }
            const T* operator->() const { return &(m_ptr->data()); }
            self_type& operator++() { m_ptr = m_ptr->next(); return *this; }
            self_type operator++(int) { self_type tmp = *this; ++(*this); return tmp; }
            self_type& operator--() { m_ptr = m_ptr->prev(); return *this; }
            self_type operator--(int) { self_type tmp = *this; --(*this); return tmp; }
            bool operator==(const self_type& b) { return m_ptr == b.m_ptr; };
            bool operator!=(const self_type& b) { return m_ptr != b.m_ptr; };
        private:
            node * m_ptr;
        };
        struct reverse_iterator
        {
            typedef reverse_iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef int difference_type;

            reverse_iterator(node * ptr=nullptr) : m_ptr(ptr) {}
            T& operator*() const { return m_ptr->data(); }
            T* operator->() const { return &(m_ptr->data()); }
            self_type& operator--() { m_ptr = m_ptr->next(); return *this; }
            self_type operator--(int) { self_type tmp = *this; ++(*this); return tmp; }
            self_type& operator++() { m_ptr = m_ptr->prev(); return *this; }
            self_type operator++(int) { self_type tmp = *this; --(*this); return tmp; }
            bool operator==(const self_type& b) { return m_ptr == b.m_ptr; };
            bool operator!=(const self_type& b) { return m_ptr != b.m_ptr; };
        private:
            node *  m_ptr;
        };
        struct const_reverse_iterator
        {
            typedef const_reverse_iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef int difference_type;

            const_reverse_iterator(node * ptr=nullptr) : m_ptr(ptr) {}
            const T& operator*() const { return m_ptr->prev()->data(); }
            const T* operator->() const { return &(m_ptr->prev()->data()); }
            self_type& operator--() { m_ptr = m_ptr->next(); return *this; }
            self_type operator--(int) { self_type tmp = *this; ++(*this); return tmp; }
            self_type& operator++() { m_ptr = m_ptr->prev(); return *this; }
            self_type operator++(int) { self_type tmp = *this; --(*this); return tmp; }
            bool operator==(const self_type& b) { return m_ptr == b.m_ptr; };
            bool operator!=(const self_type& b) { return m_ptr != b.m_ptr; };
        private:
            node *  m_ptr;
        };

        node(value_type d = value_type(), node * n = nullptr, node * p = nullptr) : data_field(d), next_ptr(n), prev_ptr(p) {}

        //Assessor/Getters
        const value_type& getData () const { return data_field; }
        node const * getPrev () const { return prev_ptr; }
        node const * getNext () const { return next_ptr; }
        //Shorter versions of the above two
        node const * prev () const { return prev_ptr; }
        node const * next () const { return next_ptr; }

        //Mutators/Setters
        void setData (const value_type& d) { data_field = d; }
        void setPrev (node * new_link) { prev_ptr = new_link; }
        void setNext (node * new_link) { next_ptr = new_link; }

        //Other
        value_type& data() { return data_field; }
        const value_type& data() const { return data_field; }
        node*& prev () { return prev_ptr; }
        node*& next () { return next_ptr; }

    private:
        value_type data_field;
        node* next_ptr;
        node* prev_ptr;
    };
} /* namespace DSDLLI17 */

#endif /* NODE_DLLI17_H_ */
