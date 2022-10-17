/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:09:35 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/17 11:12:20 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP
# include <iostream>

namespace ft {
	/********************  iterator_traits ********************/
	template <class Iterator> class iterator_traits {
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};
	template <class T> class iterator_traits<T *> {
		public:
			typedef ptrdiff_t						diffrence_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};
	template <class T> class iterator_traits<const T *> {
		public:
			typedef ptrdiff_t						diffrence_type;
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};

	/********************  Random access iterator ********************/
	template<typename T> class random_access_iterator {
		private:
			T*	_ptr;
		public:
			typedef T											value_type;
			typedef std::random_access_iterator_tag				iterator_category;
			typedef T*											pointer;
			typedef T&											reference;
			typedef ptrdiff_t									difference_type;

			random_access_iterator() : _ptr(0) {}
			random_access_iterator(pointer ptr) : _ptr(ptr) {}
			random_access_iterator(const random_access_iterator & copy) {_ptr = copy._ptr;}
			random_access_iterator &operator=(const random_access_iterator & assign) {
				_ptr = assign._ptr;
				return *this;
			}
			~random_access_iterator(){}
			pointer base() const {return _ptr;}
			bool operator==(const random_access_iterator & it) {
				return (_ptr == it._ptr);
			}
			bool operator!=(const random_access_iterator & it) {
				return !(*this == it);
			}
			reference operator*(void) {return *_ptr;}
			pointer operator->(void) {return &(operator*());}
			random_access_iterator & operator++(void) {++_ptr; return *this;}
			random_access_iterator & operator--(void) {--_ptr; return *this;}
			random_access_iterator operator++(int) {
				random_access_iterator tmp(*this);
				++_ptr;
				return tmp;
			}
			random_access_iterator operator--(int) {
				random_access_iterator tmp = *this;
				--_ptr;
				return tmp;
			}
			random_access_iterator operator+(int n) const {
				return random_access_iterator(_ptr + n);
			}
			random_access_iterator operator-(int n) const {
				return random_access_iterator(_ptr - n);
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
			operator random_access_iterator<const T> () const {
				return (random_access_iterator<const T>(_ptr));
			}
	};
	template <class Iterator> bool operator==(const random_access_iterator<Iterator> &lhs, const random_access_iterator<Iterator> &rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator> bool operator!=(const random_access_iterator<Iterator> &lhs, const random_access_iterator<Iterator> &rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iterator> bool operator<(const random_access_iterator<Iterator> &lhs, const random_access_iterator<Iterator> &rhs) {
		return (lhs.base() < rhs.base());
	}
	template <class Iterator> bool operator<=(const random_access_iterator<Iterator> &lhs, const random_access_iterator<Iterator> &rhs) {
		return (lhs.base() <= rhs.base());
	}
	template <class Iterator> bool operator>(const random_access_iterator<Iterator> &lhs, const random_access_iterator<Iterator> &rhs) {
		return (lhs.base() > rhs.base());
	}
	template <class Iterator> bool operator>=(const random_access_iterator<Iterator> &lhs, const random_access_iterator<Iterator> &rhs) {
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator> random_access_iterator<Iterator> operator+( typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator> &rev_it) {
		return (random_access_iterator<Iterator>(rev_it.base() + n));
	}
	template <class Iterator> typename random_access_iterator<Iterator>::difference_type operator-( const random_access_iterator<Iterator> &lhs, const random_access_iterator<Iterator> &rhs) {
		return (lhs.base() - rhs.base());
	}

	/********************  Reverse iterator ********************/
	template <class Iterator> class reverse_iterator{
		protected:
			Iterator	current;
		public:
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			reverse_iterator() {}
			explicit reverse_iterator (iterator_type it) : current(it) {}
			template <class Iter>  reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {}
			template< class U > reverse_iterator& operator=( const reverse_iterator<U>& other ) {current = other.base(); return *this;}
			iterator_type base() const {return current;}
			reference operator*() const {iterator_type tmp = current; return *--tmp;}
			reverse_iterator operator+ (difference_type n) const {return reverse_iterator(current - n);}
			reverse_iterator operator- (difference_type n) const {return reverse_iterator(current + n);}
			reverse_iterator& operator++() {--current; return *this;}
			reverse_iterator  operator++(int) {reverse_iterator tmp = *this; ++current; return tmp;}
			reverse_iterator& operator--() {++current; return *this;}
			reverse_iterator  operator--(int) {reverse_iterator tmp = *this; --current; return tmp;}
			reverse_iterator& operator+= (difference_type n) {current -= n; return *this;}
			reverse_iterator& operator-= (difference_type n) {current += n; return *this;}
			pointer operator->() const {return &(operator*());}
			reference operator[] (difference_type n) const {return base()[-n-1];}
	};
	template <class Iter1, class Iter2> bool operator== (const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iter1, class Iter2> bool operator!= (const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iter1, class Iter2> bool operator< (const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return (lhs.base() < rhs.base());
	}
	template <class Iter1, class Iter2> bool operator<= (const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return (lhs.base() <= rhs.base());
	}
	template <class Iter1, class Iter2> bool operator> (const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return (lhs.base() > rhs.base());
	}
	template <class Iter1, class Iter2> bool operator>= (const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return (lhs.base() >= rhs.base());
	}
	template <class Iter> reverse_iterator<Iter> operator+ (typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rev_it) {
		return reverse_iterator<Iter>(rev_it.base() - n);
	}
	template <class Iter> typename reverse_iterator<Iter>::difference_type operator- (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
		return rhs.base() - lhs.base();
	}
}

#endif