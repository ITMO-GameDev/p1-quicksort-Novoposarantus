#pragma once

enum Color { RED, BLACK, DOUBLE_BLACK };

namespace lab3 {

	template<typename K, typename V>
	class Node {
        public:
		    K key;
		    V value;
		    int color;
		    Node* left, * right, * parent;

		    explicit Node(K key, V value);
		    ~Node();
	};

	template<typename K, typename V>
	class Dictionary final {
	private:
		Node<K, V>* root;
	protected:
		int getColor(Node<K, V>*&);
		void setColor(Node<K, V>*&, int);
		Node<K, V>* insertBST(Node<K, V>*&, Node<K, V>*&);
		void rotateLeft(Node<K, V>*&);
		void rotateRight(Node<K, V>*&);
		void fixInsertRBTree(Node<K, V>*&);
		void fixDeleteRBTree(Node<K, V>*&);
		Node<K, V>* deleteBST(Node<K, V>*&, K);
		Node<K, V>* minValueNode(Node<K, V>*&);
		Node<K, V>* maxValueNode(Node<K, V>*&);
		int getHeight(Node<K, V>*) const;
		Node<K, V>* find(Node<K, V>*&, const K&);
	public:
		class Iterator
		{
			friend class Dictionary<K, V>;
		public:
			Iterator(Node<K, V>*&);
			const K& key() const;
			const V& get() const;
			void set(const V& value);
			void next();
			void prev();
			bool hasNext();
			bool hasPrev();
		private:
			Node<K, V>* current;
			Node<K, V>* getNext();
			Node<K, V>* getPrev();
			bool isLeftToParent(Node<K, V>*&);
			bool isRightToParent(Node<K, V>*&);
			bool isParentHasRight(Node<K, V>*&);
			bool isParentHasleft(Node<K, V>*&);
			Node<K, V>* findNodeToPrev(Node<K, V>*&);

		};

		Dictionary();
		~Dictionary();
		void put(const K&, const V&);
		void remove(const K&);
		bool contains(const K&);
        V& Dictionary<K, V>::operator[](const K&);
		int size() const;
        Iterator iterator() {
            Iterator iterator(this->root);
            return iterator;
        }
        const Iterator iterator() const {
            Iterator iterator(this->root);
            return iterator;
        }
	};


#pragma region Node

    template<typename K, typename V>
    Node<K, V>::Node(K key, V value) {
        this->key = key;
        this->value = value;
        this->color = RED;
        this->left = this->parent = this->right = nullptr;
    }

    template<typename K, typename V>
    Node<K, V>::~Node() {
        if (std::is_destructible<K>::value) {
            this->key.~K();
        }

        if (std::is_destructible<V>::value) {
            this->value.~V();
        }

        delete(this->left);
        delete(this->right);
    }
#pragma endregion

#pragma region Dictionary protected

    template<typename K, typename V>
    int Dictionary<K, V>::getColor(Node<K, V>*& node) {
        if (node == nullptr) {
            return BLACK;
        }

        return node->color;
    }

    template<typename K, typename V>
    void Dictionary<K, V>::setColor(Node<K, V>*& node, int color) {
        if (node == nullptr) {
            return;
        }

        node->color = color;
    }


    template<typename K, typename V>
    Node<K, V>* Dictionary<K, V>::insertBST(Node<K, V>*& root, Node<K, V>*& ptr) {
        if (root == nullptr)
            return ptr;

        if (ptr->key < root->key) {
            root->left = insertBST(root->left, ptr);
            root->left->parent = root;
        }
        else if (ptr->key > root->key) {
            root->right = insertBST(root->right, ptr);
            root->right->parent = root;
        }

        return root;
    }

    template<typename K, typename V>
    void Dictionary<K, V>::rotateLeft(Node<K, V>*& ptr) {
        Node<K, V>* right_child = ptr->right;
        ptr->right = right_child->left;

        if (ptr->right != nullptr)
            ptr->right->parent = ptr;

        right_child->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = right_child;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = right_child;
        else
            ptr->parent->right = right_child;

        right_child->left = ptr;
        ptr->parent = right_child;
    }

    template<typename K, typename V>
    void Dictionary<K, V>::rotateRight(Node<K, V>*& ptr) {
        Node<K, V>* left_child = ptr->left;
        ptr->left = left_child->right;

        if (ptr->left != nullptr)
            ptr->left->parent = ptr;

        left_child->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = left_child;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = left_child;
        else
            ptr->parent->right = left_child;

        left_child->right = ptr;
        ptr->parent = left_child;
    }

    template<typename K, typename V>
    void Dictionary<K, V>::fixInsertRBTree(Node<K, V>*& ptr) {
        Node<K, V>* parent = nullptr;
        Node<K, V>* grandparent = nullptr;
        while (ptr != root && this->getColor(ptr) == RED && this->getColor(ptr->parent) == RED) {
            parent = ptr->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left) {
                Node<K, V>* uncle = grandparent->right;
                if (this->getColor(uncle) == RED) {
                    this->setColor(uncle, BLACK);
                    this->setColor(parent, BLACK);
                    this->setColor(grandparent, RED);
                    ptr = grandparent;
                }
                else {
                    if (ptr == parent->right) {
                        rotateLeft(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    this->rotateRight(grandparent);
                    std::swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            }
            else {
                Node<K, V>* uncle = grandparent->left;
                if (this->getColor(uncle) == RED) {
                    this->setColor(uncle, BLACK);
                    this->setColor(parent, BLACK);
                    this->setColor(grandparent, RED);
                    ptr = grandparent;
                }
                else {
                    if (ptr == parent->left) {
                        this->rotateRight(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    this->rotateLeft(grandparent);
                    std::swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            }
        }
        this->setColor(root, BLACK);
    }

    template<typename K, typename V>
    void Dictionary<K, V>::fixDeleteRBTree(Node<K, V>*& node) {
        if (node == nullptr)
            return;

        if (node == root) {
            root = nullptr;
            return;
        }

        if (this->getColor(node) == RED || this->getColor(node->left) == RED || this->getColor(node->right) == RED) {
            Node<K, V>* child = node->left != nullptr ? node->left : node->right;

            if (node == node->parent->left) {
                node->parent->left = child;
                if (child != nullptr)
                    child->parent = node->parent;
                setColor(child, BLACK);
                delete (node);
            }
            else {
                node->parent->right = child;
                if (child != nullptr)
                    child->parent = node->parent;
                this->setColor(child, BLACK);
                delete (node);
            }
        }
        else {
            Node<K, V>* sibling = nullptr;
            Node<K, V>* parent = nullptr;
            Node<K, V>* ptr = node;
            setColor(ptr, DOUBLE_BLACK);
            while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
                parent = ptr->parent;
                if (ptr == parent->left) {
                    sibling = parent->right;
                    if (getColor(sibling) == RED) {
                        this->setColor(sibling, BLACK);
                        this->setColor(parent, RED);
                        rotateLeft(parent);
                    }
                    else {
                        if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                            this->setColor(sibling, RED);
                            if (getColor(parent) == RED)
                                this->setColor(parent, BLACK);
                            else
                                setColor(parent, DOUBLE_BLACK);
                            ptr = parent;
                        }
                        else {
                            if (getColor(sibling->right) == BLACK) {
                                this->setColor(sibling->left, BLACK);
                                this->setColor(sibling, RED);
                                this->rotateRight(sibling);
                                sibling = parent->right;
                            }
                            this->setColor(sibling, parent->color);
                            this->setColor(parent, BLACK);
                            this->setColor(sibling->right, BLACK);
                            this->rotateLeft(parent);
                            break;
                        }
                    }
                }
                else {
                    sibling = parent->left;
                    if (getColor(sibling) == RED) {
                        this->setColor(sibling, BLACK);
                        this->setColor(parent, RED);
                        this->rotateRight(parent);
                    }
                    else {
                        if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                            this->setColor(sibling, RED);
                            if (getColor(parent) == RED)
                                this->setColor(parent, BLACK);
                            else
                                this->setColor(parent, DOUBLE_BLACK);
                            ptr = parent;
                        }
                        else {
                            if (getColor(sibling->left) == BLACK) {
                                setColor(sibling->right, BLACK);
                                setColor(sibling, RED);
                                rotateLeft(sibling);
                                sibling = parent->left;
                            }
                            this->setColor(sibling, parent->color);
                            this->setColor(parent, BLACK);
                            this->setColor(sibling->left, BLACK);
                            this->rotateRight(parent);
                            break;
                        }
                    }
                }
            }
            if (node == node->parent->left)
                node->parent->left = nullptr;
            else
                node->parent->right = nullptr;
            delete(node);
            setColor(this->root, BLACK);
        }
    }

    template<typename K, typename V>
    Node<K, V>* Dictionary<K, V>::deleteBST(Node<K, V>*& root, K key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            return deleteBST(root->left, key);

        if (key > root->key)
            return deleteBST(root->right, key);

        if (root->left == nullptr || root->right == nullptr)
            return root;

        Node<K, V>* temp = minValueNode(root->right);
        root->key = temp->key;
        return deleteBST(root->right, temp->key);
    }

    template<typename K, typename V>
    Node<K, V>* Dictionary<K, V>::minValueNode(Node<K, V>*& node) {

        Node<K, V>* ptr = node;

        while (ptr->left != nullptr)
            ptr = ptr->left;

        return ptr;
    }

    template<typename K, typename V>
    Node<K, V>* Dictionary<K, V>::maxValueNode(Node<K, V>*& node) {
        Node<K, V>* ptr = node;

        while (ptr->right != nullptr)
            ptr = ptr->right;

        return ptr;
    }

    template<typename K, typename V>
    int Dictionary<K, V>::getHeight(Node<K, V>* node) const {
        if (node == nullptr) {
            return 0;
        }

        return 1 + getHeight(node->left) + getHeight(node->right);
    }

    template<typename K, typename V>
    Node<K, V>* Dictionary<K, V>::find(Node<K, V>*& root, const K& key) {
        if (root == nullptr) {
            return nullptr;
        }

        if (root->key == key) {
            return root;
        }

        if (key < root->key)
            return find(root->left, key);

        if (key > root->key)
            return find(root->right, key);
    }
#pragma endregion

#pragma region Dictionary public

    template<typename K, typename V>
    Dictionary<K, V>::Dictionary() {
        this->root = nullptr;
    }

    template<typename K, typename V>
    Dictionary<K, V>::~Dictionary() {
        delete(this->root);
    }

    template<typename K, typename V>
    void Dictionary<K, V>::put(const K& key, const V& value) {
        Node<K, V>* node = this->find(this->root, key);
        if (node == nullptr) {
            node = new Node<K, V>(key, value);
            this->root = insertBST(this->root, node);
            fixInsertRBTree(node);
        }
        else {
            if (std::is_destructible<V>::value) {
                node->value.~V();
            }
            node->value = value;
        }
    }

    template<typename K, typename V>
    void Dictionary<K, V>::remove(const K& key) {
        if (this->find(this->root, key) == nullptr) {
            return;
        }

        Node<K, V>* node = this->deleteBST(this->root, key);
        fixDeleteRBTree(node);
    }

    template<typename K, typename V>
    bool Dictionary<K, V>::contains(const K& key) {
        return this->find(this->root, key) != nullptr;
    }

    template<typename K, typename V>
    V& Dictionary<K, V>::operator[](const K& key) {
        Node<K, V>* node = this->find(this->root, key);
        if (node == nullptr) {
            throw std::runtime_error("key is not exist in hashtable");
        }

        return node->value;
    }

    template<typename K, typename V>
    int Dictionary<K, V>::size() const {
        return this->getHeight(this->root);
    }
#pragma endregion

#pragma region Iterator private

    template<typename K, typename V>
    bool Dictionary<K, V>::Iterator::isLeftToParent(Node<K, V>*& node) {
        return node->parent->left->key == node->key;
    }

    template<typename K, typename V>
    bool Dictionary<K, V>::Iterator::isRightToParent(Node<K, V>*& node) {
        return node->parent->right->key == node->key;
    }

    template<typename K, typename V>
    bool Dictionary<K, V>::Iterator::isParentHasRight(Node<K, V>*& node) {
        return node->parent->right != nullptr;
    }


    template<typename K, typename V>
    bool Dictionary<K, V>::Iterator::isParentHasleft(Node<K, V>*& node) {
        return node->parent->left != nullptr;
    }

    template<typename K, typename V>
    Node<K, V>* Dictionary<K, V>::Iterator::getNext() {
        if (this->current == nullptr) return nullptr;
        if (this->current->left != nullptr) return this->current->left;
        if (this->current->right != nullptr) return this->current->right;
        if (this->current->parent == nullptr) return nullptr;

        if (this->isLeftToParent(this->current) && this->isParentHasRight(this->current)) {
            return this->current->parent->right;
        }

        Node<K, V>* index = this->current->parent;
        while (index != nullptr
            && index->parent != nullptr
            && isRightToParent(index)
            && isParentHasRight(index))
        {
            index = index->parent;
        }

        if (index == nullptr || index->parent == nullptr) {
            return nullptr;
        }

        return index->parent->right;
    }


    template<typename K, typename V>
    Node<K, V>* Dictionary<K, V>::Iterator::findNodeToPrev(Node<K, V>*& node) {
        if (node->left == nullptr && node->right == nullptr)
        {
            return node;
        }
        if (node->right != nullptr) {
            return findNodeToPrev(node->right);
        }
        if (node->left != nullptr) {
            return findNodeToPrev(node->left);
        }
    }

    template<typename K, typename V>
    Node<K, V>* Dictionary<K, V>::Iterator::getPrev() {
        if (this->current == nullptr) return nullptr;
        if (this->current->parent == nullptr) return nullptr;

        if (this->isLeftToParent(this->current)) {
            return this->current->parent;
        }

        if (this->isRightToParent(this->current) && !this->isParentHasleft(this->current)) {
            return this->current->parent;
        }

        Node<K, V>* index = this->current->parent->left;
        return this->findNodeToPrev(index);
    }
#pragma endregion

#pragma region Iterator public 
    template<typename K, typename V>
    Dictionary<K, V>::Iterator::Iterator(Node<K, V>*& root) {
        this->current = root;
    }

    template<typename K, typename V>
    const K& Dictionary<K, V>::Iterator::key() const {
        return this->current->key;
    }

    template<typename K, typename V>
    const V& Dictionary<K, V>::Iterator::get() const {
        return this->current->value;
    }

    template<typename K, typename V>
    void Dictionary<K, V>::Iterator::set(const V& value) {
        if (std::is_destructible<V>::value) {
            this->current->value.~V();
        }
        this->current->value = value;
    }

    template<typename K, typename V>
    void Dictionary<K, V>::Iterator::next() {
        this->current = this->getNext();
    }

    template<typename K, typename V>
    void Dictionary<K, V>::Iterator::prev() {
        this->current = this->getPrev();
    }

    template<typename K, typename V>
    bool Dictionary<K, V>::Iterator::hasNext() {
        return this->getNext() != nullptr;
    }

    template<typename K, typename V>
    bool Dictionary<K, V>::Iterator::hasPrev() {
        return this->getPrev() != nullptr;
    }
#pragma endregion
}
