// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class SymNode
{
public:
    string key;
    int height;
    int address;
    SymNode *par;
    SymNode *left;
    SymNode *right;

    SymNode()
    {
        this->key = "";
        this->height = 0;
        this->address = 1;
        this->par = NULL;
        this->left = NULL;
        this->right = NULL;
    }
    SymNode(string k)
    {
        this->key = k;
        this->height = 0;
        this->address = 1;
        this->par = NULL;
        this->left = NULL;
        this->right = NULL;
    }

    SymNode *LeftLeftRotation()
    {
        if (this->par != NULL)
        {
            if ((this->par)->left == this)
            {
                (this->par)->left = this->right;
            }
            else
            {
                (this->par)->right = this->right;
            }
        }
        SymNode *temp = (this->right)->left;
        (this->right)->left = this;
        (this->right)->par = this->par;
        this->par = this->right;
        this->right = temp;
        if (this->right != NULL)
        {
            (this->right)->par = this;
        }
        // a ki height manage karna
        int rh;
        if (this->right == NULL)
        {
            rh = -1;
        }
        else
        {
            rh = this->right->height;
        }
        int lh;
        if (this->left == NULL)
        {
            lh = -1;
        }
        else
        {
            lh = this->left->height;
        }
        this->height = 1 + max(lh, rh);
        // b ki height manage karna
        lh = this->height;
        if ((this->par)->right == NULL)
        {
            rh = -1;
        }
        else
        {
            rh = ((this->par)->right)->height;
        }
        (this->par)->height = 1 + max(lh, rh);
        return this->par; // root kar rha hu
    }
    SymNode *RightRightRotation()
    {
        if (this->par != NULL)
        {
            if ((this->par)->left == this)
            {
                (this->par)->left = this->left;
            }
            else
            {
                (this->par)->right = this->left;
            }
        }
        SymNode *temp = (this->left)->right;
        (this->left)->right = this;
        (this->left)->par = this->par;
        this->par = this->left;
        this->left = temp;
        if (this->left != NULL)
        {
            (this->left)->par = this;
        }
        // a ki height manage karna
        int rh;
        if (this->right == NULL)
        {
            rh = -1;
        }
        else
        {
            rh = this->right->height;
        }
        int lh;
        if (this->left == NULL)
        {
            lh = -1;
        }
        else
        {
            lh = this->left->height;
        }
        this->height = 1 + max(lh, rh);
        // b ki height manage karna
        rh = this->height;
        if ((this->par)->left == NULL)
        {
            lh = -1;
        }
        else
        {
            lh = ((this->par)->left)->height;
        }
        (this->par)->height = 1 + max(lh, rh);
        return this->par; // root return
    }
    SymNode *LeftRightRotation()
    {
        this->left = (this->left)->LeftLeftRotation();
        return this->RightRightRotation();
    }
    SymNode *RightLeftRotation()
    {
        this->right = (this->right)->RightRightRotation();
        return this->LeftLeftRotation();
    }
    ~SymNode()
    {
        this->key = "";
        this->height = -1;
        this->address = -1;
    }
};
class SymbolTable
{
private:
    int size;
    SymNode *root;

public:
    int getheight(SymNode *temp)
    {
        if (temp == NULL)
        {
            return -1;
        }
        else
        {
            return temp->height;
        }
    }
    SymbolTable()
    {
        this->size = 0;
        this->root = NULL;
    }
    ~SymbolTable()
    {
    }
    void insert(string k)
    {
        if (this->size == 0)
        {
            SymNode *temp = new SymNode(k);
            size++;
            this->root = temp;
            return;
        }
        SymNode *find;
        find = this->root;
        while (true)
        {
            if (find->right == NULL && find->left == NULL)
            {
                break;
            }
            else if (find->key < k && find->right != NULL)
            {
                find = find->right;
            }
            else if (find->key > k && find->left != NULL)
            {
                find = find->left;
            }
            else
            {
                break;
            }
        }
        SymNode *temp = new SymNode(k);
        if (find->key < k)
        {
            find->right = temp;
            temp->par = find;
        }
        else
        {
            find->left = temp;
            temp->par = find;
        }
        int lh = getheight(find->left);
        int rh = getheight(find->right);
        find->height = 1 + max(lh, rh);
        int hdiff = rh - lh;
        while (find != NULL)
        {
            lh = getheight(find->left);
            rh = getheight(find->right);
            find->height = 1 + max(lh, rh);
            hdiff = rh - lh;
            if (!(hdiff >= -1 && hdiff <= 1))
            {
                break;
            }
            find = find->par;
        }
        if (find == NULL)
        {
            size++;
            return;
        }
        SymNode *parent = find->par;
        SymNode *demn;
        bool bool_left = false;
        if (parent != NULL && parent->left == find)
        {
            bool_left = true;
        }
        if (hdiff < -1)
        {
            int ldiff = getheight((find->left)->right) - getheight((find->left)->left);
            if (ldiff < 0)
            {
                demn = find->RightRightRotation();
            }
            else
            {
                demn = find->LeftRightRotation();
            }
        }
        else
        {
            int rdiff = getheight((find->right)->right) - getheight((find->right)->left);
            if (rdiff > 0)
            {
                demn = find->LeftLeftRotation();
            }
            else
            {
                demn = find->RightLeftRotation();
            }
        }
        if (parent == NULL)
        {
            this->root = demn;
            size++;
            return;
        }
        else
        {
            demn->par = parent;
            if (bool_left)
            {
                parent->left = demn;
            }
            else
            {
                parent->right = demn;
            }
        }
        while (demn != NULL)
        {
            lh = getheight(demn->left);
            rh = getheight(demn->right);
            demn->height = 1 + max(lh, rh);
            demn = demn->par;
        }
        size++;
    }
    int search(string k)
    {
        if (this->size == 0)
        {
            return -1;
        }
        SymNode *find;
        find = this->root;
        bool found = true;
        while (true)
        {
            if (k == find->key)
            {
                break;
            }
            else if (find->left == NULL && find->right == NULL)
            {
                found = false;
                break;
            }
            else if (k < find->key && find->left != NULL)
            {
                find = find->left;
            }
            else if (k > find->key && find->right != NULL)
            {
                find = find->right;
            }
            else
            {
                found = false;
                break;
            }
        }
        if (!found)
        {
            return -1;
        }
        else
        {
            return find->address;
        }
    }

    void assign_address(string k, int count)
    {
        SymNode *find;
        find = this->root;
        bool found = true;
        while (true)
        {
            if (k == find->key)
            {
                break;
            }
            else if (find->left == NULL && find->right == NULL)
            {
                found = false;
                break;
            }
            else if (k < find->key && find->left != NULL)
            {
                find = find->left;
            }
            else if (k > find->key && find->right != NULL)
            {
                find = find->right;
            }
            else
            {
                found = false;
                break;
            }
        }
        find->address = count;
    }
    SymNode *get_root()
    {
        return root;
    }
};
class haash
{
public:
    vector<SymbolTable *> arr;
    haash(int size)
    {
        for (int i = 0; i < size; i++)
        {
            SymbolTable *demp = new SymbolTable();
            arr.push_back(demp);
        }
    }
    int search(string id)
    {
        int idx = hashmap(id);
        bool istrue = false;
        if (arr[idx]->get_root() == NULL)
        {
            return -1;
        }
        else
        {
            return arr[idx]->search(id);
        }
    }
    void insert(string id)
    {
        int idx = hashmap(id);
        int count = arr[idx]->search(id);
        if (count == -1)
        {
            arr[idx]->insert(id);
        }
        else
        {
            arr[idx]->assign_address(id, count + 1);
        }
    }
    int hashmap(std::string id)
    {
        unsigned long hash = 5381;
        int c;

        for (char c : id)
        {
            hash = ((hash << 5) + hash) + c;
            hash = hash%10103;
        }

        return hash%10103;
    }
};
class Dict
{
private:
    // You can add attributes/helper functions here
    haash *noice;
    void toLower(string &s);
    string separators = " .,-:!\"\'()?[];@";

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};
