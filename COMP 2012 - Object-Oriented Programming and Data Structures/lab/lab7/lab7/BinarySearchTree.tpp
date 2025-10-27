template<typename T1, typename T2>
BinarySearchTree<T1, T2>::BinarySearchTree(const string& name, const T1& x, const T2& y):
    name(name), score{x, y}, left_sub_tree(nullptr), right_sub_tree(nullptr) {}

template<typename T1, typename T2>
BinarySearchTree<T1, T2>::BinarySearchTree(const BinarySearchTree<T1, T2>& other_tree): name(other_tree.name),
                                                                                        score(other_tree.score)
    {
        //cout << "copy constructor called" << endl;
        if(other_tree.left_sub_tree != nullptr)
        {    
            this->left_sub_tree = new BinarySearchTree<T1,T2>(*(other_tree.left_sub_tree));
        }
        else
        {
            this->left_sub_tree = nullptr;
        }

        if(other_tree.right_sub_tree != nullptr)
        {
            this->right_sub_tree = new BinarySearchTree<T1,T2>(*(other_tree.right_sub_tree));
        }
        else
        {
            this->right_sub_tree = nullptr;
        }
    }
    // TODO 1: copy the members of this node and two subtrees


template<typename T1, typename T2>
BinarySearchTree<T1, T2>::~BinarySearchTree() {
    // TODO 2: release the resources occupied by the two subtrees
    if(this->left_sub_tree != nullptr)
    {
        delete this->left_sub_tree;
        this->left_sub_tree = nullptr;
    }

    if(this->right_sub_tree != nullptr)
    {
        delete this->right_sub_tree;
        this->right_sub_tree = nullptr;
    }
};

template<typename T1, typename T2>
int BinarySearchTree<T1, T2>::size() const {
    // TODO 3: return the size of the tree by recursively compute the size
    if(this->left_sub_tree == nullptr && this->right_sub_tree == nullptr)
    {return 1;}
    else if(this->left_sub_tree != nullptr && this->right_sub_tree == nullptr)
    {return 1 + this->left_sub_tree->size();}
    else if(this->left_sub_tree == nullptr && this->right_sub_tree != nullptr)
    {return 1 + this->right_sub_tree->size();}
    else
    {return 1 + this->left_sub_tree->size() + this->right_sub_tree->size();}
}

template<typename T1, typename T2>
bool BinarySearchTree<T1, T2>::findByScorePair(const T1 &x, const T2 &y) const {
    // TODO 4: find the name of the node by the score.
    // If the score exists, call printName(), and return true
    // If the score does not exist, do nothing and return false
    // Hint: call the function recursively
    // **Note**: You are expected to search either left or right tree and compare the value to get the node contains target ScorePair.
    if(this->score.baseScore == x )
    {
        if(this->score.bonusScore == y)
        {
            this->printName();
            return true;
        }
        else if(y < this->score.bonusScore )
        {
            if(this->left_sub_tree == nullptr)
            {
                return false;
            }
            else
            {
                return this->left_sub_tree->findByScorePair(x, y);
            }
        }
        else
        {
            if(this->right_sub_tree == nullptr)
            {
                return false;
            }
            else
            {
                return this->right_sub_tree->findByScorePair(x, y);
            }
        }
    }

    else if(x < this->score.baseScore)
    {
        if(this->left_sub_tree == nullptr)
        {
            return false;
        }
        else
        {
            return this->left_sub_tree->findByScorePair(x, y);
        }
    }

    else
    {
        if(this->right_sub_tree == nullptr)
        {
            return false;
        }
        else
        {
            return this->right_sub_tree->findByScorePair(x, y);
        }
    }

}

template<typename T1, typename T2>
bool BinarySearchTree<T1, T2>::findByName(const string& name) const {
    // TODO 5: find the score of the node by the name.
    // If the score exists, call printPoint(), and return true
    // If the score does not exist, do nothing and return false
    // Hint: use 'a.compare(b)' or 'a == b' to do the string comparison.
    if(this->name == name)
    {
        this->printPoint();
        return true;
    }

    if(this->left_sub_tree == nullptr && this->right_sub_tree == nullptr)
        return false;
    else if(this->left_sub_tree != nullptr && this->right_sub_tree == nullptr)
        return this->left_sub_tree->findByName(name);
    else if(this->left_sub_tree == nullptr && this->right_sub_tree != nullptr)
        return this->right_sub_tree->findByName(name);
    else
        return (this->left_sub_tree->findByName(name) || this->right_sub_tree->findByName(name));
}


template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::insert(const string& name, const T1 &x, const T2 &y) {
    if (findByName(name) || findByScorePair(x, y)) {
        cout << "The data exists." << endl;
        return;
    }
    // TODO 6: Insert a node to the tree. Do nothing if any of name or score exists. (Which is given)
    // implement the remaining code below
    if(x < this->score.baseScore)
    {
        if(this->left_sub_tree == nullptr)
        {
            this->left_sub_tree = new BinarySearchTree<T1, T2>(name,x,y);
        }
        else
        {
            this->left_sub_tree->insert(name,x,y);
        }
    }
    else if(x > this->score.baseScore)
    {
        if(this->right_sub_tree == nullptr)
        {
            this->right_sub_tree = new BinarySearchTree<T1, T2>(name,x,y);
        }
        else
        {
            this->right_sub_tree->insert(name,x,y);
        }
    }
    else
    {
        if(y < this->score.bonusScore)
        {
            if(this->left_sub_tree == nullptr)
            {
                this->left_sub_tree = new BinarySearchTree<T1, T2>(name,x,y);
            }
            else
            {
                this->left_sub_tree->insert(name,x,y);
            }
        }
        else
        {
            if(this->right_sub_tree == nullptr)
            {
                this->right_sub_tree = new BinarySearchTree<T1, T2>(name,x,y);
            }
            else
            {
                this->right_sub_tree->insert(name,x,y);
            }
        }
    }

}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::inorderTraversal() const {
    // TODO 7: run printAll() by in order traversal
    if(this->left_sub_tree != nullptr)
    {
        this->left_sub_tree->inorderTraversal();
    }

    this->printAll();

    if(this->right_sub_tree != nullptr)
    {
        this->right_sub_tree->inorderTraversal();
    }
}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::printName() const {
    cout << "The name is " << name << "." << endl;
}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::printPoint() const {
    cout << "The score is " << "(" << score.baseScore << ", " << score.bonusScore << ")." << endl;
}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::printAll() const {
    cout << "Name: " << name << ", " << "Point: (" << score.baseScore << ", " << score.bonusScore << ")." << endl;
}

