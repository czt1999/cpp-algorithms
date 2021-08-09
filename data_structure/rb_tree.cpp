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

            static bool isRed(RbNode node);

            // 改变指定节点的颜色
            static void flipColor(RbNode node);

            // 因每次修改节点关系都涉及到*parent
            // 故将这部分操作封装成两个工具性函数
            static void pointLeft(RbNode parent, RbNode child);

            static void pointRight(RbNode parent, RbNode child);

            static void unlinkAndDelete(RbNode node);

            static void copyKV(RbNode from, RbNode to);

            static RbNode getMin(RbNode node);

            static RbNode getMax(RbNode node);

            // 左旋（让右子节点替代原节点的位置）
            void rotateLeft(RbNode node);

            // 右旋（让左子节点替代原节点的位置）
            void rotateRight(RbNode node);

            // 根据红黑树的特性调整
            void adjustRed(RbNode node);

            // 移除指定节点
            void remove(RbNode node);

            void adjustBlack(RbNode node);

        public:
            // 返回树的高度
            int depth();

            // 搜索由key指定的节点
            string get(int key);

            // 添加/更新
            string put(int key, const string &val);

            // 删除
            string remove(int key);

            bool isRed(int key);
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

        void RbTree::unlinkAndDelete(RbNode node) {
            if (node) {
                RbNode parent = node->parent;
                if (parent && node == parent->left) {
                    parent->left = nullptr;
                } else if (parent) {
                    parent->right = nullptr;
                }
                delete node;
            }
        }

        void RbTree::copyKV(RbNode from, RbNode to) {
            if (from && to) {
                to->key = from->key;
                to->val = from->val;
            }
        }

        RbNode RbTree::getMin(RbNode node) {
            RbNode min = node;
            if (min) {
                while (min->left) min = min->left;
            }
            return min;
        }

        RbNode RbTree::getMax(RbNode node) {
            RbNode max = node;
            if (max) {
                while (max->right) max = max->right;
            }
            return max;
        }

        bool RbTree::isRed(RbNode node) {
            // 叶子节点（空节点）是黑色
            return node && (RED == node->color);
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
            return pair{par, tar};
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
                    adjustRed(n);
                }
            }
            return ret;
        }

        string RbTree::remove(int key) {
            pair<RbNode, RbNode> s = search(key);
            auto ret = s.second ? s.second->val : "";
            remove(s.second);
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
        void RbTree::adjustRed(RbNode x) {
            // 黑节点无需再做调整
            if (isRed(x)) {
                RbNode y = x->parent;
                if (isRed(y)) {
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
                    adjustRed(y);
                } else if (!y) {
                    // 已是根节点
                    x->color = BLACK;
                }
            }
        }

        void RbTree::remove(RbNode node) {
            if (node) {
                RbNode left = node->left, right = node->right, rpl;
                // 1. 原节点的左子树和右子树均为空
                if (!left && !right) {
                    // 1.1 删除的是根节点
                    if (!node->parent) {
                        root = nullptr;
                        delete node;
                        return;
                    }
                    // 1.2 红节点直接删除
                    // 1.3 黑节点且不是根节点需进行调整
                    adjustBlack(node);
                    unlinkAndDelete(node);
                    return;
                }
                if (left) {
                    // 2. 原节点有左子树
                    // 用左子树最大节点替代原节点
                    rpl = getMax(left);
                } else {
                    // 3. 原节点有右子树
                    // 用右子树最小节点替代原节点
                    rpl = getMin(right);
                }
                // 把替代节点的key和val转移到原节点
                // 节点的连接关系没有改变
                copyKV(rpl, node);
                // 递归，移除替代节点
                remove(rpl);
            }
        }

        bool RbTree::isRed(int key) {
            return isRed(search(key).second);
        }

        void RbTree::adjustBlack(RbNode node) {
            RbNode parent;
            // 红节点或根节点无需调整
            if (!isRed(node) && (parent = node->parent)) {
                bool is_left = (node == parent->left);
                RbNode sibling = (is_left ? parent->right : parent->left);
                RbNode sl = sibling->left, sr = sibling->right;
                // 1. 父节点是红色（兄弟节点是黑色）
                //    且兄弟节点的两个子节点都是黑色
                //    不需要再向上传递
                if (isRed(parent) && !isRed(sl) && !isRed(sr)) {
                    parent->color = BLACK;
                    sibling->color = RED;
                    return;
                }
                // 2. 兄弟节点、兄弟节点的子节点都是黑色
                if (!isRed(sibling) && !isRed(sl) && !isRed(sr)) {
                    sibling->color = RED;
                    adjustBlack(parent);
                    return;
                }
                // 3. 兄弟节点是黑色
                //    且兄弟节点有至少一个红色子节点
                if (!isRed(sibling) && (isRed(sl) || isRed(sr))) {
                    if (is_left) {
                        if (isRed(sl)) {
                            // RL
                            sl->color = parent->color;
                            rotateRight(sibling);
                        } else {
                            // RR
                            sr->color = sibling->color;
                            sibling->color = parent->color;
                        }
                        parent->color = BLACK;
                        rotateLeft(parent);
                    } else {
                        if (isRed(sl)) {
                            // LL
                            sl->color = sibling->color;
                            sibling->color = parent->color;
                        } else {
                            // LR
                            sr->color = parent->color;
                            rotateLeft(sibling);
                        }
                        parent->color = BLACK;
                        rotateRight(parent);
                    }
                    return;
                }
                // 4. 兄弟节点是红色
                parent->color = RED;
                sibling->color = BLACK;
                if (is_left) {
                    rotateLeft(parent);
                } else {
                    rotateRight(parent);
                }
                adjustBlack(node);
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
    rbt.put(6, "6");
    rbt.put(7, "7");
    rbt.put(8, "8");
    rbt.put(9, "9");
    rbt.put(10, "10");
    rbt.put(11, "11");
    rbt.put(12, "12");
    /*
     *                [4]
     *             /       \
     *          [2]         8
     *         /  \      /     \
     *      [1]   [3]  [6]     [10]
     *                /  \     /  \
     *              [5]  [7] [9]  [11]
     *                              \
     *                               12
     */
    cout << "depth(): " << rbt.depth() << endl; // 5
    cout << "isRed(1): " << rbt.isRed(1) << endl;   // 0
    cout << "isRed(2): " << rbt.isRed(2) << endl;   // 0
    cout << "isRed(3): " << rbt.isRed(3) << endl;   // 0
    cout << "isRed(4): " << rbt.isRed(4) << endl;   // 0
    cout << "isRed(5): " << rbt.isRed(5) << endl;   // 0
    cout << "isRed(6): " << rbt.isRed(6) << endl;   // 0
    cout << "isRed(7): " << rbt.isRed(7) << endl;   // 0
    cout << "isRed(8): " << rbt.isRed(8) << endl;   // 1
    cout << "isRed(9): " << rbt.isRed(9) << endl;   // 0
    cout << "isRed(10): " << rbt.isRed(10) << endl; // 0
    cout << "isRed(11): " << rbt.isRed(11) << endl; // 0
    cout << "isRed(12): " << rbt.isRed(12) << endl; // 1
    rbt.remove(12);
    cout << "depth(): " << rbt.depth() << endl; // 4
    rbt.remove(5);
    cout << "depth(): " << rbt.depth() << endl; // 4
}