/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:47 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/10 15:17:45 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
int	main(void) {

	std::vector<int> vect;

	for (int i = 0; i < 5; ++i)
		vect.push_back(i);
	
	std::cout << std::endl << vect.size() << std::endl;

	vect.assign(2, 10);
	for (size_t i = 0; i < 5; ++i)
		std::cout << vect[i] << " ";

	std::cout << std::endl << vect.size() << std::endl;
	return 0;
}