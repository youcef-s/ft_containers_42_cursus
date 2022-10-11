/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:09:35 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/11 18:21:33 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP
# include <iostream>

namespace ft {
	/********************  Iterator ********************/
	template<class Category, class T, class Distance = std::ptrdiff_t,
	class Pointer = T*, class Reference = T& > struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference 	reference;
	};
	/********************  Random access iterator ********************/
	template<typename T> class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {
		private:
			pointer	_ptr;
		public:
			random_access_iterator() : _ptr(0) {}
			random_access_iterator(pointer ptr) : _ptr(ptr) {}
			random_access_iterator(const random_access_iterator & copy) {_ptr = copy._ptr;}
			random_access_iterator &operator=(const random_access_iterator & assign) {
				_ptr = assign._ptr;
				return *this;
			}
			~random_access_iterator(){}
			pointer base() {return _ptr;}
			bool operator==(const random_access_iterator & it1, const random_access_iterator & it2) {
				return (it1.base() == it2.base());
			}
			bool operator!=(const random_access_iterator & it1, const random_access_iterator & it2) {
				return !(it1 == it2);
			}
			reference operator*(void) {return *_ptr;}
			pointer operator->(void) {return _ptr;}
			random_access_iterator & operator++(void) {++_ptr; return *this;}
			random_access_iterator & operator--(void) {--_ptr; return *this;}
			random_access_iterator & operator++(int) {
				random_access_iterator tmp = *this;
				++_ptr;
				return tmp;
			}
			random_access_iterator & operator--(int) {
				random_access_iterator tmp = *this;
				--_ptr;
				return tmp;
			}
			random_access_iterator operator+(int n) {
				return random_access_iterator(_ptr + n);
			}
			random_access_iterator operator-(int n) {
				return random_access_iterator(_ptr - n);
			}
			random_access_iterator operator-(const random_access_iterator & it) {
				return random_access_iterator(_ptr - it.base());
			}
			bool operator<(const random_access_iterator & it1, const random_access_iterator & it2) {
				return (it1.base() < it2.base());
			}
			bool operator>(const random_access_iterator & it1, const random_access_iterator & it2) {
				return (it1.base() > it2.base());
			}
			bool operator<=(const random_access_iterator & it1, const random_access_iterator & it2) {
				return (it1.base() <= it2.base());
			}
			bool operator>=(const random_access_iterator & it1, const random_access_iterator & it2) {
				return (it1.base() >= it2.base());
			}
			random_access_iterator &operator+=(int n) {
				_ptr += n;
				return *this;
			}
			random_access_iterator &operator-=(int n) {
				_ptr -= n;
				return *this;
			}
			reference &operator[](int n) {return _ptr[n];}
	};
	/********************  Reverse iterator ********************/
	template <class Iterator> class reverse_iterator{
		private:
			iterator_type	_it;
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

			reverse_iterator();
			explicit reverse_iterator (iterator_type it) : _it(it) {}
			template <class Iter>  reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it._it) {}
			iterator_type base() const {return _it;}
			reference operator*() const {iterator_type tmp = _it; --tmp; return *tmp;}
			reverse_iterator operator+ (difference_type n) const {return reverse_iterator(_it - n);}
			reverse_iterator operator- (difference_type n) const {return reverse_iterator(_it + n);}
			reverse_iterator& operator++() {--_it; return *this;}
			reverse_iterator  operator++(int) {reverse_iterator tmp = *this; ++_it; return tmp;}
			reverse_iterator& operator--() {++_it; return *this;}
			reverse_iterator  operator++(int) {reverse_iterator tmp = *this; --_it; return tmp;}
			reverse_iterator& operator+= (difference_type n) {_it -= n; return *this;}
			reverse_iterator& operator-= (difference_type n) {_it += n; return *this;}
			pointer operator->() const {return &(operator*());}
			reference operator[] (difference_type n) const {return base()[-n-1];}
		
	};
}

#endif