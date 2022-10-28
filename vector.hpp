/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:04:27 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/28 17:44:20 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <iterator>
# include "iterators.hpp"
# include "lexicographical_compare.hpp"
# include "is_integral.hpp"

namespace ft {
	template< class T, class Allocator = std::allocator<T> > class vector {
		public:
			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef std::ptrdiff_t									difference_type;
			typedef std::size_t										size_type;

			/********************  Member functions ********************/
			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _ptr(NULL) {}
			
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
				_size = n;
				_capacity = n;
				_alloc = alloc;
				_ptr = _alloc.allocate(n);
				for(size_type i = 0; i < n; ++i)
					_alloc.construct(_ptr + i, val);
			}			
			template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
				difference_type size = std::distance(first, last);
				_size = static_cast<size_type>(size);
				_capacity = static_cast<size_type>(size);
				_alloc = alloc;
				_ptr = _alloc.allocate(size);
				for(difference_type i = 0; i < size; ++i) {
					_alloc.construct(_ptr + i, *first);
					first++;
				}
			}
			vector (const vector& x) {
				_size = 0;
				_capacity = 0;
				*this = x;
			}
			vector& operator= (const vector& x) {
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_ptr + i);
				if (_capacity)
					_alloc.deallocate(_ptr, _capacity);
				_capacity = x._capacity;
				_size = x._size;
				_alloc = x._alloc;
				if (_capacity)
					_ptr = _alloc.allocate(_capacity);
				for(size_type i = 0; i < _size; ++i)
					_alloc.construct(_ptr + i, x._ptr[i]);
				return *this;
			}
			~vector() {
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_ptr + i);
				if (_capacity)
					_alloc.deallocate(_ptr, _capacity);
			}
			allocator_type get_allocator() const {
				return _alloc;
			}
			void assign( size_type count, const T& value ) {
				clear();
				reserve(count);
				for(size_type i = 0; i < count; ++i)
					push_back(value);
			}
			template< class InputIt > void assign( InputIt first, InputIt last,
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) {
				size_type dist = static_cast<size_type>(std::distance(first, last));
				clear();
				reserve(dist);
				for (;first != last; ++first)
						push_back(*first);
			}
			/******************** Iterators ********************/
			iterator begin() {return iterator(_ptr);}
			const_iterator begin() const {return const_iterator(_ptr);}
			iterator end() {return iterator(_ptr + _size);}
			const_iterator end() const {return const_iterator(_ptr + _size);}
			reverse_iterator rbegin() {return reverse_iterator(end());}
			const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
			reverse_iterator rend() {return reverse_iterator(begin());}
			const_reverse_iterator rend() const {return const_reverse_iterator(begin());}	
			/******************** Capacity ********************/
			bool empty() const {return (_size == 0 ? true : false);}
			size_type size() const {return _size;}
			size_type max_size() const {return _alloc.max_size();}
			void reserve( size_type new_cap ) {
				if(new_cap > max_size())
					throw std::length_error("The size requested is greater than the maximum size!");
				else if (new_cap > _capacity) {
					pointer	newptr = _alloc.allocate(new_cap);
					for(size_type i = 0; i < _size; ++i)
						_alloc.construct(newptr + i, _ptr[i]);
					for(size_type i = 0; i < _size; ++i)
						_alloc.destroy(_ptr + i);
					if (_capacity)
						_alloc.deallocate(_ptr, _capacity);
					std::swap(newptr, _ptr);
					_capacity = new_cap;
				}
			}
			size_type capacity() const {return _capacity;}
			/******************** Modifiers ********************/
			void clear() {
				for(size_type i = 0; i < _size; ++i)
					_alloc.destroy(_ptr + i);
				_size = 0;
			}
			iterator insert (iterator position, const value_type& val) {
				vector<value_type>	tmp;

				tmp.assign(position, end());
				size_type tmpsize = static_cast<size_type>(std::distance(begin(), position));
				for (size_type i = tmpsize; i < _size; ++i)
					_alloc.destroy(_ptr + i);
				_size = tmpsize;
				push_back(val);
				for (size_type i = 0; i < tmp.size(); ++i)
					push_back(tmp[i]);
				return (begin() + tmpsize);
			}
			void insert (iterator position, size_type n, const value_type& val) {
				vector<value_type>	tmp;
				tmp.assign(position, end());
				if (n > _capacity)
					reserve(_size + n);
				else if (!_size)
					reserve(n);
				size_type tmpsize = static_cast<size_type>(std::distance(begin(), position));
				for (size_type i = tmpsize; i < _size; ++i)
					_alloc.destroy(_ptr + i);
				_size = tmpsize;
				for (size_type i = 0;i < n; ++i)
					push_back(val);
				for(size_type i = 0; i < tmp.size(); ++i)
					push_back(tmp[i]);
			}
			template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
				vector<value_type>	tmp;
				tmp.assign(position, end());
				size_type tmpsize = static_cast<size_type>(std::distance(begin(), position));
				for (size_type i = tmpsize; i < _size; ++i)
					_alloc.destroy(_ptr + i);
				_size = tmpsize;
				for (; first != last; ++first)
					push_back(*first);
				for (size_type i = 0; i < tmp.size(); ++i)
					push_back(tmp[i]);
			}
			iterator erase( iterator pos ) {
				if (pos == end())
					return end();
				_alloc.destroy(&(*pos));
				for (;pos != end(); ++pos) {
					_alloc.construct(&*pos, *(pos + 1));
					_alloc.destroy(&*(pos + 1));
				}
				_size--;
				return pos;
			}
			iterator erase( iterator first, iterator last ) {
				difference_type	dist = std::distance(first, last);
				if (dist == 0)
					return last;
				iterator it = first;
				for(;first != last; ++first)
					_alloc.destroy(&(*first));
				if (last == end())
					return end();
				for (;it != end(); ++it, ++first) {
					_alloc.construct(&*it, *first);
					_alloc.destroy(&*first);
				}
				_size -= static_cast<size_type>(dist);
				return it;
			}
			void push_back( const T& value ) {
				if (_capacity == 0)
					reserve(1);
				else if (_size + 1 > _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_ptr + _size, value);
				_size++;
			}
			void pop_back() {
				if (_size == 0)
					return ;
				_alloc.destroy(_ptr + _size);
				_size--;
			}
			void resize( size_type count, T value = T() ) {
				if (count > max_size())
					throw std::length_error("The capacity required exceeds max_size()");
				else if (_size > count) {
					while (_size > count)
						pop_back();
				}
				else {
					while(_size < count)
						push_back(value);
				}
			}
			void swap( vector& other ) {
				std::swap(_size, other._size);
				std::swap(_capacity, other._capacity);
				std::swap(_ptr, other._ptr);
			}
			/******************** Element access ********************/
			reference at( size_type pos ) {
				if (pos >= _size)
					throw  std::out_of_range("The element required is not within the range");
				return _ptr[pos];
			}
			const_reference at( size_type pos ) const {
				if (pos >= _size)
					throw  std::out_of_range("The element required is not within the range");	
				return _ptr[pos];
			}
			reference operator[]( size_type pos ) {return _ptr[pos];}
			const_reference operator[]( size_type pos ) const {return _ptr[pos];}
			reference front() {return _ptr[0];}
			const_reference front() const {return _ptr[0];}
			reference back() {return _ptr[_size - 1];}
			const_reference back() const {return _ptr[_size - 1];}
			T* data() {return _ptr;}
			const T* data() const {return _ptr;}

		private:
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;
			pointer			_ptr;
	};
	/********************  Non Member functions ********************/
	template< class U, class Alloc >
	bool operator==( const ft::vector<U,Alloc>& lhs, const ft::vector<U,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		for (std::size_t i = 0; i < lhs.size(); ++i) {
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}
	template< class U, class Alloc >
	bool operator!=( const ft::vector<U,Alloc>& lhs, const ft::vector<U,Alloc>& rhs ) {
		return !(lhs == rhs);
	}
	template< class U, class Alloc >
	bool operator<( const ft::vector<U,Alloc>& lhs, const ft::vector<U,Alloc>& rhs ) {
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class U, class Alloc >
	bool operator>=( const ft::vector<U,Alloc>& lhs, const ft::vector<U,Alloc>& rhs ) {
		return !(lhs < rhs);
	}
	template< class U, class Alloc >
	bool operator>( const ft::vector<U,Alloc>& lhs, const ft::vector<U,Alloc>& rhs ) {
		return lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
	template< class U, class Alloc >
	bool operator<=( const ft::vector<U,Alloc>& lhs, const ft::vector<U,Alloc>& rhs ) {
		return !(lhs > rhs);
	}
	template <class T, class Alloc>  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif