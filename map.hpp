/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 11:13:15 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/10/22 19:02:57 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterators.hpp"
#include "pair.hpp"

namespace ft {

	template< class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> > > class map {

		private:
			Tree<ft::pair<Key, T> , Compare, Allocator>*	_avl;
			Allocator										_alloc;
			Compare											_cmp;
			std::size_t										_size;
		
		public:
			typedef Key																			Key_type;
			typedef T																			mapped_type;
			typedef ft::pair<Key_type, mapped_type>												value_type;
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
				: _cmp(comp) , _alloc(alloc), _size(0) {}
			template <class InputIterator> map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) {
				_size = static_cast<size_type>(std::distance(first, last));
				for (; first != last; ++first) {
					Node<T, Allocator>*	node = _avl->search(_avl->root, *first);
					if (!node)
						_avl->insert(*first);
				}
			}
			map (const map& x) {_size = 0; *this = x;}
			map& operator=( const map& other ) {
				clear();
				_avl->clone(other._avl);
				_size = other.size();
			}
			~map() {clear();}
			allocator_type get_allocator() const {return _alloc;}
			/******************** Element access ********************/
			T& at( const Key& key ) {
				Node<T, Allocator>*	node = _avl->search(_avl->root, key);
				if (node)
					return node->data->second;
				else
					throw std::out_of_range("Element not found");
			}
			const T& at( const Key& key ) const {return static_cast<const T&>(at(key));}
			T& operator[]( const Key& key ) {
				Node<T, Allocator>*	node = _avl->search(_avl->root, key);
				if (!node) {
					node = _avl->insert(key);
					_size++;
					return node->data->second;
				}
				return node->data->second;
			}
			/******************** Iterators ********************/
			iterator begin() {return iterator(_avl->minNode() ? _avl->minNode()->data : NULL, _avl);}
			const_iterator begin() const {return const_iterator(_avl->minNode() ? _avl->minNode().data : NULL, _avl);}
			iterator end() {return iterator(NULL, _avl);}
			const_iterator end() const {return const_iterator(NULL, _avl);}
			reverse_iterator rbegin() {return reverse_iterator(end());}
			const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
			reverse_iterator rend() {return reverse_iterator(begin());}
			const_reverse_iterator rend() const {return const_reference(begin());}
			/******************** Capacity ********************/
			bool empty() const {return _size == 0 ? true : false;}
			size_type size() const {return _size;}
			size_type max_size() const {return _alloc.max_size();}
			/******************** Modifiers ********************/
			void clear() {
				_avl->preOrder(_avl->root);
				_avl->root = NULL;
				_size = 0;
			}
			std::pair<iterator, bool> insert( const value_type& value ) {
				
			}
			iterator insert( iterator pos, const value_type& value ) {
				
			}
			template <class InputIt> void insert (InputIt first, InputIt last) {
				
			}
	};
}