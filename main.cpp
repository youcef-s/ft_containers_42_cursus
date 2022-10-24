/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:47 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/24 18:45:38 by ylabtaim         ###   ########.fr       */
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

int	main(void) {

	ft::map<char, int>	map;
	map['r'] = 10;
	map['b'] = 100;
	map['k'] = 86;
	map.insert(ft::make_pair('a', 12));
	ft::map<char, int>::iterator	it = map.begin();
	ft::map<char, int>::iterator	it2 = map.end();
	// ft::map<char, int>::const_iterator	cit = map.begin();
	ft::map<char, int>	map2(it, it2);
	ft::map<char, int>	map3;
	map3.insert(it, it2);
	// map3.erase(map3.begin());
	// map3.erase('a');
	map3.erase(map3.begin(), map3.end());
	std::cout << map3.size() << std::endl;
	// map2.insert(ft::make_pair('c', 120));
	// map.swap(map2);
	// std::cout << map['c'] << std::endl;
	return 0;
}