/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:06:38 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/26 15:57:05 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft {
	template <class T, T v> struct integral_constant {
	static const T					value = v;
	typedef T						value_type;
	typedef integral_constant<T,v>	type;
	operator T() { return v; }
	};

	template <class T> struct is_integral : integral_constant<bool, false>{};
	template <> struct is_integral<bool> : integral_constant<bool, true>{};
	template <> struct is_integral<char> : integral_constant<bool, true>{};
	template <> struct is_integral<wchar_t> : integral_constant<bool, true>{};
	template <> struct is_integral<signed char> : integral_constant<bool, true>{};
	template <> struct is_integral<short int> : integral_constant<bool, true>{};
	template <> struct is_integral<int> : integral_constant<bool, true>{};
	template <> struct is_integral<long int> : integral_constant<bool, true>{};
	template <> struct is_integral<long long int> : integral_constant<bool, true>{};
	template <> struct is_integral<unsigned char> : integral_constant<bool, true>{};
	template <> struct is_integral<unsigned short int> : integral_constant<bool, true>{};
	template <> struct is_integral<unsigned int> : integral_constant<bool, true>{};
	template <> struct is_integral<unsigned long int> : integral_constant<bool, true>{};
	template <> struct is_integral<unsigned long long int> : integral_constant<bool, true>{};

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };
};

#endif