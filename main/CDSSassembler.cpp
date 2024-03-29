#include <stdlib.h>
#include <iostream>
using namespace std;
/* We will implement DAG as Strictly Binary Tree where each node has zero or two children */
struct bin_tree
{
    char data;
    int label;
    struct bin_tree *right, *left;
};
typedef bin_tree node;
class dag
{
private:
    /* R is stack for storing registers */
    int R[10];
    int top;
    /* op will be used for opcode name w.r.t. arithmetic operator e.g. ADD for + */
    char *op;

public:
    void initializestack(node *root)
    {
        /* value of top = index of topmost element of stack R = label of Root of tree(DAG) minus one */
        top = root->label - 1;
        /* Allocating Stack Registers */
        int temp = top;
        for (int i = 0; i <= top; i++)
        {
            R[i] = temp;
            temp--;
        }
    }
    /* insertnode() and insert() functions are for adding nodes to tree(DAG) */
    void insertnode(node **tree, char val)
    {
        node *temp = NULL;
        if (!(*tree))
        {
            temp = (node *)malloc(sizeof(node));
            temp->left = temp->right = NULL;
            temp->data = val;
            temp->label = -1;
            *tree = temp;
        }
    }
    void insert(node **tree, char val)
    {
        char l, r;
        int numofchildren;
        insertnode(tree, val);
        cout << "\nEnter number of children of " << val << " :";
        cin >> numofchildren;
        if (numofchildren == 2)
        {
            cout << "\nEnter Left Child of " << val << " :";
            cin >> l;
            insertnode(&(*tree)->left, l);
            cout << "\nEnter Right Child of " << val << " :";
            cin >> r;
            insertnode(&(*tree)->right, r);

            insert(&(*tree)->left, l);
            insert(&(*tree)->right, r);
        }
    }
    /* findleafnodelabel() will find out the label of leaf nodes of tree(DAG) */
    void findleafnodelabel(node *tree, int val)
    {
        if (tree->left != NULL && tree->right != NULL)
        {
            findleafnodelabel(tree->left, 1);
            findleafnodelabel(tree->right, 0);
        }
        else
        {
            tree->label = val;
        }
    }
    /* findinteriornodelabel() will find out the label of interior nodes of tree(DAG) */
    void findinteriornodelabel(node *tree)
    {
        if (tree->left->label == -1)
        {
            findinteriornodelabel(tree->left);
        }
        else if (tree->right->label == -1)
        {
            findinteriornodelabel(tree->right);
        }
        else
        {
            if (tree->left != NULL && tree->right != NULL)
            {
                if (tree->left->label == tree->right->label)
                {
                    tree->label = (tree->left->label) + 1;
                }
                else
                {
                    if (tree->left->label > tree->right->label)
                    {
                        tree->label = tree->left->label;
                    }
                    else
                    {
                        tree->label = tree->right->label;
                    }
                }
            }
        }
    }
    /* function print_inorder() will print inorder of nodes. Here we are also printing label of each node
    of tree(DAG) */
    void print_inorder(node *tree)
    {
        if (tree)
        {
            print_inorder(tree->left);
            cout << tree->data << " with Label " << tree->label << "\n";
            print_inorder(tree->right);
        }
    }
    /* function swap() will swap the top and second top elements of Register stack R */
    void swap()
    {
        int temp;
        temp = R[0];
        R[0] = R[1];
        R[1] = temp;
    }
    /* function pop() will remove and return topmost element of stack */
    int pop()
    {
        int temp = R[top];
        top--;
        return temp;
    }
    /* function push() will increment top by one and will insert element at top position of Register stack
     */
    void push(int temp)
    {
        top++;
        R[top] = temp;
    }
    /* nameofoperation() will return opcode w.r.t. arithmetic operator */
    void nameofoperation(char temp)
    {
        switch (temp)
        {
        case '+':
            op = (char *)"ADD";
            break;
        case '-':
            op = (char *)"SUB";
            break;
        case '*':
            op = (char *)"MUL";
            break;
        case '/':
            op = (char *)"DIV";
            break;
        }
    }
    /* gencode() will generate Assembly code w.r.t. labels of tree(DAG) */
    void gencode(node *tree)
    {
        if (tree->left != NULL && tree->right != NULL)
        {
            if (tree->left->label == 1 && tree->right->label == 0 && tree->left->left == NULL && tree->left->right == NULL && tree->right->left == NULL && tree->right->right == NULL)
            {
                cout << "MOV " << tree->left->data << ","
                     << "R[" << R[top] << "]\n";
                nameofoperation(tree->data);
                cout << op << " " << tree->right->data << ",R[" << R[top] << "]\n";
            }
            else if (tree->left->label >= 1 && tree->right->label == 0)
            {
                gencode(tree->left);
                nameofoperation(tree->data);
                cout << op << " " << tree->right->data << ",R[" << R[top] << "]\n";
            }
            else if (tree->left->label < tree->right->label)
            {
                int temp;
                swap();
                gencode(tree->right);
                temp = pop();
                gencode(tree->left);
                push(temp);
                swap();
                nameofoperation(tree->data);
                cout << op << " "
                     << "R[" << R[top - 1] << "],R[" << R[top] << "]\n";
            }
            else if (tree->left->label >= tree->right->label)
            {
                int temp;
                gencode(tree->left);
                temp = pop();
                gencode(tree->right);
                push(temp);
                nameofoperation(tree->data);
                cout << op << " "
                     << "R[" << R[top - 1] << "],R[" << R[top] << "]\n";
            }
        }
        else if (tree->left == NULL && tree->right == NULL && tree->label == 1)
        {
            cout << "MOV " << tree->data << ",R[" << R[top] << "]\n";
        }
    }
    /* deltree() will free the memory allocated for tree(DAG) */
    void deltree(node *tree)
    {
        if (tree)
        {
            deltree(tree->left);
            deltree(tree->right);
            free(tree);
        }
    }
    
};
/* Program execution will start from main() function */
int main()
{
    node *root;
    root = NULL;
    node *tmp;
    char val;
    int i, temp;
    dag d;

    /* Inserting nodes into tree(DAG) */
    cout << "\nEnter root of tree:";
    cin >> val;
    d.insert(&root, val);
    /* Finding Labels of Leaf nodes */
    d.findleafnodelabel(root, 1);
    /* Finding Labels of Interior nodes */
    while (root->label == -1)
        d.findinteriornodelabel(root);
    /* Initializing Stack contents and top variable */
    d.initializestack(root);
    /* Printing inorder of nodes of tree(DAG) */
    cout << "\nInorder Display:\n";
    d.print_inorder(root);

    /* Printing assembly code w.r.t. labels of tree(DAG) */
    cout << "\nAssembly Code:\n";
    d.gencode(root);

    /* Deleting all nodes of tree */
    d.deltree(root);
    return 0;
}
