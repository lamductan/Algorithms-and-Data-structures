#include <iostream>
#include <algorithm>
using namespace std;

enum Color {RED, BLACK};

typedef struct Node* ref;
struct Node {
    int key;
    int color;
    ref parent;
    ref left;
    ref right;
};

void initialize(ref& nil, ref& root) {
    nil = new Node;
    nil->color = BLACK;
    nil->left = nil->right = NULL;
    nil->parent = nil;
    root = nil;
}

ref getNode(int key, int color, ref nil) {
    ref p = new Node;
    p->key = key;
    p->color = color;
    p->left = p->right = p->parent = nil;
    return p;
}

void leftRotate(ref &root, ref x, ref nil) {
    ref y = x->right;
    x->right = y->left;
    if (y->left != nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(ref &root, ref x, ref nil) {
    ref y = x->left;
    x->left = y->right;
    if (y->right != nil)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    y->right = x;
    x->parent = y;
}

/* Insertion functions for RBT */
void BST_Insert(ref &root, ref x, ref nil) {
    ref y = nil;
    ref z = root;
    while (z != nil) {
        y = z;
        if (x->key < z->key)
            z = z->left;
        else
            z = z->right;
    }
    x->parent = y;
    if (y == nil)
        root = x;
    else
        if (x->key < y->key)
            y->left = x;
        else
            y->right = x;
}

void ins_leftAdjust(ref &root, ref &x, ref nil) {
    ref u = x->parent->parent->right;
    if (u->color == RED) {
        x->parent->color = BLACK;
        u->color = BLACK;
        x->parent->parent->color = RED;
        x = x->parent->parent;
    }
    else {
        if (x == x->parent->right) {
            x = x->parent;
            leftRotate(root, x, nil);
        }
        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        rightRotate(root, x->parent->parent, nil);
    }
}

void ins_rightAdjust(ref &root, ref &x, ref nil) {
    ref u = x->parent->parent->left;
    if (u->color == RED) {
        x->parent->color = BLACK;
        u->color = BLACK;
        x->parent->parent->color = RED;
        x = x->parent->parent;
    }
    else {
        if (x == x->parent->left) {
            x = x->parent;
            rightRotate(root, x, nil);
        }
        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        leftRotate(root, x->parent->parent, nil);
    }
}

void Insertion_FixUp(ref &root, ref x, ref nil) {
    while (x->parent->color == RED)
        if (x->parent == x->parent->parent->left)
            ins_leftAdjust(root, x, nil);
        else
            ins_rightAdjust(root, x, nil);
    root->color = BLACK;
}

// Main insertion function
void RBT_Insertion(ref &root, int key, ref nil) {
    ref x = getNode(key, RED, nil);
    BST_Insert(root, x, nil);
    Insertion_FixUp(root, x, nil);
}
/* End of insertion functions */


/* Delete functions */
ref searchTree(ref &root, int k, ref nil) {
    ref z = root;
    while (z != nil) {
        if (k < z->key)
            z = z->left;
        else if (k > z->key)
            z = z->right;
        else
            return z;
    }
    return nil;
}

ref TreeSuccessor(ref &root, ref &x, ref nil) {
    ref successor = x->right;
    while (successor->left != nil)
        successor = successor->left;
    return successor;
}

void del_leftAdjust(ref &root, ref &x, ref nil) {
    ref w = x->parent->right;
    if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        leftRotate(root, x->parent, nil);
        w = x->parent->right;
    }
    if ((w->right->color == BLACK) && (w->left->color == BLACK)) {
        w->color = RED;
        x = x->parent;
    }
    else {
        if (w->right->color == BLACK) {
            w->left->color = BLACK;
            w->color = RED;
            rightRotate(root, w, nil);
            w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        leftRotate(root, x->parent, nil);
        x = root;
    }
}

void del_rightAdjust(ref &root, ref &x, ref nil) {
    ref w = x->parent->left;
    if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rightRotate(root, x->parent, nil);
        w = x->parent->left;
    }
    if ((w->right->color == BLACK) && (w->left->color == BLACK)) {
        w->color = RED;
        x = x->parent;
    }
    else {
        if (w->left->color == BLACK) {
            w->right->color = BLACK;
            w->color = RED;
            leftRotate(root, w, nil);
            w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        rightRotate(root, x->parent, nil);
        x = root;
    }
}

void Deletion_FixUp(ref &root, ref &x, ref nil) {
    while ((x->color == BLACK) && (x != root))
        if (x == x->parent->left)
            del_leftAdjust(root, x, nil);
        else
            del_rightAdjust(root, x, nil);
    x->color = BLACK;
}

void RBT_Deletion(ref &root, int k, ref nil) {
    ref z = searchTree(root, k, nil);
    if (z == nil)
        return;
    ref y = (z->left == nil) || (z->right == nil) ?
                z : TreeSuccessor(root, z, nil);
    ref x = (y->left == nil) ? y->right : y->left;
    x->parent = y->parent;
    if (y->parent == nil)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    if (y != z)
        z->key = y->key;
    if (y->color == BLACK)
        Deletion_FixUp(root, x, nil);
    delete y;
}
/* End of delete functions */


/* Traversal functions */
void preorder(ref root, ref nil) {
    if (root == nil || root == NULL)
        return;
    cout << root->key << " ";
    preorder(root->left, nil);
    preorder(root->right, nil);
}

void inorder(ref root, ref nil) {
    if (root == nil || root == NULL)
        return;
    inorder(root->left, nil);
    cout << root->key << " ";
    inorder(root->right, nil);
}

void postorder(ref root, ref nil) {
    if (root == nil || root == NULL)
        return;
    postorder(root->left, nil);
    postorder(root->right, nil);
    cout << root->key << " ";
}

void Reverse(ref &p, ref &q) {
    ref x = p, y = p->right, t;
    while (x != q) {
        t = y->right;
        y->right = x;
        x = y, y = t;
    }
}

void MorrisPostOrder(ref root, ref nil) {
    ref dummy = new Node;
    dummy->left = root;
    dummy->right = nil;
    root->parent = dummy;
    ref p = dummy;
    while (p)
        if (p->left == nil)
            p = p->right;
    else {
        ref tmp = p->left;
        while (tmp->right != nil && tmp->right != p)
            tmp = tmp->right;
        if (tmp->right == nil) {
            tmp->right = p;
            p = p->left;
        }
        else {
            Reverse(p->left, tmp);
            ref t = tmp;
            while (t != p->left) {
                cout << t->key << " ";
                t = t->right;
            }
            cout << t->key << " ";
            Reverse(tmp, p->left);
            tmp->right = nil;
            p = p->right;
        }
    }
    delete dummy;
}
/* End of traversal functions */

void destruct(ref &root, ref nil) {
    if (root == nil || root == NULL)
        return;
    destruct(root->left, nil);
    destruct(root->right, nil);
    delete root;
    root = NULL;
}

int main() {
    ref nil, root;
    initialize(nil, root);

    int a[] = {70, 60, 50, 40, 30, 20, 10, 80, 90};
    for(int i = 0; i < int(sizeof(a)/sizeof(a[0])); i++)
        RBT_Insertion(root, a[i], nil);


    cout << "Preorder:  ";
    preorder(root, nil);
    cout << endl;

    cout << "Inorder:   ";
    inorder(root, nil);
    cout << endl;

    cout << "Postorder: ";
    postorder(root, nil);
    cout << endl;

    // Delete 50
    RBT_Deletion(root, 50, nil);
    cout << "Delete 50" << endl;
    cout << "Preorder:  ";
    preorder(root, nil);
    cout << endl;

    cout << "Inorder:   ";
    inorder(root, nil);
    cout << endl;

    cout << "Postorder: ";
    postorder(root, nil);
    cout << endl;

    cout << "Morris Postorder: ";
    MorrisPostOrder(root, nil);
    cout << endl;

    destruct(root, nil);
    cout << endl;
    return 0;
}
