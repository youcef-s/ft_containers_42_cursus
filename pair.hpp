/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:57:06 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/16 17:30:57 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {
	template <class T1, class T2> struct pair {
		T1	first;
		T2	second;

		typedef T1	first_type;
		typedef T2	second_type;

		pair() : first(first_type()), second(second_type()) {}
		template<class U, class V> pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
		pair (const first_type& a, const second_type& b) : first(a) , second(b) {}
		pair& operator= (const pair& pr) {first = pr.first; second = pr.second; return *this;}
	};
	template< class T1, class T2 > ft::pair<T1, T2> make_pair( T1 t, T2 u ) {
		return ft::pair<T1 , T2>(t, u);
	}
	template <class T1, class T2> bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
	template <class T1, class T2> bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(lhs == rhs);
	}
	template <class T1, class T2> bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
	}
	template <class T1, class T2> bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(rhs < lhs);
	}
	template <class T1, class T2> bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return rhs < lhs;
	}
	template <class T1, class T2> bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(lhs < rhs);
	}
}



#endif