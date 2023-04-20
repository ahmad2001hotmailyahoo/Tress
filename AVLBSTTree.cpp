// AVL /binary search tree implementation

#include<iostream>
#include<math.h>
#include <queue>
/// <summary>
/// LL Rotation
///			      5(2)		 4(1)
///			  4(1)   =>  3(0)	 5(0)
///		  3(0)		
/// RR Rotation
///			5(2)			  6(1)
///				6(1)   =>  5(0)   7(0)
///					7(0)		
/// LR Rotation
///			5(2)		        5(2)            4(1)
///		3(1)      =>        4(1)       =>   3(0)    5(0)
///		    4(0)		3(0)
/// RL Rotation
///			5(2)		         5(2)                  6(1)
///				7(1)    =>          6(1)      =>   5(0)    7(0)
///		    6(0)		                7(0)  
/// </summary>

struct AVL_BST_TREE {
	int key;
	AVL_BST_TREE* left;
	AVL_BST_TREE* right;
	int hieght;
};

int getHieght(AVL_BST_TREE* _tree) {
	if (_tree == NULL) return 0;
	else return _tree->hieght;
}

int getBalancedFactor(AVL_BST_TREE* _tree) {
	if (_tree == NULL) return 0;
	else return getHieght(_tree->left) - getHieght(_tree->right);
}

AVL_BST_TREE* createNode(int _key) {
	AVL_BST_TREE* _new_tree_node = new AVL_BST_TREE;
	_new_tree_node->key = _key;
	_new_tree_node->right = _new_tree_node->left = NULL;
	_new_tree_node->hieght = 1;
	return _new_tree_node;
}

int getMax(int _value_left, int _value_right){
	return (_value_left > _value_right) ? _value_left : _value_right;
}

AVL_BST_TREE* LLRotation(AVL_BST_TREE* _tree){
	AVL_BST_TREE* t;
	AVL_BST_TREE* tp;

	t = _tree;
	tp = _tree->left;

	t->left = tp->right;
	tp->right = t;

	return tp;

}

AVL_BST_TREE* RRRotation(AVL_BST_TREE* _tree) {
	AVL_BST_TREE* t;
	AVL_BST_TREE* tp;

	t = _tree;
	tp = t->right;

	t->right = tp->left;
	tp->left = t;

	return tp;

}

AVL_BST_TREE* LRRotation(AVL_BST_TREE* _tree) {
	AVL_BST_TREE* p;
	AVL_BST_TREE* tp;
	AVL_BST_TREE* tp2;

	p = _tree;
	tp = _tree->left;
	tp2 = _tree->left->right;


	p->left = tp2->right;
	tp->right = tp2->left;

	tp2->left=tp;
	tp2->right=p;
	
	return tp2;
}

AVL_BST_TREE* RLRotation(AVL_BST_TREE* _tree) {
	AVL_BST_TREE* p;
	AVL_BST_TREE* tp;
	AVL_BST_TREE* tp2;

	p = _tree;
	tp = _tree->right;
	tp2 = _tree->right->left;


	p->right = tp2->left;
	tp->left = tp2->right;

	tp2->left = p;
	tp2->right = tp;
	

	return tp2;
}

AVL_BST_TREE* insertion(AVL_BST_TREE* _tree, int _key) {
	if (_tree == NULL) {
		return  createNode(_key);

	}
	else if (_tree->key > _key) {
		_tree->left = insertion(_tree->left, _key);
	}
	else if (_tree->key < _key) {
		_tree->right = insertion(_tree->right, _key);
	}

	else if (_tree->key == _key) {
		return _tree;
	}

	_tree->hieght = 1 + getMax(getHieght(_tree->right), getHieght(_tree->left));

	int _balanced_factor = getBalancedFactor(_tree);



		//case1: LL rotation
		
		if (_balanced_factor > 1 && _key < _tree->left->key) {
			AVL_BST_TREE* left= LLRotation(_tree);
			left->hieght = getMax(getHieght(_tree->right), getHieght(_tree->left));
			return left;
		}
		
		///*
#       //case1: RR rotation
		else if (_balanced_factor < -1 && _key > _tree->right->key) {
			AVL_BST_TREE* right =  RRRotation(_tree);
			right->hieght = getMax(getHieght(_tree->right), getHieght(_tree->left));
			return right;
		}
		//*/

		///*
		//case1: LR rotation
		
		else if ( _balanced_factor > 1 && _key > _tree->right->key) {
			AVL_BST_TREE* left = LLRotation(_tree);
			left->hieght = getMax(getHieght(_tree->right), getHieght(_tree->left));
			return left;
		}
		//*/

		//case1: RL rotation
		 if (_balanced_factor < -1 && _key < _tree->left->key) {
			 AVL_BST_TREE* left = LLRotation(_tree);
			 left->hieght = getMax(getHieght(_tree->right), getHieght(_tree->left));
			 return left;
			
		}

	return _tree;
}

void print_tree_preoder(AVL_BST_TREE* _tree) {
	if (_tree == NULL) return;
	std::cout << (_tree->key) <<" , ";
	int _balanced_factor = getBalancedFactor(_tree);
	std::cout << "_value_ == " << _tree->key << "_balanced_factor" << _balanced_factor << " , hieght" << getHieght(_tree) << std::endl;
	print_tree_preoder(_tree->left);
	print_tree_preoder(_tree->right);
}

void print_tree_postoder(AVL_BST_TREE* _tree) {
	if (_tree == NULL) return;
	print_tree_preoder(_tree->left);
	print_tree_preoder(_tree->right);
	std::cout << (_tree->key) << " , ";
	int _balanced_factor = getBalancedFactor(_tree);
	std::cout << "_value_ == " << _tree->key << "_balanced_factor" << _balanced_factor << " , hieght" << getHieght(_tree) << std::endl;
}

void print_tree_inoder(AVL_BST_TREE* _tree) {
	if (_tree == NULL) return;
	print_tree_preoder(_tree->left);
	std::cout << (_tree->key) << " , ";
	int _balanced_factor = getBalancedFactor(_tree);
	std::cout << "_value_ == " << _tree->key << "_balanced_factor" << _balanced_factor << " , hieght" << getHieght(_tree) << std::endl;
	print_tree_preoder(_tree->right);
}

void levelorder_newline(AVL_BST_TREE *v) {
	std::queue <AVL_BST_TREE *> q;
	struct AVL_BST_TREE* cur;
	q.push(v);
	q.push(NULL);

	while (!q.empty()) {
		cur = q.front();
		q.pop();
		if (cur == NULL && q.size() != 0) {
			std::cout << "\n";

			q.push(NULL);
			continue;
		}
		if (cur != NULL) {
			std::cout << " " << cur->key;

			if (cur->left != NULL) {
				q.push(cur->left);
			}
			if (cur->right != NULL) {
				q.push(cur->right);
			}
		}


	}
}

int main() {
	AVL_BST_TREE* _tree = NULL;

	/* Constructing tree given in
	the above figure */
	_tree = insertion(_tree, 10);
	_tree = insertion(_tree, 10);
	_tree = insertion(_tree, 9);
	_tree = insertion(_tree, 8);
	_tree = insertion(_tree, 7);
	_tree = insertion(_tree, 6);

	print_tree_preoder(_tree);
	print_tree_inoder(_tree);
	print_tree_postoder(_tree);

	return 0;
}


