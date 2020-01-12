#include <stack>

template <typename K, typename V>
class Dictionary final {
private:
	typedef enum  { RED = true, BLACK = false } nodeColor;

	class Node {
	public:
		K key;
		V val;
		Node * left;
		Node * right;
		bool color;
		Node(K key, V val);
	};

	class Iterator
	{
		friend class Dictionary<K, V>;
	public:
		Iterator(Dictionary<K, V>& dict);;
		void Reset();

		const K& key() const;
		const V& get() const;
		void set(const V& value);
		void next();
		void prev();
		bool hasNext() const;
		bool hasPrev() const;
	private:
		Node* current;
		std::stack<Node*> nextStack;
		std::stack<Node*> prevStack;
		int count;
		Dictionary<K, V>& dict;

	};

	static bool getRed(Node* node);
	Node* rotateLeft(Node* h);
	Node* rotateRight(Node* h);
	static void flipColors(Node* h);
	Node* moveRedLeft(Node* h);
	Node* moveRedRight(Node* h);
	Node* fixUp(Node* h);
	Node* minNode(Node* h);
	Node* deleteMin(Node* h);
	Node* insert(Node* h, const K& key, const V& val);
	Node* remove(Node* h, const K& key);
	void recursivePrint(const Node* h) const;
	void recursiveDelete(const Node* h) const;

	Node* getRoot();
	Node* root;
	int dictSize;

public:

	Dictionary();
	Dictionary(const Dictionary&) = delete;
	Dictionary& operator=(const Dictionary&) = delete;
	~Dictionary();
	void put(const K& key, const V& value);
	void remove(const K& key);
	bool contains(const K& key);
	const V& operator[](const K& key) const;
	V& operator[](const K& key);
	int size() const;
	V& search(const K& key);
	Iterator iterator();
	Iterator iterator() const;
};
#include "Dictionary.hpp"