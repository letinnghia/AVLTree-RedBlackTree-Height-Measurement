#include <iostream>


class AVLTree {
private:

    struct Node 
	{
		int key;
		int height;
		Node* left;
		Node* right;

		Node(int val): key(val), height(0), left(nullptr), right(nullptr) {}
	};

    Node* root;

    int height(Node* node) 
	{
        if (node == nullptr) 
            return -1;
        
        return node->height;
    }

    int balanceFactor(Node* node) 
	{
        if (node == nullptr) 
            return 0;
        
        return height(node->left) - height(node->right);
    }

    Node* rotateRight(Node* node) 
	{
        Node* lChild = node->left;
        Node* subtree = lChild->right;

        lChild->right = node;
        node->left = subtree;

        node->height = std::max(height(node->left), height(node->right)) + 1;
        lChild->height = std::max(height(lChild->left), height(lChild->right)) + 1;

        return lChild;
    }

    Node* rotateLeft(Node* node) 
	{
        Node* rChild = node->right;
        Node* subtree = rChild->left;

        rChild->left = node;
        node->right = subtree;

        node->height = std::max(height(node->left), height(node->right)) + 1;
        rChild->height = std::max(height(rChild->left), height(rChild->right)) + 1;

        return rChild;
    }

    Node* insert(Node* node, int key) 
	{
        if (node == nullptr) 
            return new Node(key);
        
        if (key < node->key) 
            node->left = insert(node->left, key);
        else if (key > node->key) 
            node->right = insert(node->right, key);
        else 
            return node;

        node->height = std::max(height(node->left), height(node->right)) + 1;

        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->key) 
            return rotateRight(node);

        if (balance < -1 && key > node->right->key) 
            return rotateLeft(node);
        

        if (balance > 1 && key > node->left->key) 
		{
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key) 
		{
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorderTraversal(Node* node) 
	{
        if (node == nullptr) 
			return;

		inorderTraversal(node->left);
		std::cout << node->key << " ";
		inorderTraversal(node->right);
        
    }

	void deleteSubTree(Node* root) 
	{
		if (root == nullptr) 
			return;
		
		deleteSubTree(root->left);
		deleteSubTree(root->right);
		delete root;
	}

public:
    AVLTree(): root(nullptr) {}

	~AVLTree()
	{
		deleteSubTree(root);
	}

    void insert(int key) 
	{
        root = insert(root, key);
    }

    void print() 
	{
        inorderTraversal(root);
        std::cout << std::endl;
    }

    void clear()
    {
        deleteSubTree(root);
        root = nullptr;
    }

	int getHeight()
	{
		return height(root);
	}
};