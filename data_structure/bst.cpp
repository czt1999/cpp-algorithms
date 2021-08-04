//
// Created by ZiT on 2021/7/21.
//
#include <optional>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

namespace data_structure {

    namespace binary_search_tree {

        typedef struct Node {
            int key{};
            string val;
            struct Node *left{};
            struct Node *right{};
        } *BiNode;

        /**
         * @brief Binary Search Tree
         */
        class BST {
        private:
            // 根节点
            BiNode root;

            // 以指定节点为根，获取对应（子）树的深度
            int depth(BiNode node);

            // 搜索由key指定的节点，返回<父节点,目标节点(可能为空)>,<空,根节点>
            pair<BiNode, BiNode> search(int key);

        public:
            // 搜索由key指定的节点
            string get(int key);

            // 添加/更新
            string add(int key, const string &val);

            // 删除
            string remove(int key);

            // 获取树的深度
            int depth();
        };

        //
        // ~~~~~~~~~~~~ Implements for BST ~~~~~~~~~~~~
        //

        int BST::depth() {
            return depth(root);
        }

        int BST::depth(BiNode node) {
            return node == nullptr ? 0 : max(depth(node->left), depth(node->right)) + 1;
        }

        pair<BiNode, BiNode> BST::search(int key) {
            BiNode par = nullptr, tar = root;
            while (tar != nullptr && tar->key != key) {
                par = tar;
                tar = (tar->key < key) ? tar->right : tar->left;
            }
            return pair<BiNode, BiNode>(par, tar);
        }

        string BST::get(int key) {
            pair<BiNode, BiNode> s = search(key);
            return s.second == nullptr ? "" : s.second->val;
        }

        string BST::add(int key, const string &val) {
            pair<BiNode, BiNode> s = search(key);
            auto ret = s.second == nullptr ? "" : s.second->val;
            if (s.second == nullptr) {
                auto n = new Node{key, val};
                if (s.first == nullptr) {
                    root = n;
                } else if (s.first->key < key) {
                    s.first->right = n;
                } else {
                    s.first->left = n;
                }
            }
            return ret;
        }

        string BST::remove(int key) {
            pair<BiNode, BiNode> s = search(key);
            auto ret = s.second == nullptr ? "" : s.second->val;
            if (s.second != nullptr) {
                BiNode rpl;
                if (s.second->left == nullptr) {
                    // 被移除的节点没有左子树，用右子树替代它
                    rpl = s.second->right;
                } else {
                    // 用左子树最右端的节点（lr）替代原节点
                    BiNode rpl_parent;
                    for (rpl = s.second->left; rpl->right != nullptr; rpl = rpl->right, rpl_parent = rpl) {}
                    rpl->right = s.second->right;
                    if (rpl != s.second->left) {
                        rpl->left = s.second->left;
                        rpl_parent->right = nullptr;
                    }
                }
                // 释放原节点的空间
                delete s.second;
                // 将替代节点链接到原先的父节点
                if (s.first == nullptr) {
                    // 被移除的是根节点
                    root = rpl;
                } else if (s.first->left == s.second) {
                    s.first->left = rpl;
                } else {
                    s.first->right = rpl;
                }
            }
            return ret;
        }

    } // namespace binary_search_tree
} // namespace data_structure

int main(int argc, char *argv[]) {
    data_structure::binary_search_tree::BST bst{};
    bst.add(3, "3");
    bst.add(2, "2");
    bst.add(1, "1");
    bst.add(4, "4");
    bst.add(5, "5");
    /*       3
     *      / \
     *     2   4
     *    /     \
     *   1       5
     */
    cout << "======= Order 1 ========" << endl;
    cout << "depth(): " << bst.depth() << endl;
    cout << "remove(2): " << bst.remove(2) << endl;
    cout << "depth(): " << bst.depth() << endl;
    cout << "remove(4): " << bst.remove(4) << endl;
    cout << "depth(): " << bst.depth() << endl;
    cout << "remove(1): " << bst.remove(1) << endl;
    cout << "depth(): " << bst.depth() << endl;
    cout << "remove(5): " << bst.remove(5) << endl;
    cout << "depth(): " << bst.depth() << endl;
    cout << "remove(3): " << bst.remove(3) << endl;
    cout << "depth(): " << bst.depth() << endl;
    bst.add(2, "2");
    bst.add(1, "1");
    bst.add(3, "3");
    bst.add(4, "4");
    bst.add(5, "5");
    /*      2
     *     / \
     *    1   3
     *         \
     *          4
     *           \
     *            5
     */
    cout << "======= Order 2 ========" << endl;
    cout << "depth(): " << bst.depth() << endl;
}