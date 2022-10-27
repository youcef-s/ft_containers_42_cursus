/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:15:53 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/27 11:11:46 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {
	template <class T, class Container = vector<T> > class stack {
		protected:
			Container	c;
		public:
			typedef Container			 				container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;

			explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}
			stack( const stack& other ) {*this = other;}
			~stack() {}
			stack& operator=( const stack& other ) {c = other.c;return *this;}
			bool empty() const {return c.empty();}
			size_type size() const {return c.size();}
			value_type& top() {return c.back();}
			const value_type& top() const {return c.back();}
			void push (const value_type& val) {c.push_back(val);}
			void pop() {c.pop_back();}
			template <class U, class C> friend bool operator== (const stack<U,C>& lhs, const stack<U,C>& rhs) {
				return lhs.c == rhs.c;
			}
			template <class U, class C> friend bool operator!= (const stack<U,C>& lhs, const stack<U,C>& rhs) {
				return lhs.c != rhs.c;
			}
			template <class U, class C> friend bool operator< (const stack<U,C>& lhs, const stack<U,C>& rhs) {
				return lhs.c < rhs.c;
			}
			template <class U, class C> friend bool operator<= (const stack<U,C>& lhs, const stack<U,C>& rhs) {
				return lhs.c <= rhs.c;
			}
			template <class U, class C> friend bool operator> (const stack<U,C>& lhs, const stack<U,C>& rhs) {
				return lhs.c > rhs.c;
			}
			template <class U, class C> friend bool operator>= (const stack<U,C>& lhs, const stack<U,C>& rhs) {
				return lhs.c >= rhs.c;
			}
	};
}

#endif