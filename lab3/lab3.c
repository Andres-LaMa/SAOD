#include "lib.h"

int main()
{
    heap *h;
    heapnode node;

    h = heap_create(100);
    heap_insert(h, 16, "1");
    heap_insert(h, 14, "2");
    heap_insert(h, 10, "3");
    heap_insert(h, 80, "4");
    heap_insert(h, 70, "5");
    heap_insert(h, 90, "6");
    heap_insert(h, 40, "7");
    heap_insert(h, 30, "8");
    heap_insert(h, 20, "9");
    heap_insert(h, 19, "10");

    node = heap_extract_min(h);
    printf("Item: %d\n", node.key);

    node = heap_extract_min(h);
    printf("Item: %d\n", node.key);

    printf("%d\n", heap_decrease_key(h, 1, 11));

    node = heap_extract_min(h);
    printf("Item: %d\n", node.key);

    heap_free(h);
    return 0;
}