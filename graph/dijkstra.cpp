//
// Created by ZiT on 2021/7/27.
//
#include <iostream>

#define INF 1024

namespace graph {

    namespace dijkstra {

        /**
         * @brief Dijkstra 单源最短路径算法
         * @tparam V  顶点数
         * @param g   以领接矩阵表示的图
         * @param src 源点序号
         */
        template<size_t V>
        int *dijkstra(const int g[V][V], int src) {
            // 记录当前最短路径
            int *distance = new int[V];
            memcpy(distance, g[src], sizeof(int) * V);
            // 已确定最短路径的点集
            bool visited[V];
            for (int i = 0; i < V; ++i) {
                visited[i] = (i == src);
            }

            while (true) {
                int to_visit = -1;
                int d = INF;
                // 选择未访问点集中距离最近的点作为中间点
                for (int i = 0; i < V; ++i) {
                    if (!visited[i] && distance[i] < d) {
                        to_visit = i;
                        d = distance[i];
                    }
                }
                if (to_visit < 0) {
                    break;
                }
                // 更新距离
                for (int i = 0; i < V; ++i) {
                    int new_distance = d + g[to_visit][i];
                    if (new_distance < distance[i]) {
                        distance[i] = new_distance;
                    }
                }
                // 更新已访问点集
                visited[to_visit] = true;
            }
            return distance;
        }


    } // namespace dijkstra
} // namespace graph

int main(int argc, char *argv[]) {
    /*
     *           5           3
     *     A -------- B ---------- E -------
     *      \       /   \         /         |
     *     9 \    / 2   1 \     / 1         |
     *        \ /     8     \ /             |
     *         C ----------- D ------- F    | 4
     *          \          /     5    /     |
     *       12  \    ---- 2        / 1     |
     *            \ /             /         |
     *             G ----------- H ---------
     *                     3
     * */
    int graph[8][8] = {
            {0,   5,   9,   INF, INF, INF, INF, INF},
            {5,   0,   2,   1,   3,   INF, INF, INF},
            {9,   2,   0,   8,   INF, INF, 12,  INF},
            {INF, 1,   8,   0,   1,   5,   2,   INF},
            {INF, 3,   INF, 1,   0,   INF, INF, 4},
            {INF, INF, INF, 5,   INF, 0,   INF, 1},
            {INF, INF, 12,  2,   INF, INF, 0,   3},
            {INF, INF, INF, INF, 4,   1,   3,   0}
    };
    int *distance = graph::dijkstra::dijkstra(graph, 0);
    for (int i = 1; i < 8; ++i) {
        std::cout << "A到" << (char) ('A' + i) << "的最短距离为"
                  << distance[i] << std::endl;
    }
    free(distance);
}