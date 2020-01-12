#include <iostream>
#include <stack>

template <typename K, typename V>
Dictionary<K, V>::Node::Node(K key, V val)
{
	this->key = key;
	this->val = val;
	this->color = RED;
	this->right = nullptr;
	this->left = nullptr;
}

template <typename K, typename V>
Dictionary<K, V>::Iterator::Iterator(Dictionary<K, V>& dict) : dict(dict)
{
	nextStack = std::stack<Node*>();
	prevStack = std::stack<Node*>();
	current = dict.root;
	count = 0;
	Reset();
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::Reset()
{
	current = dict.root;
	if (current == nullptr)
	{
		return;
	}
	while (!nextStack.empty())
	{
		nextStack.pop();
	}

	nextStack.push(nullptr);

	while (!prevStack.empty())
	{
		prevStack.pop();
	}
	prevStack.push(dict.root);
	count = 0;
}

template <typename K, typename V>
const K& Dictionary<K, V>::Iterator::key() const
{
	return current->key;
}

template <typename K, typename V>
const V& Dictionary<K, V>::Iterator::get() const
{
	return current->val;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::set(const V& value)
{
	current->val = value;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::next()
{
	if (current == nullptr) return;

	if (current != dict.root)
	{
		prevStack.push(current);
	}
	if (current->right != nullptr)
	{
		nextStack.push(current->right);
	}
	if (current->left != nullptr)
	{
		current = current->left;
	}
	else
	{
		current = nextStack.top();
		nextStack.pop();
	}
	count++;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::prev()
{
	current = prevStack.top();
	prevStack.pop();
	count--;
}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasNext() const
{
	return (count) < dict.dictSize - 1;
}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasPrev() const
{
	return current != dict.root;
}

template <typename K, typename V>
bool Dictionary<K, V>::getRed(Node* node)
{
	if (node == nullptr) return false;
	return (node->color);
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::rotateLeft(Node* head)
{
	Node* x = head->right;
	head->right = x->left;
	x->left = head;
	x->color = head->color;
	head->color = RED;
	return x;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::rotateRight(Node* head)
{
	Node* x = head->left;
	head->left = x->right;
	x->right = head;
	x->color = head->color;
	head->color = RED;
	return x;
}

template <typename K, typename V>
void Dictionary<K, V>::flipColors(Node* head)
{
	head->color = !head->color;
	head->left->color = !head->left->color;
	head->right->color = !head->right->color;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::moveRedLeft(Node* head)
{
	flipColors(head);
	if (getRed(head->right->left))
	{
		head->right = rotateRight(head->right);
		head = rotateLeft(head);
		flipColors(head);
	}
	return head;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::moveRedRight(Node* head)
{
	flipColors(head);
	if (getRed(head->left->left))
	{
		head = rotateRight(head);
		flipColors(head);
	}
	return head;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::fixUp(Node* head)
{
	if (getRed(head->right) && !getRed(head->left)) head = rotateLeft(head);
	if (getRed(head->left) && getRed(head->left->left)) head = rotateRight(head);
	if (getRed(head->left) && getRed(head->right)) flipColors(head);
	return head;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::minNode(Node* head)
{
	return (head->left == nullptr) ? head : minNode(head->left);
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::deleteMin(Node* head)
{
	if (head->left == nullptr) return nullptr;
	if (!getRed(head->left) && !getRed(head->left->left))
		head = moveRedLeft(head);
	head->left = deleteMin(head->left);
	return fixUp(head);
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::insert(Node* head, const K& key, const V& val)
{
	if (head == nullptr)
	{
		Node* value = new Node(key, val);
		dictSize++;
		return value;
	}
	if (key == head->key) head->val = val;
	else if (key < head->key) head->left = insert(head->left, key, val);
	else head->right = insert(head->right, key, val);

	head = fixUp(head);

	return head;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::remove(Node* head, const K& key)
{
	if (key < head->key)
	{
		if (!getRed(head->left) && !getRed(head->left->left))
			head = moveRedLeft(head);
		head->left = remove(head->left, key);
	}
	else
	{
		if (getRed(head->left))
			head = rotateRight(head);
		if (key == head->key && head->right == nullptr)
		{
			dictSize--;
			return nullptr;
		}
		if (!getRed(head->right) && !getRed(head->right->left))
			head = moveRedRight(head);
		if (key == head->key)
		{
			Node* mn = minNode(head->right);
			head->val = mn->val;
			head->key = mn->key;
			head->right = deleteMin(head->right);
			dictSize--;
			delete mn;
		}
		else
		{
			head->right = remove(head->right, key);
		}
	}

	return fixUp(head);
}

template <typename K, typename V>
void Dictionary<K, V>::recursivePrint(const Node* head) const
{
	if (head == nullptr)
		return;
	recursivePrint(head->left);
	std::cout << head->key << "=" << head->val << std::endl;
	recursivePrint(head->right);
}

template <typename K, typename V>
void Dictionary<K, V>::recursiveDelete(const Node* head) const
{
	if (head == nullptr)
		return;
	recursiveDelete(head->left);
	recursiveDelete(head->right);
	delete head;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::getRoot()
{
	return root;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary()
{
	root = nullptr;
	dictSize = 0;
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
	recursiveDelete(root);
}

template <typename K, typename V>
V& Dictionary<K, V>::search(const K& key)
{
	Node* x = root;
	while (x != nullptr)
	{
		if (key == x->key) return x->val;
		else if (key < x->key) x = x->left;
		else x = x->right;
	}
	auto empty = V();
	return  empty;
}

template <typename K, typename V>
bool Dictionary<K, V>::contains(const K& key)
{
	Node* x = root;
	while (x != nullptr)
	{
		if (key == x->key) return true;
		else if (key < x->key) x = x->left;
		else x = x->right;
	}
	return false;
}

template <typename K, typename V>
void Dictionary<K, V>::put(const K& key, const V& value)
{
	root = insert(root, key, value);
	root->color = BLACK;
}

template <typename K, typename V>
void Dictionary<K, V>::remove(const K& key)
{
	if (!contains(key)) return;
	root = remove(root, key);
	root->color = BLACK;
}

template <typename K, typename V>
const V& Dictionary<K, V>::operator[](const K& key) const
{
	if (!contains(key))
	{
		auto none = V();
		return none;
	};
	return search(key);
}

template <typename K, typename V>
V& Dictionary<K, V>::operator[](const K& key)
{
	if (!contains(key)) put(key, V());
	return search(key);
}

template <typename K, typename V>
int Dictionary<K, V>::size() const
{
	return dictSize;
}

template <typename K, typename V>
typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator()
{
	Iterator iterator(*this);
	return iterator;
}

template <typename K, typename V>
typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator() const
{
	Iterator iterator(*this);
	return iterator;
}