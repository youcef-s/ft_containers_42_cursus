/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:09:35 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/24 18:36:36 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <iostream>
# include "avl.hpp"

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
			typedef std::ptrdiff_t					diffrence_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};
	template <class T> class iterator_traits<const T *> {
		public:
			typedef std::ptrdiff_t					diffrence_type;
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
			typedef std::ptrdiff_t								difference_type;

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
			reference operator[](int n) {return _ptr[n];}
			operator random_access_iterator<const T> () const {
				return (random_access_iterator<const T>(_ptr));
			}
	};
	template <class Iter1, class Iter2>  bool operator==(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iter1, class Iter2>  bool operator!=(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iter1, class Iter2>  bool operator<(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() < rhs.base());
	}
	template <class Iter1, class Iter2>  bool operator<=(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() <= rhs.base());
	}
	template <class Iter1, class Iter2>  bool operator>(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() > rhs.base());
	}
	template <class Iter1, class Iter2>  bool operator>=(const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator> random_access_iterator<Iterator> operator+( typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator> &rev_it) {
		return (random_access_iterator<Iterator>(rev_it.base() + n));
	}
	template <class Iter1, class Iter2> typename random_access_iterator<Iter1>::difference_type operator-( const random_access_iterator<Iter1> &lhs, const random_access_iterator<Iter2> &rhs) {
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
	template <class Iter1, class Iter2> typename reverse_iterator<Iter1>::difference_type operator- (const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return rhs.base() - lhs.base();
	}
	/********************  Bidirectional iterator ********************/
	template<typename T, typename Comp, typename Alloc> class bidirectional_iterator {
		private:
			T*						_ptr;
			Tree<T, Comp , Alloc >*	_avl;
		public:
			typedef T											value_type;
			typedef std::bidirectional_iterator_tag				iterator_category;
			typedef T*											pointer;
			typedef T&											reference;
			typedef std::ptrdiff_t								difference_type;

			bidirectional_iterator() : _ptr(NULL) , _avl(NULL) {}
			bidirectional_iterator(pointer ptr, Tree<T, Comp, Alloc>* avl) : _ptr(ptr), _avl(avl) {}
			bidirectional_iterator(const bidirectional_iterator & copy) : _ptr(copy._ptr), _avl(copy._avl) {}
			bidirectional_iterator & operator=(const bidirectional_iterator & assign) {
				_ptr = assign._ptr;
				_avl = assign._avl;
				return *this;
			}
			~bidirectional_iterator() {}
			bool operator==(const bidirectional_iterator & it) {
				return _ptr == it._ptr;
			}
			bool operator!=(const bidirectional_iterator & it) {
				return _ptr != it._ptr;
			}
			reference operator*() {return *_ptr;}
			pointer operator->() {return &(operator*());}
			bidirectional_iterator & operator++() {
				Node<T, Alloc>*	node = _avl->search(_avl->root, *_ptr);
				if (node) {
					Node<T, Alloc>*	succ = _avl->successor(*_ptr);
					if (succ)
						_ptr = &succ->data;
					else
						_ptr = NULL;	
				}
				return *this;
			}
			bidirectional_iterator & operator--() {
				Node<T, Alloc>*	node = _avl->search(_avl->root, *_ptr);
				if (node) {
					Node<T, Alloc>*	succ = _avl->predecessor(*_ptr);
					if (succ)
						_ptr = &succ->data;
					else
						_ptr = NULL;
				}
				return *this;
			}
			bidirectional_iterator operator++(int) {
				bidirectional_iterator	tmp = *this;
				++(*this);
				return tmp;
			}
			bidirectional_iterator operator--(int) {
				bidirectional_iterator	tmp = *this;
				--(*this);
				return tmp;
			}
			operator bidirectional_iterator<const T, Comp, Alloc> () const {
				return bidirectional_iterator<const T, Comp, Alloc>
				(_ptr, reinterpret_cast<const Tree<const value_type, Comp, Alloc>*>(_avl));
			}
	};
}

#endif