// Thomas van Harskamp // s1007576 // Wiskunde & Informatica
// Jordy Aaldering     // s1004292 // Informatica

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

void swap (vector<int>& tree, int a, int b)
{
    //  Pre-condition:
    assert (a >= 0 && b >= 0 && a != b);
    /*  Post-condition:
        The values of tree[a] and tree[b] are swapped.
    */
    int tmp  = tree[a];
    tree[a] = tree[b];
    tree[b] = tmp;
}

bool push_up (vector<int>& tree, int treeSize)
{
    //  Pre-condition:
    assert (true);
    /*  Post-condition:
        If a child is larger than its parent, the two are swapped.
    */
    bool isSorted = true;

    for (int childPos = 0; childPos < treeSize; childPos++)
    {
        int parentPos = 0;
        if  (childPos > 2)
            parentPos = (childPos - 1) / 2;

        if (tree[childPos] > tree[parentPos])
        {
            isSorted = false;
            swap (tree, childPos, parentPos);
        }
    }
    return isSorted;
}

void build_heap (vector<int>& tree, int treeSize)
{
    //  Pre-condition:
    assert (true);
    /*  Post-condition:
        A heap is created.
    */
    do
        cout << "Building..." << endl;
    while (!push_up(tree, treeSize));
}

void push_down (vector<int>& tree, int heapSize)
{
    //  Pre-condition:
    assert (heapSize >= 0);
    /*  Post-condition:
        The parent keeps swapping with its largest child,
        as long as the value of the parent is lower than that child.
    */
    int parentPos = 0, child1Pos = 1, child2Pos = 2;

    while ((tree[parentPos] < tree[child1Pos] || tree[parentPos] < tree[child2Pos]) && child2Pos < heapSize)
    {
        if (tree[child1Pos] >= tree[child2Pos])
        {
            swap (tree, parentPos, child1Pos);
            parentPos = child1Pos;
        }
        else
        {
            swap (tree, parentPos, child2Pos);
            parentPos = child2Pos;
        }
        child1Pos = 2 * parentPos + 1;
        child2Pos = child1Pos + 1;
    }
}

void pick_heap (vector<int>& tree, int treeSize)
{
    //  Pre-condition:
    assert (true);
    /*  Post-condition:
        The heap is sorted.
    */
    for (int heapSize = treeSize - 1; heapSize > 1; heapSize--)
    {
        cout << "Picking..." << endl;
        swap (tree, 0, heapSize);
        push_down (tree, heapSize - 1);
    }
}

void show_heap (vector<int>& tree, int treeSize)
{
    //  Pre-condition:
    assert (true);
    /*  Post-condition:
    The tree is shown to the user.
    */
    cout << "Heap:";
    for (int i = 0; i < treeSize; i++)
    cout << " " << tree[i];
    cout << endl;
}

int main ()
{
    vector<int> tree = {2,14,30,29,42,30,11,-5,0,51};
    int treeSize = static_cast<int> (tree.size());

    build_heap (tree, treeSize);
    show_heap  (tree, treeSize);

    pick_heap (tree, treeSize);
    show_heap (tree, treeSize);

    return 0;
}

/*
Exercises:
    1a.
        Only elementary operations are used.
        So the complexity order of the function 'easter' is O(1).

    1b.
        n =  sqrt(static_cast<double>(x))
        The if statement has a complexity order of 1.
        The for loop has a complexity order of n.
        The complexity order of the if statement inside of the for loop is also 1.
        f(n) = a + bn
        So the complexity order is O(n).

    2a.
        Phase 1:
                     2
                    / \
                  14  30
                 / \  / \
               29 42 30  11
              / \  \
            -5  0  51
                     30
                    / \
                  42  30
                 / \  / \
               2  51 14 11
              / \  \
            -5  0  29
                     42
                    / \
                  51  30
                 / \  / \
               2  30 14 11
              / \  \
            -5  0  29
                     51
                    / \
                  42  30
                 / \  / \
               2  30 14 11
              / \  \
            -5  0  29

        Phase 2:
            {51,42,30,2,30,14,11,-5,0,29}
            {42,30,30,2,29,14,11,-5,0,51}
            {30,29,30,2,0,14,11,-5,42,51}
            {30,29,-5,2,0,14,11,30,42,51}
            {29,11,-5,2,0,14,30,30,42,51}
            {14,11,-5,2,0,29,30,30,42,51}
            {11,0,-5,2,14,29,30,30,42,51}
            {2,0,-5,11,14,29,30,30,42,51}
            {-5,0,2,11,14,29,30,30,42,51}

    2b.
        push_up:
            The for loop has a complexity order of n.
            push_up depends on the depth of the tree, so ^2log n.
            So the order of run-time complexity is O(^2log n).

        build_heap:
            build_heap contains a do-while loop.
            The complexity order of the do-while loop is n.
            So the order of run-time complexity is O(n * ^2log n)

        push_down:
            push_down contains a while loop.
            The while loop depends on the size of the parent and its children.
            So the order of run-time complexity is O(^2log n).

        pick_heap:
            pick_heap contains a while loop.
            The while loop depends on the heap size.
            So the order of run-time complexity is O(n).
*/
