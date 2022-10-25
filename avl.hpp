/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:54:29 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/25 16:26:32 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
# define AVL_HPP

#include <iostream>

namespace ft { 

	template <typename T, class Alloc = std::allocator<T> > class Node {
		public:
			T		data;
			Node*	parent;
			Node*	left;
			Node*	right;
			int		height;

			Node() {
				left = NULL;
				right = NULL;
				parent = NULL;
				data.first = 0;
				data.second = 0;
				height = 0;
			}
			Node(const T &val) {
				left = NULL;
				right = NULL;
				parent = NULL;
				data = val;
				height = 1;
			}
			Node &operator=(Node const &src) {
				left = src.left;
				right = src.right;
				parent = src.parent;
				height = src.height;
				data = src.data;
				return (*this);
			}
			~Node() {}
	};

	template <typename T, class Comp = std::less<T> , class Alloc = std::allocator<T> > class Tree {
		public:
		Node<T, Alloc>											*root;
		Comp													compare;
		Alloc													_alloc;
		typename Alloc::template rebind<Node<T, Alloc> >::other	n_alloc;

		Tree(): root(NULL) {}
		Tree(const Tree &src) {
			*this = src;
		}
		Tree &operator=(Tree const &src) {
			root = src.root;
			compare = src.compare;
			return (*this);
		}
		~Tree(){}

		int getHeight(Node<T, Alloc> *N) {
			return N == NULL ? 0 : N->height;
		}

		Node<T, Alloc> *rightRotate(Node<T, Alloc> *oldTop) {
			Node<T, Alloc> *newTop = oldTop->left;
			if (!newTop) return oldTop;
			Node<T, Alloc> *tmpR = newTop->right;
			if (newTop->right) newTop->right->parent = oldTop;
			newTop->right = oldTop;
			oldTop->left = tmpR;
			newTop->parent = oldTop->parent;
			oldTop->parent = newTop;
			oldTop->height = std::max(getHeight(oldTop->left), getHeight(oldTop->right)) + 1;
			newTop->height = std::max(getHeight(newTop->left), getHeight(newTop->right)) + 1;
			return newTop;
		}

		Node<T, Alloc> *leftRotate(Node<T, Alloc> *oldTop) {
			Node<T, Alloc> *newTop = oldTop->right;
			Node<T, Alloc> *tmpL = newTop->left;
			if (newTop->left) newTop->left->parent = oldTop;
			newTop->left = oldTop;
			oldTop->right = tmpL;
			newTop->parent = oldTop->parent;
			oldTop->parent = newTop;
			oldTop->height = std::max(getHeight(oldTop->left), getHeight(oldTop->right)) + 1;
			newTop->height = std::max(getHeight(newTop->left), getHeight(newTop->right)) + 1;
			return newTop;
		}

		int getBalance(Node<T, Alloc> *N) {
			return N == NULL ? 0 : getHeight(N->left) - getHeight(N->right);
		}

		Node<T, Alloc>* rebalance(Node<T, Alloc>* node, const T& key) {
			int Balance = getBalance(node);
			if (Balance > 1) {
				if (compare(key.first, node->left->data.first))
					return rightRotate(node);
				else {
					node->left = leftRotate(node->left);
					return rightRotate(node);
				}
			}
			if (Balance < -1) {
				if (compare(node->right->data.first, key.first))
					return leftRotate(node);
				else {
					node->right = rightRotate(node->right);
					return leftRotate(node);
				}
			}
			return node;
		}

		Node<T, Alloc>* insert(T key) {
			root = insert(root, key);
			return root;
		}

		Node<T, Alloc> *newNode(T const &key) {
			Node<T, Alloc>* node = n_alloc.allocate(1);
			n_alloc.construct(node, key);
			return (node);
		}
		Node<T, Alloc>* insert(Node<T, Alloc>* node, const T& key) {
			if (!node)
				return (newNode(key));
			if (compare(key.first, node->data.first)) {
				node->left = insert(node->left, key);
				node->left->parent = node;
			}
			else if (compare(node->data.first, key.first)) {
				node->right = insert(node->right, key);
				node->right->parent = node;
			}
			else
				return (node);
			node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
			return rebalance(node, key);
		}

		void preOrder(Node<T, Alloc> *node) {
			if(node != NULL) {
				preOrder(node->left);
				preOrder(node->right);
				n_alloc.deallocate(node, 1);
				node = NULL;
			}
		}
		
		Node<T, Alloc>* minNode(Node<T, Alloc>* node) const {
			Node<T, Alloc>* current = node;
			while (current->left)
				current = current->left;
			return current;
		}

		Node<T, Alloc>* maxNode(Node<T, Alloc>* node) const {
			Node<T, Alloc>*	current = node;
			while (current->right)
				current = current->right;
			return current;
		}
		
		bool deleteNode(T key) {
			if (search(root, key)) {
				root = deleteNode(root, key);
				return true;
			}
			return false;
		}

		Node<T, Alloc>* deleteNode(Node<T, Alloc>* node, const T& key) {
			if (node == NULL)
				return NULL;
			if (compare(key.first ,node->data.first))
				node->left = deleteNode(node->left, key);
			else if(compare(node->data.first, key.first))
				node->right = deleteNode(node->right, key);
			else {
				if(node->left == NULL || node->right == NULL) {
					Node<T, Alloc> *temp = node->left ? node->left : node->right;
					if (temp == NULL) {
						temp = node;
						node = NULL;
					}
					else {
						Node<T, Alloc> *np = node->parent;
						*node = *temp;
						node->parent = np;
					}
					n_alloc.destroy(temp);
					n_alloc.deallocate(temp, 1);
				}
				else {
					Node<T, Alloc> *tmp = minNode(node->right);
					node->data = tmp->data;
					node->right = deleteNode(node->right, tmp->data);
				}
			}
			if (node == NULL)
				return NULL;
			node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
			return rebalance(node, key);
		}
		Node<T, Alloc>* search(Node<T, Alloc>* node, const T& key) const {
			if (node == NULL)
				return NULL;
			if (node->data.first == key.first)
				return (node);
			if (compare(key.first, node->data.first))
				return (search(node->left, key));
			else if (compare(node->data.first, key.first))
				return (search(node->right, key));
			return (node);
		}
		Node<T, Alloc>* successor(const T& var) const {
			Node<T, Alloc>*	node = search(root, var);
			if (node == NULL)
				return NULL;
			if (node->right)
				return minNode(node->right);
			Node<T, Alloc>*	succ = node->parent;
			while (succ && succ->left != node) {
				node = succ;
				succ = node->parent;
			}
			return succ;
		}
		Node<T, Alloc>* predecessor(const T& var) const {
			Node<T, Alloc>*	node = search(root, var);
			if (node == NULL)
				return NULL;
			if (node->left)
				return maxNode(node->left);
			Node<T, Alloc>*	succ = node->parent;
			while (succ && succ->right != node) {
				node = succ;
				succ = node->parent;
			}
			return succ;
		}
		void clone(const Node<T, Alloc> *node) {
			if (!node)
				return ;
			clone(node->left);
			if (node->data.first)
				insert(node->data);
			clone(node->right);
		}
	};
}

#endif