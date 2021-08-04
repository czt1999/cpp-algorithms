//
// Created by ZiT on 2021/8/1.
//
#include <iostream>
#include <vector>

using namespace std;

namespace data_structure {

    namespace avl_tree {

        typedef struct Node {
            int key{};
            string val;
            struct Node *left{};
            struct Node *right{};
            struct Node *parent{};
            int depth{1};
        } *AvlNode;

        class AVL {
        private:
            // 根节点
            AvlNode root;

            // 以指定节点为根，获取对应（子）树的深度
            static int depth(AvlNode node);

            static int computeDepth(AvlNode node);

            // 因每次修改节点关系都涉及到*parent
            // 故将这部分操作封装成两个工具性函数
            static void pointLeft(AvlNode parent, AvlNode child);

            static void pointRight(AvlNode parent, AvlNode child);

            // 搜索由key指定的节点
            pair<AvlNode, AvlNode> search(int key);

            // 根据AVL的特性调整
            void adjust(AvlNode node);

            void LL(AvlNode node);

            void RR(AvlNode node);

            void LR(AvlNode node);

            void RL(AvlNode node);

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
        // ~~~~~~~~~~~~ Implements for AVL ~~~~~~~~~~~~
        //

        int AVL::depth(AvlNode node) {
            return node ? node->depth : 0;
        }

        int AVL::depth() {
            return depth(root);
        }

        int AVL::computeDepth(AvlNode node) {
            return max(depth(node->left), depth(node->right)) + 1;
        }

        void AVL::pointLeft(AvlNode parent, AvlNode child) {
            if (parent) {
                parent->left = child;
                if (child) {
                    child->parent = parent;
                }
            }
        }

        void AVL::pointRight(AvlNode parent, AvlNode child) {
            if (parent) {
                parent->right = child;
                if (child) {
                    child->parent = parent;
                }
            }
        }

        pair<AvlNode, AvlNode> AVL::search(int key) {
            AvlNode par = nullptr, tar = root;
            while (tar && tar->key != key) {
                par = tar;
                tar = (tar->key < key) ? tar->right : tar->left;
            }
            return pair(par, tar);
        }

        string AVL::get(int key) {
            pair<AvlNode, AvlNode> s = search(key);
            return s.second ? s.second->val : "";
        }

        string AVL::add(int key, const string &val) {
            pair<AvlNode, AvlNode> s = search(key);
            auto ret = s.second ? s.second->val : "";
            if (s.second) {
                // key已存在
                s.second->val = val;
            } else {
                auto n = new Node{key, val};
                if (!s.first) {
                    // 新增的节点作为根节点
                    root = n;
                } else {
                    // 链接到已有节点
                    if (s.first->key < key) {
                        pointRight(s.first, n);
                    } else {
                        pointLeft(s.first, n);
                    }
                    // 对路径上受影响的节点作必要调整
                    for (AvlNode tmp = s.first; tmp; tmp = tmp->parent) {
                        adjust(tmp);
                    }
                }
            }
            return ret;
        }

        string AVL::remove(int key) {
            pair<AvlNode, AvlNode> s = search(key);
            auto ret = s.second ? s.second->val : "";
            if (s.second) {
                AvlNode rpl, last_effected; // 记录受影响的最底部节点
                if (s.second->left) {
                    // 用左子树最右端的节点（lr）替代原节点
                    AvlNode rpl_parent;
                    for (rpl = s.second->left; rpl->right; rpl_parent = rpl, rpl = rpl->right) {}
                    pointRight(rpl, s.second->right);
                    if (rpl != s.second->left) {
                        pointRight(rpl_parent, rpl->left);
                        pointLeft(rpl, s.second->left);
                        last_effected = rpl_parent;
                    } else {
                        last_effected = rpl;
                    }
                } else {
                    // 被移除的节点没有左子树，用右子树替代它
                    rpl = s.second->right;
                    last_effected = s.first;
                }
                // 释放原节点的空间
                delete s.second;
                // 将替代节点链接到原先的父节点
                if (!s.first) {
                    // 被移除的是根节点
                    root = rpl;
                    rpl->parent = nullptr;
                } else if (s.first->left == s.second) {
                    pointLeft(s.first, rpl);
                } else {
                    pointRight(s.first, rpl);
                }
                // 对路径上受影响的节点作必要调整
                for (AvlNode tmp = last_effected; tmp; tmp = tmp->parent) {
                    adjust(tmp);
                }
            }
            return ret;
        }

        void AVL::adjust(AvlNode node) {
            if (node) {
                AvlNode l = node->left, r = node->right;
                int ld = depth(l), rd = depth(r);
                // 先更新高度
                node->depth = max(ld, rd) + 1;
                if (ld - rd > 1) {
                    if (depth(l->left) > depth(l->right)) {
                        LL(node);
                    } else {
                        LR(node);
                    }
                } else if (rd - ld > 1) {
                    if (depth(r->left) > depth(r->right)) {
                        RL(node);
                    } else {
                        RR(node);
                    }
                }
            }
        }

        //      X (unbalanced)
        //     /                      Y
        //    Y               =>    /   \
        //   /                     Z     X
        //  Z
        void AVL::LL(AvlNode x) {
            AvlNode y = x->left, p = x->parent;
            pointLeft(x, y->right);
            pointRight(y, x);
            if (p) {
                if (p->left == x) {
                    pointLeft(p, y);
                } else {
                    pointRight(p, y);
                }
            } else {
                root = y;
                y->parent = nullptr;
            }
            x->depth = computeDepth(x);
        }

        //  X (unbalanced)
        //   \                        Y
        //    Y               =>    /   \
        //     \                   X     Z
        //      Z
        void AVL::RR(AvlNode x) {
            AvlNode y = x->right, p = x->parent;
            pointRight(x, y->left);
            pointLeft(y, x);
            if (p) {
                if (p->left == x) {
                    pointLeft(p, y);
                } else {
                    pointRight(p, y);
                }
            } else {
                root = y;
                y->parent = nullptr;
            }
            x->depth = computeDepth(x);
        }

        //    X (unbalanced)           X
        //   /                        /
        //  Y                 =>     Z      =>   LL(X)
        //   \                      /
        //    Z                    Y
        void AVL::LR(AvlNode x) {
            AvlNode y = x->left, z = y->right;
            pointRight(y, z->left);
            pointLeft(z, y);
            pointLeft(x, z);
            y->depth = computeDepth(y);
            z->depth = computeDepth(z);
            LL(x);
        }

        //   X (unbalanced)       X
        //    \                    \
        //     Y              =>    Z       =>   RR(X)
        //    /                      \
        //   Z                        Y
        void AVL::RL(AvlNode x) {
            AvlNode y = x->right, z = y->left;
            pointLeft(y, z->right);
            pointRight(z, y);
            pointRight(x, z);
            y->depth = computeDepth(y);
            z->depth = computeDepth(z);
            LL(x);
        }

    } // namespace avl_tree
} // namespace data_structure

int main(int argc, char *argv[]) {
    data_structure::avl_tree::AVL avl{};
    cout << "======= Order 1 ========" << endl;
    avl.add(1, "1");
    avl.add(2, "2");
    avl.add(3, "3");
    avl.add(4, "4");
    avl.add(5, "5");
    /*       2
     *      / \
     *     1   4
     *        / \
     *       3   5
     */
    cout << "depth(): " << avl.depth() << endl;
    cout << "remove(2): " << avl.remove(2) << endl;
    /*       4
     *      / \
     *     1   5
     *      \
     *       3
     */
    cout << "depth(): " << avl.depth() << endl;
    cout << "remove(4): " << avl.remove(4) << endl;
    /*       3
     *      / \
     *     1   5
     */
    cout << "depth(): " << avl.depth() << endl;
    cout << "remove(1): " << avl.remove(1) << endl;
    cout << "depth(): " << avl.depth() << endl;
    cout << "remove(5): " << avl.remove(5) << endl;
    cout << "depth(): " << avl.depth() << endl;
    cout << "remove(3): " << avl.remove(3) << endl;
    cout << "depth(): " << avl.depth() << endl;
}