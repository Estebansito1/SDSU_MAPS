#ifndef BUILDINGTREE_H
#define BUILDINGTREE_H

#include <string>

    struct BuildingNode
    {
        std::string key;
        int id;
        BuildingNode* left;
        BuildingNode* right;

        BuildingNode(const std::string& k, int i)
            : key(k), id(i), left(nullptr), right(nullptr) {}
    };
/////////////////////
//
    class BuildingTree
    {
    public:
        BuildingTree() : root(nullptr) {}

        void insert(const std::string& key, int id)
        {
            root = insertRec(root, key, id);
        }

    int find(const std::string& key) const
        {
        BuildingNode* cur = root;
        while (cur)
            {
                if (key == cur->key) return cur->id;
                if (key < cur->key) cur = cur->left;
                else cur = cur->right;
            }
            return -1;
        }
//////////////
//
    private:
        BuildingNode* root;

        static BuildingNode* insertRec(BuildingNode* node, const std::string& key, int id)
        {
            if (!node) return new BuildingNode(key, id);
            if (key < node->key) node->left  = insertRec(node->left,  key, id);
            else if (key > node->key) node->right = insertRec(node->right, key, id);

            return node;
        }
    };

    #endif


