/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:47 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/12 16:26:15 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: fix the issue of reverse_iterator + number not working

#include "vector.hpp"
#include <vector>

int	main(void) {

	ft::vector<int>	vect1(2, 10);
	ft::vector<int>	vect2(2, 20);
	ft::vector<int>::reverse_iterator	it;
	ft::vector<int>::reverse_iterator	it2;
	it = vect1.rbegin();
	it2 = vect2.rbegin();

	std::cout << *it << std::endl;
	std::cout << *it2 << std::endl;
	return 0;
}