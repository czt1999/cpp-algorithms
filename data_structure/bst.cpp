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
            int key;
            string val;
            Node *left;
            Node *right;
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
            string put(int key, const string &val);

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
            return node ? max(depth(node->left), depth(node->right)) + 1 : 0;
        }

        pair<BiNode, BiNode> BST::search(int key) {
            BiNode par = nullptr, tar = root;
            while (tar && tar->key != key) {
                par = tar;
                tar = (tar->key < key) ? tar->right : tar->left;
            }
            return pair<BiNode, BiNode>(par, tar);
        }

        string BST::get(int key) {
            pair<BiNode, BiNode> s = search(key);
            return s.second ? s.second->val : "";
        }

        string BST::put(int key, const string &val) {
            pair<BiNode, BiNode> s = search(key);
            auto ret = s.second ? s.second->val : "";
            if (s.second) {
                s.second->val = val;
            } else {
                auto n = new Node{key, val};
                if (!s.first) {
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
            auto ret = s.second ? s.second->val : "";
            if (s.second) {
                BiNode rpl;
                if (s.second->left) {
                    // 用左子树最右端的节点替代原节点
                    BiNode rpl_parent;
                    for (rpl = s.second->left; rpl->right; rpl_parent = rpl, rpl = rpl->right) {}
                    rpl->right = s.second->right;
                    if (rpl != s.second->left) {
                        rpl_parent->right = rpl->left;
                        rpl->left = s.second->left;
                    }
                } else {
                    // 被移除的节点没有左子树，用右子树替代它
                    rpl = s.second->right;
                }
                // 释放原节点的空间
                delete s.second;
                // 将替代节点链接到原先的父节点
                if (!s.first) {
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
    cout << "======= Order 1 ========" << endl;
    /*       3
     *      / \
     *     2   4
     *    /     \
     *   1       5
     */
    bst.put(3, "3");
    bst.put(2, "2");
    bst.put(1, "1");
    bst.put(4, "4");
    bst.put(5, "5");
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

    cout << "======= Order 2 ========" << endl;
    /*      2
     *     / \
     *    1   3
     *         \
     *          4
     *           \
     *            5
     */
    bst.put(2, "2");
    bst.put(1, "1");
    bst.put(3, "3");
    bst.put(4, "4");
    bst.put(5, "5");
    cout << "remove(3): " << bst.remove(3) << endl;
    cout << "depth(): " << bst.depth() << endl;
    cout << "remove(2): " << bst.remove(2) << endl;
    cout << "depth(): " << bst.depth() << endl;
    cout << "remove(4): " << bst.remove(4) << endl;
    cout << "depth(): " << bst.depth() << endl;
    cout << "remove(5): " << bst.remove(5) << endl;
    cout << "depth(): " << bst.depth() << endl;
    cout << "remove(1): " << bst.remove(1) << endl;
    cout << "depth(): " << bst.depth() << endl;

    cout << "======= Order 3 ========" << endl;
    /*
     *       4
     *      /
     *     1
     *      \
     *       3
     *      /
     *     2
     * */
    bst.put(4, "4");
    bst.put(1, "1");
    bst.put(3, "3");
    bst.put(2, "2");
    cout << "depth(): " << bst.depth() << endl;
    cout << "remove(4): " << bst.remove(4) << endl;
    cout << "depth(): " << bst.depth() << endl;
}