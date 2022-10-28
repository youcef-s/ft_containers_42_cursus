/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:23:19 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/28 11:24:18 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <map>

using namespace ft;
using std::cout;

int	main(void) {

	cout << "\033[0;32m** Constructors && operator= **\033[0m\n";
	{
		map<char,int> map1;

		map1['a'] = 1;
		map1['b'] = 7;
		map1['c'] = -2;
		map1['d'] = 3;

		map<char,int> map2 (map1.begin(),map1.end());
		map1['e'] = 10;
		map<char,int> map3 (map2);
		map3 = map1;

		for(map<char,int>::iterator i = map3.begin(); i !=  map3.end(); ++i)
			cout << i->first << " = " <<  i->second << "\t";
		cout << "\n";
	}

	cout << "\033[0;32m** get_allocator **\033[0m\n";
	{
		map<int,int> mp;
		pair<const int,int>* pr;

		pr = mp.get_allocator().allocate(5);
		for (int i = 0; i < 5; ++i)
			mp.get_allocator().construct(pr + i, make_pair(i, i*10));
		for (int i = 0; i < 5; ++i)
			cout << pr[i].first << " = " << pr[i].second << '\t';
		cout << '\n';
		for (int i = 0; i < 5; ++i)
			mp.get_allocator().destroy(pr + i);
		mp.get_allocator().deallocate(pr, 5);
	}

	cout << "\033[0;32m** operator[] && at **\033[0m\n";
	{
		map<char,std::string> mp;

		mp['a'] = "something";
		mp['b'] = "something else";
		mp['c'] = mp['b'];

		cout << "mp['a'] contains " << mp.at('a') << "\n";
		cout << "mp['b'] contains " << mp.at('b') << "\n";
		cout << "mp['c'] contains " << mp['c'] << "\n";
		cout << "mp['d'] contains " << mp['d'] << "\n";
	}

	cout << "\033[0;32m** Begin && end **\033[0m\n";
	{
		map<char,int> mp;

		mp['b'] = 10;
		mp['a'] = 20;
		mp['c'] = 30;

		for (map<char,int>::iterator it = mp.begin(); it != mp.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << " <-- iterator\n";
		for (map<char,int>::const_iterator it = mp.begin(); it != mp.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << " <-- const_iterator\n";
	}

	cout << "\033[0;32m** rbegin && rend **\033[0m\n";
	{
		map<char,int> mp;

		mp['a'] = 10;
		mp['b'] = 20;
		mp['c'] = 30;

		for (map<char,int>::reverse_iterator rit = mp.rbegin(); rit != mp.rend(); ++rit)
			cout << rit->first << " = " << rit->second << '\t';
		cout << " <-- reverse_iterator\n";
		for (map<char,int>::const_reverse_iterator rit = mp.rbegin(); rit != mp.rend(); ++rit)
			cout << rit->first << " = " << rit->second << '\t';
		cout << " <-- const_reverse_iterator\n";
	}

	cout << "\033[0;32m** empty && size **\033[0m\n";
	{
		map<char,int> mp;
		cout << "after creating a fresh map: the map is emoty: ";
		cout << std::boolalpha << mp.empty() << "\n";
		cout << "the size of the map is " << mp.size() << "\n";
		
		mp['a'] = 10;
		cout << "after adding an element: the map is emoty: ";
		cout << std::boolalpha << mp.empty() << "\n";
		cout << "the size of the map is " << mp.size() << "\n";
		
		mp.erase('a');
		cout << "after removing the element: the map is emoty: ";
		cout << std::boolalpha << mp.empty() << "\n";
		cout << "the size of the map is " << mp.size() << "\n";
	}

	cout << "\033[0;32m** clear **\033[0m\n";
	{
		map<char,int> mp;

		mp['x'] = 10;
		mp['y'] = 20;
		mp['z'] = 30;

		for (map<char,int>::iterator it = mp.begin(); it != mp.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << " <-- before\n";

		mp.clear();
		mp['a'] = 3;
		mp['b'] = 7;

		for (map<char,int>::iterator it = mp.begin(); it != mp.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << " <-- after\n";
	}
	
	cout << "\033[0;32m** insert **\033[0m\n";
	{
		map<char,int> map1;

		map1.insert (pair<char,int>('a', 10));
		map1.insert (pair<char,int>('z', 20));

		pair<map<char,int>::iterator,bool> pr;
		pr = map1.insert(pair<char,int>('z', 50));
		if (pr.second == false) {
			cout << "element 'z' is already in the map";
			cout << " with a value of " << pr.first->second << '\n';
		}

		map<char,int>::iterator it = map1.begin();
		map1.insert(it, pair<char,int>('b', 30));
		map1.insert(it, pair<char,int>('c', 40));

		map<char,int> map2;
		map2.insert(map1.begin(), map1.find('c'));

		for (it = map1.begin(); it != map1.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << " <-- map1\n";

		for (it = map2.begin(); it != map2.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << " <-- map2\n";
	}
	
	cout << "\033[0;32m** erase **\033[0m\n";
	{
		map<char,int> mp;

		mp['a'] = 10;
		mp['b'] = 20;
		mp['c'] = 30;
		mp['d'] = 40;
		mp['e'] = 50;
		mp['f'] = 60;

		map<char,int>::iterator it = mp.find('b');
		mp.erase(it);
		mp.erase('c');

		it = mp.find('e');
		mp.erase(it, mp.end());

		for (it = mp.begin(); it != mp.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << "\n";
	}

	cout << "\033[0;32m** swap **\033[0m\n";
	{
		map<char,int> map1, map2;

		map1['x'] = 1;
		map1['y'] = 2;

		map2['a'] = 3;
		map2['b'] = 5;
		map2['c'] = 7;

		map1.swap(map2);

		for (map<char,int>::iterator it = map1.begin(); it != map1.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << " <-- map1\n";

		for (map<char,int>::iterator it = map2.begin(); it != map2.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << " <-- map2\n";
	}

	cout << "\033[0;32m** count **\033[0m\n";
	{
		map<char,int> mp;

		mp['a'] = 10;
		mp['b'] = 20;
		mp['c'] = 30;
		
		cout << "number of elements with key 'a': " << mp.count('a') << '\n'; 
		cout << "number of elements with key 'z': " << mp.count('z') << '\n'; 
	}

	cout << "\033[0;32m** find **\033[0m\n";
	{
		map<char,int> mp;
		map<char,int>::iterator it;

		mp['a'] = 3;
		mp['b'] = 5;
		mp['c'] = 7;


		cout << "a = " << mp.find('a')->second << '\t';
		cout << "b = " << mp.find('b')->second << '\t';
		cout << "c = " << mp.find('c')->second << '\t';
		cout << '\n';
	}
	
	cout << "\033[0;32m** lower_bound && upper_bound **\033[0m\n";
	{
		map<char,int> mp;
		map<char,int>::iterator low, up;

		mp['a'] = 10;
		mp['b'] = 20;
		mp['c'] = 30;
		mp['d'] = 40;
		mp['e'] = 50;

		low = mp.lower_bound('b');
		up = mp.upper_bound('c');

		cout << "The lower bound of 'b' : " << low->first << " = " << low->second << '\n';
		cout << "The upper bound of 'c' : " << up->first << " = " << up->second << '\n';
	}

	cout << "\033[0;32m** equal_range **\033[0m\n";
	{
		map<char,int> mp;

		mp['a'] = 10;
		mp['b'] = 20;
		mp['c'] = 30;

		pair<map<char,int>::iterator,map<char,int>::iterator> pr;
		pr = mp.equal_range('b');

		cout << "The lower bound of 'b' : ";
		cout << pr.first->first << " = " << pr.first->second << '\n';
		cout << "The upper bound of 'b' : ";
		cout << pr.second->first << " = " << pr.second->second << '\n';
	}

	cout << "\033[0;32m** key_comp **\033[0m\n";
	{
		map<char,int> mp;

		map<char,int>::key_compare cmpfun = mp.key_comp();

		mp['a'] = 20;
		mp['b'] = 10;
		mp['c'] = 30;

		char last = mp.rbegin()->first;

		map<char,int>::iterator it = mp.begin();
		do {
			cout << it->first << " = " << it->second << '\t';
		} while (cmpfun((*it++).first, last));
		cout << '\n';
	}

	cout << "\033[0;32m** value_comp **\033[0m\n";
	{
		map<char,int> mp;

		mp['a'] = 20;
		mp['b'] = 10;
		mp['c'] = 30;

		pair<char,int> last = *mp.rbegin();

		map<char,int>::iterator it = mp.begin();
		do {
			cout << it->first << " = " << it->second << '\t';
		} while (mp.value_comp()(*it++, last));
		cout << '\n';
	}

	cout << "\033[0;32m** relational operators **\033[0m\n";
	{
		map<char, int> map1;
		map<char, int> map2;
		map1['a'] = 10;
		map1['b'] = 20;
		map2['c'] = 30;

		if (map1 == map2)
			cout << "map1 and map2 are equal\n";
		if (map1 != map2)
			cout << "map1 and map2 are not equal\n";
		if (map1 < map2)
			cout << "map1 is less than map2\n";
		if (map1 > map2)
			cout << "map1 is greater than map2\n";
		if (map1 <= map2)
			cout << "map1 is less than or equal to map2\n";
		if (map1 >= map2)
			cout << "map1 is greater than or equal to map2\n";
	}

	cout << "\033[0;32m** swap (non-member) **\033[0m\n";
	{
		map<char,int> map1, map2;

		map1['x'] = 1;
		map1['y'] = 2;

		map2['a'] = 3;
		map2['b'] = 5;
		map2['c'] = 7;

		swap(map1, map2);

		for (map<char,int>::iterator it = map1.begin(); it != map1.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << " <-- map1\n";

		for (map<char,int>::iterator it = map2.begin(); it != map2.end(); ++it)
			cout << it->first << " = " << it->second << '\t';
		cout << " <-- map2\n";
	}
}
