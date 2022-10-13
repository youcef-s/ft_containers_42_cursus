/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:47 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/13 19:53:09 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: fix the issue of reverse_iterator + number not working and erase() seg

#include "vector.hpp"
#include <vector>

int	main(void) {

	ft::vector<int>	vect(5, 45);
	
	ft::vector<int>	vect2;
	vect2.assign(vect.begin(), vect.end());
	vect2.insert(vect2.end(), 12);
	vect2.insert(vect2.end(), 12);
	vect2.erase(vect2.begin());
	for (std::size_t i = 0; i  < vect2.size(); ++i)
		std::cout << vect2[i] << std::endl;
	return 0;
}