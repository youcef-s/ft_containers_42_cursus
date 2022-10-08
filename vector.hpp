/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:04:27 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/08 18:45:42 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

namespace ft {
	template< class T, class Allocator = std::allocator<T> > class vector {
		public:
			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			/*
			**	TODO: implement my own iterators
			**
			**	typedef ft::random_access_iterator<value_type>			iterator;
			**	typedef ft::random_access_iterator<const value_type>	const_iterator;
			**	typedef std::reverse_iterator<iterator>					reverse_iterator;
			**	typedef std::reverse_iterator<const_iterator>			const_reverse_iterator;
			*/
			typedef ptrdiff_t										difference_type;
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
			
			template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
				difference_type size = std::distance(first, last);
				_size = size;
				_capacity = size;
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
				_alloc = x._alloc;
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_ptr + i);
				if (_capacity)
					_alloc.deallocate(_ptr, _capacity);
				_capacity = x._capacity;
				_size = x._size;
				_alloc = x._alloc;
				if (_capacity)
					_alloc.allocate(_capacity);
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
			/******************** Iterators ********************/
			/*
			**	TODO: Use my own iterators
			**
			**	iterator begin() {return iterator(_ptr);}
			**	iterator end() {return iterator(_ptr + _size);}
			**	reverse_iterator rbegin() {return reverse_iterator(end());}
			**	reverse_iterator rend() {return reverse_end(begin());}
			*/
		
			/******************** Capacity ********************/
			size_type max_size() const {return _alloc.max_size();}
			bool empty() const {return (_size == 0 ? true : false);}
			size_type size() const {return _size;}
			size_type capacity() const {return _capacity;}
			void reserve( size_type new_cap ) {
				if(new_cap > max_size())
					throw std::length_error("The size requested is greater than the maximum size!");
				else if (new_cap > _capacity) {
					pointer	newptr = _alloc.allocate(new_cap);
					for(size_type i = 0; i < _size; ++i)
						_alloc.constrct(newptr + i, _ptr[i]);
					for(size_type i = 0; i < _size; ++i)
						_alloc.destroy(_ptr + i);
					if (_capacity)
						_alloc.deallocate(_ptr, _capacity);
					std::swap(newptr, _ptr);
					_capacity = new_cap;
				}
			}
			/******************** Modifiers ********************/
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
				_alloc.destruct(_ptr + _size);
				_size--;
			}
			void clear() {
				for(size_type i = 0; i < _size; ++i)
					_alloc.destroy(_ptr + i);
				_size = 0;
			}
			void swap( vector& other ) {
				std::swap(_size, other._size);
				std::swap(_capacity, other._capacity);
				std::swap(_ptr, other._ptr);
			}
		
		private:
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;
			pointer			_ptr;
	};
}


#endif