/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:47 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/23 18:46:59 by ylabtaim         ###   ########.fr       */
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
	std::cout << map.at('r') << std::endl;
	std::cout << map.empty() << std::endl;
	std::cout << map.size() << std::endl;
	std::cout << map.max_size() << std::endl;
	map.clear();
	std::cout << map.empty() << std::endl;
	map['a'] = 20;
	std::cout << map.count('a') << std::endl;
	// map.insert(ft::make_pair('a', 12));
	// ft::map<char, int>::iterator	it = map.begin();

	return 0;
}