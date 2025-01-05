#include "rank/qu_rank.h"

#ifdef TEST_UF
int main() {
    RankQuickUnion* qu = qu_rank_create(10);
    qu_rank_union(qu, 0, 1);
    qu_rank_union(qu, 1, 2);
    qu_rank_union(qu, 2, 3);
    qu_rank_union(qu, 3, 4);

    printf("connected: %d\n", qu_rank_connected(qu, 0, 1));
    printf("connected: %d\n", qu_rank_connected(qu, 1, 4));
    printf("connected: %d\n", qu_rank_connected(qu, 3, 5));

    qu_rank_destroy(qu);
    return 0;
}
#endif