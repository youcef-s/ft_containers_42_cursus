/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:31:47 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/28 11:30:13 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <stack>
#include <vector>

using namespace ft;
using std::cout;

int	main(void) {

	cout << "\033[0;32m** Constructors && operator= && size **\033[0m\n";
	{
		vector<int> vect (3,10);

		stack<int, vector<int> > stk(vect);
		stack<int, vector<int> > stk2(stk);
		stack<int, vector<int> > stk3;

		stk3 = stk;
		cout << "size of the first stack: " << stk.size() << '\n';
		cout << "size of the second stack: " << stk2.size() << '\n';
		cout << "size of the third stack: " << stk3.size() << '\n';
	}

	cout << "\033[0;32m** empty **\033[0m\n";
	{
		stack<int, vector<int> > stk;
		cout << "after creating a fresh stack, the stack is empty: ";
		cout << std::boolalpha << stk.empty() << "\n";

		for(int i = 0;i < 3; ++i)
			stk.push(i);
		cout << "after adding 3 elements, the stack is empty: ";
		cout << std::boolalpha << stk.empty() << "\n";

		stk.pop();
		stk.pop();
		stk.pop();
		cout << "after removing 3 elements, the stack is empty: ";
		cout << std::boolalpha << stk.empty() << "\n";
	}

	cout << "\033[0;32m** top && push && pop **\033[0m\n";
	{
		stack<int, vector<int> > stk;

		stk.push(3);
		cout << "the top of the stack after pushing 3 is: " << stk.top() << "\n";
		stk.push(4);
		cout << "the top of the stack after pushing 4 is: " << stk.top() << "\n";
		stk.pop();
		cout << "the top of the stack after popping 4 is: " << stk.top() << "\n";
	}

	cout << "\033[0;32m** relational operators **\033[0m\n";
	{
		vector<int>	vect1(3, 10);
		vector<int>	vect2(4, 20);
		stack<int, vector<int> > stack1(vect1);
		stack<int, vector<int> > stack2(vect2);

		if (stack1 == stack2)
			cout << "stack1 and stack2 are equal\n";
		if (stack1 != stack2)
			cout << "stack1 and stack2 are not equal\n";
		if (stack1 < stack2)
			cout << "stack1 is less than stack2\n";
		if (stack1 > stack2)
			cout << "stack1 is greater than stack2\n";
		if (stack1 <= stack2)
			cout << "stack1 is less than or equal to stack2\n";
		if (stack1 >= stack2)
			cout << "stack1 is greater than or equal to stack2\n";
	}
}