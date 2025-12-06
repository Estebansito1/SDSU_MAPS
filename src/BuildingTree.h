/*This code defines a simple binary search tree used to store and quickly
 *look up buildings by name. Esch node keeps a buildings name =key and ID,
 *the tree inserts nodes in alphabetical order to allow fast searching.
 */

#ifndef BUILDINGTREE_H
#define BUILDINGTREE_H

#include <string>

    //data structure for each node each building
    //node represents one building in the tree
    struct BuildingNode
    {
        std::string key;
        int id;
        BuildingNode* left;
        BuildingNode* right;

        //hold one building entry inside the binary search tree
        BuildingNode(const std::string& k, int i)
            :key(k), id(i), left(nullptr), right(nullptr){}
    };
//////
    // these functions are allowed to be used by
    //others to inser buildings or search for them
    class BuildingTree
    {
    public:
        BuildingTree(): root(nullptr){}

        void insert(const std::string& key, int id)
        {
            root=insertRec(root, key, id);
        }

        //find the ID of the building by its name=key
        //search down the tree comparing keys
        int find(const std::string& key)const
        {
            BuildingNode* cur =root;
            while (cur)
            {
                if (key==cur->key)return cur->id;
                if (key<cur->key) cur=cur->left;
                else cur=cur->right;
            }
            return -1;
        }
        // private helper logic contains the internal root pointer
        //and recursuve insert function
        private:
            BuildingNode* root;
        static BuildingNode* insertRec(BuildingNode* node, const std::string& key, int id)
        {
            if (!node) return new BuildingNode(key, id);
            if (key<node->key) node->left = insertRec(node->left, key, id);
            else if (key>node->key) node->right = insertRec(node->right, key, id);
            return node;
        }

    };

#endif


