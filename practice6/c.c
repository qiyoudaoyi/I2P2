#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
    int level;
    struct _NODE *left_child;
    struct _NODE *right_child;
} Node;

void build_tree(Node **now_ptr, int *arr, int l, int r)
{
    if (l > r)  return;

    *now_ptr = (Node*)malloc(sizeof(Node));
    Node *now = *now_ptr;
    int m = (l + r) / 2;
    now->left_child = now->right_child = NULL;
    now->level = arr[m];
    if (l == r) return;
    build_tree(&(now->left_child),  arr, l, m - 1);
    build_tree(&(now->right_child), arr, m + 1, r);
}

void Inorder(Node *root)
{
    if (root == NULL) return;
    Inorder(root->left_child);
    printf(" %d", root->level);
    Inorder(root->right_child);
}

void PrintInorder(Node *root)
{
    printf("BST(in):");
    Inorder(root);
    putchar('\n');
}

int query_heatstroke(Node *now, int x)
{
    if (now == NULL)
        return 0;
    if (now->level > x)
        return query_heatstroke(now->left_child, x);
    if (now->level < x)
        return query_heatstroke(now->right_child, x);
    return 1;
}

int MaxLevel(Node *root)
{
    if (root->right_child == NULL)
        return root->level;
    return MaxLevel(root->right_child);
}

void eat_rat(Node **root_ptr, int x)
{
    Node *root = *root_ptr;
    // if (root == NULL)
    //     return;
    if (root->level < x) {
        eat_rat(&(root->right_child), x);
        return;
    }
    if (root->level > x) {
        eat_rat(&(root->left_child), x);
        return;
    }

    // Case I: No child
    if (root->left_child == NULL && root->right_child == NULL) {
        *root_ptr = NULL;
        free(root);
    }
    // Case II: One Child
    else if (root->right_child == NULL) {
        *root_ptr = root->left_child;
        free(root);
    }
    else if (root->left_child == NULL) {
        *root_ptr = root->right_child;
        free(root);
    }
    // Case III: Two Child
    else {
        root->level = MaxLevel(root->left_child);
        eat_rat(&(root->left_child), root->level);
    }
}

int main()
{
    int n, q, *arr;
    Node *root;
    scanf("%d", &n);
    arr = (int*)malloc(n * sizeof(int));
    for (int i = i; i < n; i++)
        scanf("%d", &arr[i]);
    build_tree(&root, arr, 0, n - 1);

    scanf("%d", &q);
    while (q--) {
        int x;
        scanf("%d", &x);
        if (query_heatstroke(root, x)) {
            printf("We might as well eat it.\n");
            eat_rat(&root, x);
            // PrintInorder(root);
            continue;
        }
        printf("No dinner tonight.\n");
    }
    return 0;
}