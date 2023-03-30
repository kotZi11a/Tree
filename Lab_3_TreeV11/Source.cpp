#include <fstream>
#include <iostream>
#include <string> 
#include <algorithm>
#include <cmath>


using namespace std;

struct tree {

    tree* left;
    tree* right;
    int val;
    tree()
    {
        left = 0;
        right = 0;
    }
    ~tree()
    {
        delete left;
        delete right;
    }

};

struct digit {
    bool one;
    digit* next;
    digit() {}
    digit(int n)
    {
        if (n > 0)
        {
            one = 0;
            next = new digit(n - 1);
        }
        if (n == 0)next = 0;
    }
    ~digit()
    {
        if (next) {
            delete next;
        }

    }

};

struct bin {
    int raz;
    digit* dig;

    bin() {}

    bin(int n)
    {
        raz = n;
        dig = new digit(n);
    }
    ~bin()
    {
        delete dig;
    }

    void add(int n) {
        digit* temp = getRazr(n);

        if (temp->one == false)
        {
            temp->one = 1;
        }
        else
        {
            temp->one = 0;
            add(n - 1);
        }
    }

    digit* getRazr(int n) {
        digit* temp = dig;
        for (int i = 0; i < n; i++) {
            temp = temp->next;
        }
        return temp;
    }
};

void addInTree(bin* instr, tree*& root, int val) {
    tree* tree1 = root;
    for (int i = 0; i < instr->raz - 1; i++)
    {
        if (instr->getRazr(i)->one == 0)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    if (instr->getRazr(instr->raz - 1)->one == 1)
    {
        root->right = new tree();
        root->right->val = val;
    }
    else
    {
        root->left = new tree();
        root->left->val = val;
    }
    root = tree1;
}

tree* readfromfile(const char* filename)
{
    int n = 2;
    int a;
    tree* TTree = new tree();

    ifstream file;
    file.open(filename);

    file >> a;
    TTree->val = a;
    int i = 0;

    while (!file.eof())
    {
        file >> a;
        double k = (log(n) / log(2));
        if (((log(n) / log(2)) - floor((log(n - 1) / log(2)))) == 1) i = 0;

        bin* mas = new bin(floor(k));

        for (int j = 0; j < i; j++) {
            mas->add(floor(k) - 1);
        }
        i++;
        addInTree(mas, TTree, a);
        delete mas;
        n++;

    }

    file.close();
    return TTree;

}

int reversenum(int a)
{
    string num = to_string(a);
    reverse(num.begin(), num.end());
    if (a < 0)
        return -stoi(num);
    else
        return stoi(num);
}

void reverseval(tree*& T)
{
    if (T)
    {
        reverseval(T->left);
        reverseval(T->right);
        T->val = reversenum(T->val);
    }
}

void print(tree* T, ofstream& file)
{
    if (T)
    {
        print(T->left, file);
        file << T->val << " ";
        print(T->right, file);
    }

}

int main()
{
    tree* T = 0;
    T = readfromfile("input.txt");

    reverseval(T);

    ofstream out("output.txt");
    print(T, out);

    delete T;
    out.close();
}