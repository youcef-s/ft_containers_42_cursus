/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 11:13:15 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/29 17:18:51 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterators.hpp"
#include "pair.hpp"
#include "vector.hpp"

namespace ft {

	template< class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > > class map {
		private:
			Tree<ft::pair<const Key, T> , Compare, Allocator>		_avl;
			Allocator												_alloc;
			Compare													_cmp;
			std::size_t												_size;
		
		public:
			typedef Key																			key_type;
			typedef T																			mapped_type;
			typedef ft::pair<const key_type, mapped_type>										value_type;
			typedef std::size_t																	size_type;
			typedef std::ptrdiff_t																difference_type;
			typedef Compare																		key_compare;
			typedef Allocator																	allocator_type;
			typedef value_type&																	reference;
			typedef const value_type&															const_reference;
			typedef typename Allocator::pointer													pointer;
			typedef typename Allocator::const_pointer											const_pointer;
			typedef typename ft::bidirectional_iterator<value_type, Compare, Allocator>			iterator;
			typedef typename ft::bidirectional_iterator<const value_type, Compare, Allocator>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>										reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>								const_reverse_iterator;

			class value_compare : public std::binary_function<value_type, value_type, bool> {
				friend class map;
				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator()( const value_type& lhs, const value_type& rhs ) const {
						return comp(lhs.first, rhs.first);
					}
			};
			/******************** Member functions ********************/
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _cmp(comp), _size(0) {}
			template <class InputIterator> map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) {
				_cmp = comp;
				_alloc = alloc;
				_size = static_cast<size_type>(std::distance(first, last));
				for (; first != last; ++first) {
					Node<value_type, Allocator>*	node = _avl.search(_avl.root, *first);
					if (!node)
						_avl.insert(*first);
				}
			}
			map (const map& x) {_size = 0; *this = x;}
			map& operator=( const map& other ) {
				clear();
				_avl.clone(other._avl.root);
				_size = other.size();
				return *this;
			}
			~map() {clear();}
			allocator_type get_allocator() const {return _alloc;}
			/******************** Element access ********************/
			T& at( const Key& key ) {
				Node<value_type, Allocator>*	node = _avl.search(_avl.root, ft::make_pair(key, mapped_type()));
				if (node)
					return node->data->second;
				else
					throw std::out_of_range("Element not found");
			}
			const T& at( const Key& key ) const {
				Node<value_type, Allocator>*	node = _avl.search(_avl.root, ft::make_pair(key, mapped_type()));
				if (node)
					return node->data->second;
				else
					throw std::out_of_range("Element not found");
			}
			T& operator[]( const Key& key ) {
				value_type	p = ft::make_pair<const key_type, mapped_type>(key, mapped_type());
				Node<value_type, Allocator>* node = _avl.search(_avl.root, p);
				if (!node) {
					node = _avl.insert(p);
					_size++;
					return (_avl.search(_avl.root, p))->data->second;
				}
				return node->data->second;
			}
			/******************** Iterators ********************/
			iterator begin() {return iterator(_avl.minNode(_avl.root) ? _avl.minNode(_avl.root)->data : NULL, &_avl);}
			const_iterator begin() const {return iterator(_avl.minNode(_avl.root) ? _avl.minNode(_avl.root)->data : NULL, &_avl);}
			iterator end() {return iterator(NULL, &_avl);}
			const_iterator end() const {return iterator(NULL, &_avl);}
			reverse_iterator rbegin() {return reverse_iterator(end());}
			const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
			reverse_iterator rend() {return reverse_iterator(begin());}
			const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
			/******************** Capacity ********************/
			bool empty() const {return _size == 0 ? true : false;}
			size_type size() const {return _size;}
			size_type max_size() const {return _avl.max_size();}
			/******************** Modifiers ********************/
			void clear() {
				_avl.preOrder(_avl.root);
				_avl.root = NULL;
				_size = 0;
			}
			ft::pair<iterator, bool> insert( const value_type& value ) {
				Node<value_type, Allocator>* node = _avl.search(_avl.root, value);
				bool nodeNotFound = false;
				if (!node) {
					nodeNotFound = true;
					node = _avl.insert(value);
					_size++;
				}
				return ft::pair<iterator, bool>(iterator(node->data, &_avl), nodeNotFound);
			}
			iterator insert( iterator pos, const value_type& value ) {
				(void) pos;
				return insert(value).first;
			}
			template <class InputIt> void insert (InputIt first, InputIt last) {
				for(; first != last; ++first)
					insert(*first);
			}
			void erase( iterator pos ) {
				if(_avl.deleteNode(*pos))
					_size--;
			}
			void erase( iterator first, iterator last ) {
				ft::vector<key_type> keys;
				for (;first != last; ++first)
					keys.push_back(first->first);
				for(size_t i = 0; i < keys.size(); i++)
					erase(keys[i]);
			}
			size_type erase( const Key& key ) {
				size_type n = _avl.deleteNode(ft::make_pair(key, mapped_type()));
				if (n)
					_size--;
				return n;
			}
			void swap( map& other ) {
				map	tmp = other;
				other = *this;
				*this = tmp;
			}
			/******************** Lookup ********************/
			size_type count( const Key& key ) const {
				Node<value_type, Allocator>* node = _avl.search(_avl.root, ft::make_pair(key, mapped_type()));
				return node ? 1 : 0;
			}
			iterator find( const Key& key ) {
				Node<value_type, Allocator>* node = _avl.search(_avl.root, ft::make_pair(key, mapped_type()));
				return node ? iterator(node->data, &_avl) : iterator(NULL, &_avl);
			}
			const_iterator find( const Key& key ) const {
				Node<value_type, Allocator>* node = _avl.search(_avl.root, ft::make_pair(key, mapped_type()));
				return node ? iterator(node->data, &_avl) : iterator(NULL, &_avl);
			}
			iterator lower_bound( const Key& key ) {
				Node<value_type, Allocator>* rootTmp = _avl.root;	
				Node<value_type, Allocator>* res = _avl.root;

				while (rootTmp) {
					if (!_cmp(rootTmp->data->first, key)) {
						res = rootTmp;
						rootTmp = rootTmp->left;
					}
					else
						rootTmp = rootTmp->right;
				}
				return res ? iterator(res->data, &_avl) : iterator(NULL, &_avl);
			}
			const_iterator lower_bound( const Key& key ) const {
				Node<value_type, Allocator>*	rootTmp = _avl.root;	
				Node<value_type, Allocator>*	res = _avl.root;

				while (rootTmp) {
					if (!_cmp(rootTmp->data->first, key)) {
						res = rootTmp;
						rootTmp = rootTmp->left;
					}
					else
						rootTmp = rootTmp->right;
				}
				return res ? iterator(res->data, &_avl) : iterator(NULL, &_avl);
			}
			iterator upper_bound( const Key& key ) {
				Node<value_type, Allocator>*	rootTmp = _avl.root;	
				Node<value_type, Allocator>*	res = _avl.root;

				while (rootTmp) {
					if (_cmp(key, rootTmp->data->first)) {
						res = rootTmp;
						rootTmp = rootTmp->left;
					}
					else
						rootTmp = rootTmp->right;
				}
				return res ? iterator(res->data, &_avl) : iterator(NULL, &_avl);
			}
			const_iterator upper_bound( const Key& key ) const {
				Node<value_type, Allocator>*	rootTmp = _avl.root;	
				Node<value_type, Allocator>*	res = _avl.root;

				while (rootTmp) {
					if (_cmp(key, rootTmp->data->first)) {
						res = rootTmp;
						rootTmp = rootTmp->left;
					}
					else
						rootTmp = rootTmp->right;
				}
				return res ? iterator(res->data, &_avl) : iterator(NULL, &_avl);
			}
			ft::pair<iterator,iterator> equal_range( const Key& key ) {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}
			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}
			
			/******************** Observers ********************/
			key_compare key_comp() const {
				return _cmp;
			}
			value_compare value_comp() const {
				return value_compare(_cmp);
			}
	};
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	lit = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	rit = rhs.begin();
		for (; lit != lhs.end(); ++lit, ++rit) {
			if (*lit != *rit)
				return false;
		}
		return true;
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs > rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}