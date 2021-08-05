//
// Created by ZiT on 2021/8/4.
//

#include <iostream>

using namespace std;

namespace data_structure {

    namespace rb_tree {

        typedef struct Node {
            int key{};
            string val;
            struct Node *left{};
            struct Node *right{};
            struct Node *parent{};
            bool red; // true:红节点 false:黑节点
        } *RbNode;

        //
        // 红黑树是一种特化的AVL，一样可以在查询时实现
        // O(logN) 的时间复杂度，但进行平衡的代价更低
        // 红黑树有以下限制：
        // 1. 节点是红色或黑色
        // 2. 根节点是黑色
        // 3. 叶子节点是NULL，也是黑色
        // 4. 红节点的子节点必是黑色
        // 5. 任一节点到其每个叶子的路径都包含相同数目的黑结点
        //
        class RbTree {
        private:
            // 根节点
            RbNode root;

            // 以指定节点为根，获取对应（子）树的深度
            int depth(RbNode node);

            // 搜索由key指定的节点
            pair<RbNode, RbNode> search(int key);

        public:
            // 搜索由key指定的节点
            string get(int key);
        };

        int RbTree::depth(RbNode node) {
            return 0;
        }

        pair<RbNode, RbNode> RbTree::search(int key) {
            RbNode par = nullptr, tar = root;
            while (tar && tar->key != key) {
                par = tar;
                tar = (tar->key < key) ? tar->right : tar->left;
            }
            return pair(par, tar);
        }

        string RbTree::get(int key) {
            pair<RbNode, RbNode> s = search(key);
            return s.second ? s.second->val : "";
        }


    } // namespace rb_tree
} // namespace data_structure