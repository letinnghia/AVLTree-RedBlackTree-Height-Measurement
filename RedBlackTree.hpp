#pragma once
#include <iostream>

enum Color {RED, BLACK};

class RedBlackTree 
{
private:
	struct Node 
	{
		int key;
		Color color;
		Node* left;
		Node* right;
		Node* parent;

		Node(int val): key(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
	};

    Node* root;

	int getHeightHelper(Node* node)
	{
		if (node == nullptr) 
			return -1;

		return 1 + std::max(getHeightHelper(node->left),
							getHeightHelper(node->right));
	}

    void rotateLeft(Node* &root, Node* &node) 
	{
        Node* right_child = node->right;
        node->right = right_child->left;

        if (node->right != nullptr)
            node->right->parent = node;

        right_child->parent = node->parent;

        if (node->parent == nullptr) 
            root = right_child;
        else if (node == node->parent->left)
            node->parent->left = right_child;
        else 
            node->parent->right = right_child;

        right_child->left = node;
        node->parent = right_child;
    }

    void rotateRight(Node* &root, Node* &node) 
	{
        Node* left_child = node->left;
        node->left = left_child->right;

        if (node->left != nullptr) 
            node->left->parent = node;

        left_child->parent = node->parent;

        if (node->parent == nullptr) 
            root = left_child;
        else if (node == node->parent->left) 
            node->parent->left = left_child;
        else 
            node->parent->right = left_child;

        left_child->right = node;
        node->parent = left_child;
    }

    void fixViolation(Node* &root, Node* &node) 
	{
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while ((node != root) && (node->color == RED) && (node->parent->color == RED)) 
		{
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) 
			{
                Node* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED) 
				{
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } 
				else 
				{
                    if (node == parent->right) 
					{
                        rotateLeft(root, parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateRight(root, grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            } 
			else 
			{
                Node* uncle = grandparent->left;

                if ((uncle != nullptr) && (uncle->color == RED)) 
				{
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } 
				else 
				{
                    if (node == parent->left) 
					{
                        rotateRight(root, parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateLeft(root, grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        root->color = BLACK;
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
    RedBlackTree(): root(nullptr) {}

	~RedBlackTree()
	{
		deleteSubTree(root);
	}

    void insert(int val) 
	{
        Node* node = new Node(val);

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) 
		{
            parent = current;

            if (val < current->key) 
				current = current->left;
			else 
				current = current->right;
    	}

		node->parent = parent;

		if (parent == nullptr) 
			root = node;
		else if (val < parent->key)
			parent->left = node;
		else 
			parent->right = node;

		fixViolation(root, node);
	}

	void inorderTraversal(Node* node) 
	{
        if (node == nullptr) 
			return;

		inorderTraversal(node->left);
		std::cout << node->key << " ";
		inorderTraversal(node->right);
        
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
		return getHeightHelper(root);
	}
};
