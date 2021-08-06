//
// Created by ZiT on 2021/8/4.
//

#include <iostream>

#define RED 0
#define BLACK 1

using namespace std;

namespace data_structure {

    namespace rb_tree {

        typedef struct Node {
            int key;
            string val;
            struct Node *left;
            struct Node *right;
            struct Node *parent;
            int color;
        } *RbNode;

        //
        // 红黑树是一种特化的rbt，一样可以在查询时实现
        // O(logN) 的时间复杂度，但进行平衡的代价更低
        // 红黑树有以下限制：
        // 1. 节点是红色或黑色
        // 2. 根节点是黑色
        // 3. 叶子节点是NULL，也是黑色
        // 4. 红节点要么有两个叶子节点，要么有两个黑色的非叶子节点
        // 5. 任一节点到其每个叶子的路径都包含相同数目的黑节点
        //
        class RbTree {
        private:
            // 根节点
            RbNode root;

            // 以指定节点为根，获取对应（子）树的深度
            int depth(RbNode node);

            // 搜索由key指定的节点
            pair<RbNode, RbNode> search(int key);

            // 改变指定节点的颜色
            static void flipColor(RbNode node);

            // 因每次修改节点关系都涉及到*parent
            // 故将这部分操作封装成两个工具性函数
            static void pointLeft(RbNode parent, RbNode child);

            static void pointRight(RbNode parent, RbNode child);

            // 左旋（让右子节点替代原节点的位置）
            void rotateLeft(RbNode node);

            // 右旋（让左子节点替代原节点的位置）
            void rotateRight(RbNode node);

            // 根据红黑树的特性调整
            void adjust(RbNode node);

        public:
            // 返回树的高度
            int depth();

            // 搜索由key指定的节点
            string get(int key);

            // 添加/更新
            string put(int key, const string &val);

            // 删除
            string remove(int key);
        };

        //
        // ~~~~~~~~~~~~ Implements for RbTree ~~~~~~~~~~~~
        //

        int RbTree::depth(RbNode node) {
            return node ? max(depth(node->left), depth(node->right)) + 1 : 0;
        }

        int RbTree::depth() {
            return depth(root);
        }

        void RbTree::pointLeft(RbNode parent, RbNode child) {
            if (parent) {
                parent->left = child;
                if (child) {
                    child->parent = parent;
                }
            }
        }

        void RbTree::pointRight(RbNode parent, RbNode child) {
            if (parent) {
                parent->right = child;
                if (child) {
                    child->parent = parent;
                }
            }
        }

        void RbTree::flipColor(RbNode node) {
            if (node) {
                node->color = (RED == node->color) ? BLACK : RED;
            }
        }

        //
        //   x             y
        //    \     =>    /
        //     y         x
        //
        void RbTree::rotateLeft(RbNode x) {
            RbNode y = x->right, p = x->parent;
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
        }

        //
        //     x         y
        //    /     =>    \
        //   y             x
        //
        void RbTree::rotateRight(RbNode x) {
            RbNode y = x->left, p = x->parent;
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

        string RbTree::put(int key, const string &val) {
            pair<RbNode, RbNode> s = search(key);
            auto ret = s.second ? s.second->val : "";
            if (s.second) {
                // key已存在
                s.second->val = val;
            } else {
                auto n = new Node{key, val};
                // 新增节点默认是红色
                n->color = RED;
                if (!s.first) {
                    // 新增的节点作为根节点
                    root = n;
                    n->color = BLACK;
                } else {
                    // 链接到已有节点
                    if (s.first->key < key) {
                        pointRight(s.first, n);
                    } else {
                        pointLeft(s.first, n);
                    }
                    // 作必要调整
                    adjust(s.first);
                }
            }
            return ret;
        }

        string RbTree::remove(int key) {
            pair<RbNode, RbNode> s = search(key);
            auto ret = s.second ? s.second->val : "";
            if (s.second) {
                int target_color = s.second->color;
                RbNode rpl;
                if (s.second->left) {
                    if ((rpl = s.second->left->right)) {
                        // 用左子树最右端的节点替代原节点
                        RbNode rpl_parent;
                        while (rpl->right) {
                            rpl_parent = rpl;
                            rpl = rpl->right;
                        }
                        pointRight(rpl, s.second->right);
                        if (rpl->left) {
                            // rpl只能是黑节点，只有一个红色左节点
                            rpl->left->color = BLACK;
                        } else {
                            // rpl只能是红节点，无子节点
                        }
                        rpl->color = target_color;
                        pointRight(rpl_parent, rpl->left);
                        pointLeft(rpl, s.second->left);
                    } else {
                        // 用左子树代替原节点
                        rpl = s.second->left;
                        if (rpl->left) {
                            // rpl只能是黑节点，只有一个红色左节点
                            rpl->left->color = BLACK;
                        } else {
                            // rpl只能是红节点，无子节点
                        }
                    }
                } else {
                    // 用右子树替代原节点
                    // rpl只能是红节点，无子节点
                    rpl = s.second->right;
                    rpl->color = BLACK;
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
                // 作必要调整
                adjust(rpl);
            }
            return ret;
        }

        //
        // []表示黑节点，有4种情况需要调整：
        //   1:          2:          3:        4:
        //        [z]       [z]        [z]       [z]
        //        /         /            \         \
        //       y         y              y         y
        //      /           \            /           \
        //     x             x          x             x
        //
        // 2对y右旋可得到1，3对y左旋可得到4（同rbt）
        // 1对z左旋，再变换y和z的颜色
        // 4对z右旋，再变换y和z的颜色
        // 结果形如：
        //            [y]       变换颜色         y
        //          /     \    =========>     /    \
        //        x(z)   z(x)             [x(z)]  [z(x)]
        //
        // （这几次变色操作等价于只对1和4中的x作一次变色）
        // 
        // 下一步：adjust(y)...
        //
        void RbTree::adjust(RbNode x) {
            // 黑节点无需再做调整
            if (x && (RED == x->color)) {
                RbNode y = x->parent;
                if (y && (RED == y->color)) {
                    // y是红节点，则必存在父节点
                    RbNode z = y->parent;
                    if (z->left == y) {
                        if (y->right == x) {
                            // 2: 
                            rotateLeft(y);
                            swap(x, y);
                        }
                        // 1:
                        rotateRight(z);
                    } else {
                        if (y->left == x) {
                            // 3:
                            rotateRight(y);
                            swap(x, y);
                        }
                        // 4:
                        rotateLeft(z);
                    }
                    flipColor(x);
                    // 递归
                    adjust(y);
                } else if (!y) {
                    // 已是根节点
                    x->color = BLACK;
                }
            }
        }

    } // namespace rb_tree
} // namespace data_structure

int main(int argc, char *argv[]) {
    data_structure::rb_tree::RbTree rbt{};
    cout << "======= Order 1 ========" << endl;
    rbt.put(1, "1");
    rbt.put(2, "2");
    rbt.put(3, "3");
    rbt.put(4, "4");
    rbt.put(5, "5");
    /*       2
     *      / \
     *     1   4
     *        / \
     *       3   5
     */
    cout << "depth(): " << rbt.depth() << endl;
    cout << "remove(2): " << rbt.remove(2) << endl;
    /*       4
     *      / \
     *     1   5
     *      \
     *       3
     */
    cout << "depth(): " << rbt.depth() << endl;
    cout << "remove(4): " << rbt.remove(4) << endl;
    /*       3
     *      / \
     *     1   5
     */
    cout << "depth(): " << rbt.depth() << endl;
    cout << "remove(1): " << rbt.remove(1) << endl;
    cout << "depth(): " << rbt.depth() << endl;
    cout << "remove(5): " << rbt.remove(5) << endl;
    cout << "depth(): " << rbt.depth() << endl;
    cout << "remove(3): " << rbt.remove(3) << endl;
    cout << "depth(): " << rbt.depth() << endl;
}