#ifndef __PROJ_FOUR_CRUMPLE_TREE_HPP
#define __PROJ_FOUR_CRUMPLE_TREE_HPP

#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>


class ElementNotFoundException : public std::runtime_error 
{
public:
	explicit ElementNotFoundException(const std::string & err) : std::runtime_error(err) {}
};

template<typename Key, typename Value> class Node{
	public:
	Key key;
	Value value;
	Node* left;
	Node* right;
	Node* parent;
	int status[3];
	int level;

	public: Node(){
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

	public: Node(Key key1, Value value1){
		key = key1;
		value = value1;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

template<typename Key, typename Value>
class CrumpleTree
{
private:
	Node<Key, Value>* root;
	unsigned countNode;
	void destructRecursive(Node<Key, Value>* node);
	std::vector<Key> inOrderRecursive(Node<Key, Value>* node, std::vector<Key>& foo) const;
	std::vector<Key> preOrderRecursive(Node<Key, Value>* node, std::vector<Key>& foo) const;
	std::vector<Key> postOrderRecursive(Node<Key, Value>* node, std::vector<Key>& foo) const;


public:
	CrumpleTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	CrumpleTree(const CrumpleTree & st);
	//	CrumpleTree & operator=(const CrumpleTree & st);


	// The destructor is required. 
	~CrumpleTree();

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const noexcept; 

	// returns the level on which the node with this key resides.
	// If !contains(k), this will throw an ElementNotFoundException
	unsigned getLevel(const Key & k) const;

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const CrumpleTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the balancing operation(s) if needed
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);


	// Deletes the given key from the tree
	// and performs the balancing operation(s) if needed.
	// If the key does not exist in the tree, 
	// do not modify the tree.
	void remove(const Key &k);


	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;


};


template<typename Key, typename Value>
CrumpleTree<Key,Value>::CrumpleTree()
{
	root = nullptr;
	countNode = 0;
}

template<typename Key, typename Value>
CrumpleTree<Key,Value>::~CrumpleTree()
{
	destructRecursive(root);
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::destructRecursive(Node<Key, Value>* node)
{
	if(node == nullptr){
		return;
	}

	this->destructRecursive(node->left);
	this->destructRecursive(node->right);
	delete node;
}


template<typename Key, typename Value>
size_t CrumpleTree<Key, Value>::size() const noexcept
{
	return countNode;
}

template<typename Key, typename Value>
bool CrumpleTree<Key, Value>::isEmpty() const noexcept
{
	if(countNode == 0){
		return true;
	}else{
		return false;
	}
}


template<typename Key, typename Value>
bool CrumpleTree<Key, Value>::contains(const Key &k) const noexcept
{
	Node<Key, Value>* current = root;
	while(current != nullptr){
		if(current->key == k){
			return true;
		}
		if(k < current->key){
			current = current->left;
		}else if(current->key < k){
			current = current->right;
		}
	}	
	return false;
}

template<typename Key, typename Value>
unsigned CrumpleTree<Key, Value>::getLevel(const Key & k) const
{
	Node<Key, Value>* current = root;
	while(current != nullptr){
		if(current->key == k){
			std::cout << k << " is in level " << current->level << std::endl;
			return current->level;
		}
		if(k < current->key){
			current = current->left;
		}else if(current->key < k){
			current = current->right;
		}
	}	
	throw ElementNotFoundException("element was not in the tree");
}




template<typename Key, typename Value>
Value & CrumpleTree<Key, Value>::find(const Key & k)
{
	Node<Key, Value>* current = root;
	std::cout << "FIND: " << k << std::endl;
	while(current != nullptr){
		std::cout << current->key << "→";
		if(current->key == k){
			std::cout << std::endl;
			return current->value;
		}
		if(k < current->key){
			current = current->left;
		}else if(current->key < k){
			current = current->right;
		}
	}	
	throw ElementNotFoundException("element was not in the tree");
}

template<typename Key, typename Value>
const Value & CrumpleTree<Key, Value>::find(const Key & k) const
{
	Node<Key, Value>* current = root;
	while(current != nullptr){
		if(current->key == k){
			return current->value;
		}
		if(k < current->key){
			current = current->left;
		}else if(current->key < k){
			current = current->right;
		}
	}	
	throw ElementNotFoundException("element was not in the tree");
}


template<typename Key, typename Value>
void CrumpleTree<Key, Value>::insert(const Key & k, const Value & v)
{
	Node<Key, Value>* newNode = new Node(k, v);
	newNode->level = 1;
	newNode->status[0] = 1;
	newNode->status[1] = 1;
	newNode->status[2] = 0;

	//insert at a root if tree is empty
	if(countNode == 0){
		root = newNode;
		countNode += 1;
		std::cout << "put root" << std::endl;
		return;
	}
	std::cout << "start finding" << std::endl;
	//if not empty, find level 0 to fit
	Node<Key, Value>* previous = root;
	Node<Key, Value>* current = root;
	while(current != nullptr){
		if(current->key == k){
			return;
		}
		previous = current;
		if(k < current->key){
			current = current->left;
		}else if(current->key < k){
			current = current->right;
		}
	}	
	std::cout << "found position" << std::endl;
	std::cout << "previous: " << previous->key << std::endl;
	//return if element is already in the tree
	current = newNode;
	current->parent = previous;
	/*
	親を見る
	親より低い
		終わり
	同じ高さにいる
	自分が左の時
		(0, 1)なら親を上げる
		(0, 2)なら自分を振り返る
			自分が(1, 2)なら親を下げる
			自分が(2, 1)なら親と自分を下げて間の子を上げる
	*/
	if(current->key < current->parent->key){//currentとparentを更新
		current->parent->left = current;
		current->parent->status[0] = (current->parent->level)-(current->level);
		current->status[2] = current->parent->status[0];
	}else{
		current->parent->right = current;
		current->parent->status[1] = (current->parent->level)-(current->level);
		current->status[2] = current->parent->status[1];
	}
	std::cout << "start while" << std::endl;
	while(true){
		std::cout << "current: " << current->key << std::endl;
		if(current == root){
			countNode += 1;
			return;
		}
		if(current->level < current->parent->level){//親より低いので終わり
			std::cout << "current level: " << current->level << ", parent level: " << current->parent->level << std::endl;
			if(current->key < current->parent->key){
				current->parent->status[0] = 1;
			}else{
				current->parent->status[1] = 1;
			}
			current->status[2] = 1;
			countNode += 1;
			return;
		}else if(current->level == current->parent->level){//親と同じ高さなので親は(0, ?, ?)
			std::cout << "need to adjust. " << current->level << ", " << current->parent->level << std::endl;
			if(current->key < current->parent->key){//親の左なら
				if(current->parent->status[1] == 1){//親が(0, 1)なら親を上げる
					current->parent->level += 1;
					current->parent->status[0] = 1;
					current->parent->status[1] = 2;
					current->parent->status[2] -= 1;
					current->status[2] = 1;
					current = current->parent;
					std::cout << "move " << current->key << " up in level " << current->level << std::endl;
				}else if(current->parent->status[1] == 2){//親が(0, 2)なら自分を振り返る
					if(current->status[0] == 1 && current->status[1] == 2){//自分が(1, 2)なら親を下げる
						std::cout << "pattern (1, 2)" << std::endl;
						current->parent->level -= 1;
						current->parent->left = current->right;
						if(current->right != nullptr){
							current->right->parent = current->parent;
						}
						current->right = current->parent;
						current->parent = current->right->parent;
						if(current->parent != nullptr){
							if(current->parent->key < current->key){//親の親のどっちだったかを調べて変えてあげる
								current->parent->right = current;
							}else{
								current->parent->left = current;
							}
						}else{
							root = current;
						}
						current->right->parent = current;
						current->right->status[0] = 1;
						current->right->status[1] = 1;
						current->status[0] = 1;
						current->status[1] = 1;
						current->status[2] = current->right->status[2];
						current->right->status[2] = 1;
						countNode += 1;
						return;
					}else{//自分が(2, 1)なら親と自分を下げて、自分の親側の子を上げる
						std::cout << "pattern (2, 1)" << std::endl;
						current->level -= 1;
						current->parent->level -= 1;
						current->right->level += 1;
						current->status[0] = 1;
						current->status[1] = current->right->status[0];
						current->parent->status[0] = current->right->status[1];
						current->parent->status[1] = 1;
						current->right->status[0] = 1;
						current->right->status[1] = 1;
						current->status[2] = 1;
						current->right->status[2] = current->parent->status[2];
						current->parent->status[2] = 1;
						current->parent->left = current->right->right;
						if(current->parent->left != nullptr){
							current->parent->left->parent = current->parent;
						}
						current->right->parent = current->parent->parent;
						if(current->parent->parent != nullptr){
							if(current->right->key < current->parent->parent->key){//親の親のどっちだったかを調べて変えてあげる
								current->parent->parent->left = current->right;
							}else{
								current->parent->parent->right = current->right;
							}
						}else{
							root = current->right;
						}
						current->right->right = current->parent;
						current->parent->parent = current->right;
						current->parent = current->right;
						current->right = current->right->left;
						if(current->right != nullptr){
							current->right->parent = current;
						}
						current->parent->left = current;
						countNode += 1;
						return;
					}
				}
			}else{//親の右なら
				if(current->parent->status[0] == 1){//親が(1, 0)なら親を上げる
					current->parent->level += 1;
					current->parent->status[1] = 1;
					current->parent->status[0] = 2;
					if(current->parent->status[2] != 0){
						current->parent->status[2] -= 1;
					}
					current->status[2] = 1;
					current = current->parent;
					std::cout << "move " << current->key << " up in level " << current->level << std::endl;
				}else if(current->parent->status[0] == 2){//親が(2, 0)なら自分を振り返る
					if(current->status[1] == 1 && current->status[0] == 2){//自分が(2, 1)なら親を下げる
						std::cout << "pattern (2, 1)" << std::endl;
						current->parent->level -= 1;
						current->parent->right = current->left;
						std::cout << "success" << std::endl;
						std::cout << "current: " << current->key << std::endl;
						if(current->left != nullptr){
						current->left->parent = current->parent;
						}
						std::cout << "success2" << std::endl;
						current->left = current->parent;
						current->parent = current->left->parent;
						std::cout << "success3" << std::endl;
						if(current->parent != nullptr){
							if(current->parent->key < current->key){//親の親のどっちだったかを調べて変えてあげる
								current->parent->right = current;
							}else{
								current->parent->left = current;
							}
						}else{
							root = current;
						}
						current->left->parent = current;
						current->left->status[1] = 1;
						current->left->status[0] = 1;
						current->status[0] = 1;
						current->status[1] = 1;
						current->status[2] = current->left->status[2];
						current->left->status[2] = 1;
						countNode += 1;
						return;
					}else{//自分が(1, 2)なら親と自分を下げて、自分の親側の子を上げる
						current->level -= 1;
						current->parent->level -= 1;
						current->left->level += 1;
						current->status[1] = 1;
						current->status[0] = current->left->status[1];
						current->parent->status[1] = current->left->status[0];
						current->parent->status[0] = 1;
						current->left->status[1] = 1;
						current->left->status[0] = 1;
						current->status[2] = 1;
						current->left->status[2] = current->parent->status[2];
						current->parent->status[2] = 1;
						current->parent->right = current->left->left;
						if(current->parent->right != nullptr){
							current->parent->right->parent = current->parent;
						}
						current->left->parent = current->parent->parent;
						if(current->parent->parent != nullptr){
							if(current->left->key < current->parent->parent->key){//親の親のどっちだったかを調べて変えてあげる
								current->parent->parent->left = current->left;
							}else{
								current->parent->parent->right = current->left;
							}
						}else{
							root = current->left;
						}
						current->left->left = current->parent;
						current->parent->parent = current->left;
						current->parent = current->left;
						current->left = current->left->right;
						if(current->left != nullptr){
							current->left->parent = current;
						}
						current->parent->right = current;
						countNode += 1;
						return;
					}
				}
			}
		}

	}
}


template<typename Key, typename Value>
void CrumpleTree<Key, Value>::remove(const Key &k)
{	
	std::cout << "Try to remove " << k << std::endl;
	Node<Key, Value>* current = root;
	Node<Key, Value>* nodeToRemove;
	while(current != nullptr){
		if(current->key == k){
			break;
		}
		if(k < current->key){
			current = current->left;
		}else if(current->key < k){
			current = current->right;
		}
	}
	nodeToRemove = current;
	if(current == nullptr){
		return;
	}
	std::cout << "nodeToRemove: " << nodeToRemove->key << std::endl; 
	if(current->level != 1){//消したいノードがレベル1じゃないなら
	std::cout << "need to swap. " << current -> key << " is in level " << current->level << std::endl;
		if(current->left != nullptr){//左下がnullptrじゃないなら
			current = current->left;//左下に1つ移動して
			if(current->right == nullptr){//もう右下がないなら左下と交換
				std::cout << "swap " << current->key << " and " << nodeToRemove->key << std::endl;
				if(root == nodeToRemove){
					root = current;
				}
				int temp = current->level;
				current->level = nodeToRemove->level;
				nodeToRemove->level = temp;
	
				temp = nodeToRemove->status[0];
				nodeToRemove->status[0] = current->status[0];
				current->status[0] = temp;
				temp = nodeToRemove->status[1];
				nodeToRemove->status[1] = current->status[1];
				current->status[1] = temp;
				temp = nodeToRemove->status[2];
				nodeToRemove->status[2] = current->status[2];
				current->status[2] = temp;
				if(nodeToRemove->parent != nullptr){
					if(nodeToRemove->parent->left == nodeToRemove){
						nodeToRemove->parent->left = current;
					}else{
						nodeToRemove->parent->right = current;
					}
				}
				current->parent = nodeToRemove->parent;
				nodeToRemove->parent = current;
				nodeToRemove->left = current->left;
				current->right = nodeToRemove->right;
				current->left = nodeToRemove;
				nodeToRemove->right = nullptr;
				if(current->right != nullptr){
					current->right->parent = current;
				}
				if(current->left != nullptr){
					current->left->parent = current;
				}
				if(nodeToRemove->left != nullptr){
					nodeToRemove->left->parent = nodeToRemove;
				}

				
				//std::cout << "right of " << current->key << " is " << current->right->key << std::endl;
			}else{//まだたどり着いてないなら
				while(current->right != nullptr){//右下に限界まで移動
					current = current->right;
				}
				std::cout << "current: " << current->key << std::endl;
				std::cout << "swap " << current->key << " and " << nodeToRemove->key << std::endl;
				//swap two nodes
				if(root == nodeToRemove){
					root = current;
				}
				int temp = current->level;
				current->level = nodeToRemove->level;
				nodeToRemove->level = temp;
	
				temp = nodeToRemove->status[0];
				nodeToRemove->status[0] = current->status[0];
				current->status[0] = temp;
				temp = nodeToRemove->status[1];
				nodeToRemove->status[1] = current->status[1];
				current->status[1] = temp;
				temp = nodeToRemove->status[2];
				nodeToRemove->status[2] = current->status[2];
				current->status[2] = temp;

				Node<Key, Value>* tempNode;
				tempNode = current->parent;
				if(nodeToRemove->parent != nullptr){
					if(nodeToRemove->parent->key < nodeToRemove->key){
						nodeToRemove->parent->right = current;
					}else{
						nodeToRemove->parent->left = current;
					}
					current->parent = nodeToRemove->parent;
				}else{
					current->parent = nullptr;
				}
				nodeToRemove->parent = tempNode;
				nodeToRemove->parent->right = nodeToRemove;

				tempNode = current->right;
				current->right = nodeToRemove->right;
				nodeToRemove->right = tempNode;

				tempNode = current->left;
				current->left = nodeToRemove->left;
				nodeToRemove->left = tempNode;

				if(current->right != nullptr){
					current->right->parent = current;
				}
				if(current->left != nullptr){
					current->left->parent = current;
				}
				if(nodeToRemove->left != nullptr){
					nodeToRemove->left->parent = nodeToRemove;
				}

				std::cout << "current->left: " << current->left->key << std::endl;
				std::cout << "current->left->parent: " << current->left->parent->key << std::endl;
			}
			if(nodeToRemove->left != nullptr){//左下にもう1つあったら入れ替える
				std::cout << "swap " << nodeToRemove->left->key << " and " << nodeToRemove->key << std::endl;
				nodeToRemove->left->level = 2;
				nodeToRemove->level = 1;
				nodeToRemove->left->status[2] = nodeToRemove->status[2];

				nodeToRemove->status[1] = 1;
				nodeToRemove->status[2] = 1;
				nodeToRemove->left->status[1] = 2;

				nodeToRemove->left->left = nodeToRemove;
				if(nodeToRemove->parent != nullptr){
					if(nodeToRemove->parent->left == nodeToRemove){
						nodeToRemove->parent->left = nodeToRemove->left;
					}else{
						nodeToRemove->parent->right = nodeToRemove->left;
					}
				}
				nodeToRemove->left->parent = nodeToRemove->parent;
				nodeToRemove->parent = nodeToRemove->left;
				nodeToRemove->left = nullptr;
			}
		}else{//左下がnullptrなので、右下に移動する。レベルが1じゃないので、右下は必ずある
			std::cout << "swap " << nodeToRemove << " and " << nodeToRemove->right << std::endl;
			if(root == nodeToRemove){
					root = nodeToRemove->right;
			}
			nodeToRemove->right->level = 2;
				nodeToRemove->level = 1;
				nodeToRemove->right->status[2] = nodeToRemove->status[2];
				nodeToRemove->status[0] = 1;
				nodeToRemove->status[2] = 1;
				nodeToRemove->right->status[0] = 2;

				nodeToRemove->right->right = nodeToRemove;
				if(nodeToRemove->parent != nullptr){
					if(nodeToRemove->parent->left == nodeToRemove){
						nodeToRemove->parent->left = nodeToRemove->right;
					}else{
						nodeToRemove->parent->right = nodeToRemove->right;
					}
				}
				nodeToRemove->right->parent = nodeToRemove->parent;
				nodeToRemove->parent = nodeToRemove->right;
				nodeToRemove->right = nullptr;
		}
	}
	//もしレベルが1なのに親がいないなら、rootだけのサイズ1のtree
	//それを消して終了
	if(nodeToRemove->parent == nullptr){
		delete nodeToRemove;
		root = nullptr;
		countNode -= 1;
		return;
	}

	//普通に消す
	current = nodeToRemove->parent;
	if(current->right == nodeToRemove){
		current->status[1] += 1;
		current->right = nullptr;
		delete nodeToRemove;
	}else{
		current->status[0] += 1;
		current->left = nullptr;
		delete nodeToRemove;
	}
	countNode -= 1;
	std::cout << "deleted " << k << std::endl;

	//もし消したら親が(2, 2)になったなら
	if(current->status[0] == 2 && current->status[1] == 2){
		std::cout << current->key << " is (" << current->status[0] << ", " << current->status[1] << "). move down." << std::endl; 
		current->level = 1;
		current->status[0] = 1;
		current->status[1] = 1;
		if(current->parent != nullptr){
			if(current->key < current->parent->key){
				current->parent->status[0] += 1;
			}else{
				current->parent->status[1] += 1;
			}
			current->status[2] += 1;
			current = current->parent;
		}else{
			return;
		}
	}
	std::cout << "current: " << current->key << std::endl;
	while(current != nullptr){
		Node<Key, Value>* tempNode;
		if(current->status[1] == 3){//(1or2, 3)なら
			std::cout << "move " << current->key << " down." << std::endl;
			current->level -= 1;//1 level down
			if(current->parent != nullptr){
				if(current->parent->key < current->key){
					current->parent->status[1] += 1;
				}else{
					current->parent->status[0] += 1;
				}
				current->status[2] += 1;
			}
			current->status[1]  = 2;
			current->status[0] -= 1;
			current->left->status[2] -= 1;
			if(current->status[0] == 0){//同じ高さにいたら
				if(current->left -> status[0] == 1){//一緒にいるやつが(1, 1)か(1, 2)なら
					std::cout << "move " << current->left->key << " up." <<std::endl;
					current->left->level += 1;
					std::cout <<"parent: " << current->parent->key << std::endl;
					if(current->parent != nullptr){
						if(current->parent->right == current){
							current->parent->right = current->left;
							current->parent->status[1] = (current->parent->level - current->left->level);
							current->left->status[2] = current->parent->status[1];
						}else{
							std::cout << "here" << std::endl;
							current->parent->left = current->left;
							current->parent->status[0] = (current->parent->level - current->left->level);
							current->left->status[2] = current->parent->status[0];
						}
					}
					std::cout << "root: " << root->key << ", left: " << root->left->key << std::endl;
					std::cout << "parent: " << current->parent->key << ", left: " << current->parent->left->key << std::endl;

					current->left->parent = current->parent;
					if(current->left->left != nullptr){
						current->left->left->status[2] = 2;
					}
					current->left->status[0] = 2;
					current->status[0] = current->left->status[1];
					current->status[2] = 1;
					current->left->status[1] = 1;
					tempNode = current->left->right;
					current->left->right = current;
					current->parent = current->left;
					current->left = tempNode;
					if(current->left != nullptr){
						current->left->parent = current;
					}
					std::cout << "after moving up in (1, 1) or (1, 2). current: " << current->key << std::endl;
					std::cout << current->key << " = (" << current->status[0] << ", " << current->status[1] << ", " << current->status[2] << "). in level " << current->level << std::endl;
					//もし下げたノードが葉で(2, 2)なら
					if(current->level == 2 && current->status[0] == 2 && current->status[1] == 2){
						std::cout << current->key << " was level 2 leaf. move down." << std::endl;
						current->level = 1;
						current->status[0] = 1;
						current->status[1] = 1;
						current->status[2] = 2;
						current->parent->status[1] = 2;
					}
					if(current->parent->parent == nullptr){
						root = current->parent;
					}
					return;
				}else if(current->left->status[0] == 2 && current->left->status[1] == 2){//(2, 2)なら下げる
					current->left->level -= 1;
					current->left->status[0] = 1;
					current->left->status[1] = 1;
					current->left->status[2] = 1;
					current->status[0] = 1;
					if(current->left->left != nullptr){
						current->left->left->status[2] = 1;
					}
					if(current->left->right != nullptr){
						current->left->right->status[2] = 1;
					}
				}else if(current->left->status[0] == 2 && current->left->status[1] == 1){//(2, 1)なら自分と親を下げて間の子を上げる
					current->level -= 1;
					current->left->level -= 1;
					current->left->right->level += 2;
					current->left->status[0] = 1;
					current->left->status[1] = current->left->right->status[0];
					current->status[0] = current->left->right->status[1];
					current->status[1] = 1;
					current->left->right->status[0] = 2;
					current->left->right->status[1] = 2;
					if(current->parent != nullptr){
						current->left->right->status[2] = (current->status[2] - 1);
					}else{
						current->left->right->status[2] = 0;
					}
					current->status[2] = 2;
					current->left->status[2] = 2;
					if(current->parent != nullptr){
						if(current->parent->key < current->left->right->key){
							current->parent->status[1] = current->left->right->status[2];
							current->parent->right = current->left->right;
						}else{
							current->parent->status[0] = current->left->right->status[2];
							current->parent->left = current->left->right;
						}
					}
					current->left->right->parent = current->parent;
					current->parent = current->left->right;
					current->left->right = current->parent->left;
					if(current->left->right != nullptr){
						current->left->right->parent = current->left;
					}
					current->parent->left = current->left;
					current->left->parent = current->parent;
					
					current->left = current->parent->right;
					current->parent->right = current;
					if(current->left != nullptr){
						current->left->parent = current;
					}
					if(current->parent->parent == nullptr){
						root = current->parent;
					}
					return;
				}
			}
			if(current->parent == nullptr){
				return;
			}else{
				current = current->parent;
			}

		}else if(current->status[0] == 3){//左右逆で(3, 1or2)なら
			std::cout << "move " << current->key << " down." << std::endl;
			current->level -= 1;//1 level down
			if(current->parent != nullptr){
				if(current->parent->right == current){
					current->parent->status[1] += 1;
				}else{
					current->parent->status[0] += 1;
				}
				current->status[2] += 1;
			}
			current->status[0]  = 2;
			current->status[1] -= 1;
			current->right->status[2] -= 1;
			if(current->status[1] == 0){//同じ高さにいたら
				if(current->right -> status[1] == 1){//一緒にいるやつが(1, 1)か(2, 1)なら

					std::cout << "move " << current->right->key << " up." <<std::endl;
					current->right->level += 1;
					if(current->parent != nullptr){
						if(current->parent->right ==  current){
							current->parent->right = current->right;
							current->parent->status[1] = (current->parent->level - current->right->level);
							current->right->status[2] = current->parent->status[1];
						}else{
							current->parent->left = current->right;
							current->parent->status[0] = (current->parent->level - current->right->level);
							current->right->status[2] = current->parent->status[0];
						}
					}
					current->right->parent = current->parent;
					if(current->right->right != nullptr){
						current->right->right->status[2] = 2;
					}
					current->right->status[1] = 2;
					current->status[1] = current->right->status[0];
					current->status[2] = 1;
					current->right->status[0] = 1;
					tempNode = current->right->left;
					current->right->left = current;
					current->parent = current->right;
					current->right = tempNode;
					if(current->right != nullptr){
						current->right->parent = current;
					}

					//もし下げたノードが葉で(2, 2)なら
					if(current->level == 2 && current->status[0] == 2 && current->status[1] == 2){
						current->level = 1;
						current->status[0] = 1;
						current->status[1] = 1;
						current->status[2] = 2;
						current->parent->status[0] = 2;
					}
					if(current->parent->parent == nullptr){
						root = current->parent;
					}
					return;
				}else if(current->right->status[0] == 2 && current->right->status[1] == 2){//(2, 2)なら下げる
					current->right->level -= 1;
					current->right->status[0] = 1;
					current->right->status[1] = 1;
					current->right->status[2] = 1;
					current->status[1] = 1;
					if(current->right->right != nullptr){
						current->right->right->status[2] = 1;
					}
					if(current->right->left != nullptr){
						current->right->left->status[2] = 1;
					}
				}else if(current->right->status[0] == 1 && current->right->status[1] == 2){//(1, 2)なら自分と親を下げて間の子を上げる
					current->level -= 1;
					current->right->level -= 1;
					current->right->left->level += 2;
					current->right->status[1] = 1;
					current->right->status[0] = current->right->left->status[1];
					current->status[1] = current->right->left->status[0];
					current->status[0] = 1;
					current->right->left->status[0] = 2;
					current->right->left->status[1] = 2;
					if(current->parent != nullptr){
						current->right->left->status[2] = (current->status[2] - 1);
					}else{
						current->right->left->status[2] = 0;
					}
					current->status[2] = 2;
					current->right->status[2] = 2;
					if(current->parent != nullptr){
						if(current->parent->key < current->right->left->key){
							current->parent->status[1] = current->right->left->status[2];
							current->parent->right = current->right->left;
						}else{
							current->parent->status[0] = current->right->left->status[2];
							current->parent->left = current->right->left;
						}
					}
					current->right->left->parent = current->parent;
					current->parent = current->right->left;
					current->right->left = current->parent->right;
					if(current->right->left != nullptr){
						current->right->left->parent = current->right;
					}
					current->parent->right = current->right;
					current->right->parent = current->parent;
					
					current->right = current->parent->left;
					current->parent->left = current;
					if(current->right != nullptr){
						current->right->parent = current;
					}
					if(current->parent->parent == nullptr){
						root = current->parent;
					}
					return;
				}
			}
			if(current->parent == nullptr){
				return;
			}else{
				current = current->parent;
			}
		}else{
			return;
		}
	}
	return;
}



template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::inOrder() const
{
	std::vector<Key> foo;
	foo = this->inOrderRecursive(root, foo);

	return foo; 
}

template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::inOrderRecursive(Node<Key, Value>* node, std::vector<Key>& foo) const
{
	if(node == nullptr){
		return foo;
	}

	this->inOrderRecursive(node->left, foo);
	foo.push_back(node->key);
	this->inOrderRecursive(node->right, foo);
	
	return foo; 
}


template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::preOrder() const
{
	std::vector<Key> foo;
	foo = this->preOrderRecursive(root, foo);

	return foo; 
}


template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::preOrderRecursive(Node<Key, Value>* node, std::vector<Key>& foo) const
{
	if(node == nullptr){
		return foo;
	}

	foo.push_back(node->key);
	this->preOrderRecursive(node->left, foo);
	this->preOrderRecursive(node->right, foo);
	
	return foo; 
}

template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::postOrder() const
{
	std::vector<Key> foo;
	foo = this->postOrderRecursive(root, foo);
	return foo; 
}

template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::postOrderRecursive(Node<Key, Value>* node, std::vector<Key>& foo) const
{
	if(node == nullptr){
		return foo;
	}

	this->postOrderRecursive(node->left, foo);
	this->postOrderRecursive(node->right, foo);
	foo.push_back(node->key);
	
	return foo; 
}





#endif 