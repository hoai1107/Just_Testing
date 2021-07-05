#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<stack>
#include<string> 
#include<set>
#include<iterator>
#include<queue>
#include<fstream>
#include<math.h>
#include<unordered_set>
#include<list>
#include<unordered_map>
#include<functional>
#include<fstream>
#include<sstream>

using namespace std;
 
#define fastIO ios_base::sync_with_stdio(false);cin.tie(NULL);
typedef pair<long long,long long> pll;
typedef pair<int,int> pii;
typedef long long ll;
 
/*=============================CODE===============================*/

struct node
{
    int val;
    int height;
    node *left;
    node *right;
    int balance_factor;

    node()
    {
        left = right = nullptr;
    }

    node(int x)
    {
        left = right = nullptr;
        val = x;
        height = 0;
        balance_factor = 0;
    }
};

class AVL
{
private:
    //Data
    node *root;

    //Function prototype
    node *left_rotation(node *n);
    node *right_rotation(node *n);
    void updateHeight(node *&n);
    node *balance(node *n);
    node *insertTree(node *n, int val);

    node *Left_Left_Rotate(node *n)
    {
        return right_rotation(n);
    }

    node *Left_Right_Rotate(node *n)
    {
        n->left = left_rotation(n->left);
        return right_rotation(n);
    }

    node *Right_Right_Rotate(node *n)
    {
        return left_rotation(n);
    }

    node *Right_Left_Rotation(node *n)
    {
        n->right = right_rotation(n->right);
        return left_rotation(n);
    }

public:
    AVL()
    {
        this->root = nullptr;
    }

    void insert(int val)
    {
        root = insertTree(root, val);
    }

    void display()
    {
        if (root == nullptr)
        {
            cout << "Empty tree.";
            return;
        }
        queue<node *> q1, q2;
        q1.push(root);

        while (!q1.empty())
        {
            while (!q1.empty())
            {
                node *tmp = q1.front();
                q1.pop();
                if (tmp->left != nullptr)
                    q2.push(tmp->left);
                if (tmp->right != nullptr)
                    q2.push(tmp->right);
                cout << tmp->val << ' ';
            }
            cout << endl;
            swap(q1, q2);
        }
    }

    void deleteTree(node *n)
    {
        if (n == nullptr)
        {
            return;
        }

        deleteTree(n->left);
        deleteTree(n->right);
        delete n;
        n = nullptr;
    }

    ~AVL()
    {
        deleteTree(root);
    }
};

node* AVL::left_rotation(node* n){
    node *right_tree = n->right;
    n->right = right_tree->left;
    right_tree->left = n;
    updateHeight(n);
    updateHeight(right_tree);

    return right_tree;
}

node* AVL::right_rotation(node* n){
    node* left_tree = n->left;
    n->left = left_tree->right;
    left_tree->right = n;
    updateHeight(n);
    updateHeight(left_tree);

    return left_tree;
}

node* AVL::balance(node* n){
    //Left heavy
    if (n->balance_factor == -2)
    {
        if (n->left->balance_factor <= 0)
        {
            return Left_Left_Rotate(n);
        }
        else
        {
            return Left_Right_Rotate(n);
        }
    } //Right heavy
    else if (n->balance_factor == 2)
    {
        if (n->right->balance_factor >= 0)
        {
            return Right_Right_Rotate(n);
        }
        else
        {
            return Right_Left_Rotation(n);
        }
    }

    return n;
}

node* AVL::insertTree(node* n, int val){
    if (n == nullptr)
    {
        return new node(val);
    }
    else if (val < n->val)
    {
        n->left = insertTree(n->left, val);
    }
    else if (val > n->val)
    {
        n->right = insertTree(n->right, val);
    }

    updateHeight(n);

    return balance(n);
}

void AVL::updateHeight(node*& n){
    int leftHeight = (n->left == nullptr) ? -1 : n->left->height;
    int rightHeight = (n->right == nullptr) ? -1 : n->right->height;

    n->height = 1 + max(leftHeight, rightHeight);
    n->balance_factor = rightHeight - leftHeight;
}
