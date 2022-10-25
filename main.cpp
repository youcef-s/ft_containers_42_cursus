/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:47 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/25 20:22:24 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "stack.hpp"
#include "pair.hpp"
#include "avl.hpp"
#include "map.hpp"
#include <vector>
#include <stack>
#include <map>
#include <algorithm>

using ft::map;

/* There is still a problem with ft::map<T1, T2>::reverse_iterator */

int	main(void) {

	map<char, int> var;
	var['c'] = 202;
	var['r'] = 0;
	var['e'] = 20;
	var['w'] = 2;
	var['t'] = 12;
	var['x'] = 120;

	map<char, int>::reverse_iterator it = var.rbegin();
	for(; it != var.rend(); ++it)
		std::cout << it->first << " " << it->second << "\n";

	return 0;
}
