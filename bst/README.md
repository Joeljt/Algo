## 二叉搜索树

二叉搜索树满足以下四个条件：

1. 若任意节点的左子树不为空，则左子树上所有结点的值都小于它的根节点的值
2. 若任意节点的右子树不为空，则右子树上所有结点的值都大于它的根节点的值
3. 任意节点的左、右子树也分别为二叉搜索树
4. 没有键值相等的结点

由于二分搜索树天然的递归结构，导致在具体的实现上会大量使用递归来处理。

### 插入

根据二分搜索树的性质，我们可以直接检查要插入的节点应该位于当前节点的左子树还是右子树，然后相对应地递归插入，或者更新迭代条件即可。

#### 递归版本

我们可以通过返回插入的节点，来很方便地用递归来处理整个插入动作。

递归终止条件是当前节点为空，此时直接创建新节点并返回，返回的节点会赋值给正确的节点位置，直到最后返回给根节点。

```c
BSTNode* bst_insert_node(BSTNode* node, int data) {
    if (node == NULL) {
        return createBSTNode(data);
    } else if (data < node->data) {
        node->left = bst_insert(node->left, data);
    } else {
        node->right = bst_insert(node->right, data);
    }
    return node;
}

void bst_insert(BST* bst, int data) {
    bst->root = bst_insert_node(bst->root, data);
}
```

#### 迭代版本

迭代版本需要额外维护一个 parent 节点，用来存储待插入节点的父节点。

从根节点出发，根据二叉搜索树的性质，不断在左右子树中判断并选择，直到找到待插入节点的父节点。

然后根据待插入节点与父节点的值的大小关系，决定插入到父节点的左子树还是右子树，从而完成插入。

```c
void bst_insert_iter(BST* bst, int data) {
    BSTNode* node = bst->root;
    
    if (node == NULL) {
        bst->root = createBSTNode(data);
        return;
    }

    BSTNode* parent = NULL;
    while (node != NULL) {
        parent = node;
        if (data < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    BSTNode* new_node = createBSTNode(data);
    if (data < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}
```

### 查找

二叉搜索树的查找操作与插入操作类似，都是根据二叉搜索树的性质，不断在左右子树中判断并选择，直到找到待查找的节点。

#### 递归版本

```c
bool bst_search(BST* bst, int data) {
    return bst_search_node(bst->root, data);
}

bool bst_search_node(BSTNode* node, int data) {
    if (node == NULL) {
        return false;
    } else if (data == node->data) {
        return true;
    } else if (data < node->data) {
        return bst_search_node(node->left, data);
    } else {
        return bst_search_node(node->right, data);
    }
}
```

#### 迭代版本

```c
bool bst_search_iter(BST* bst, int data) {
    BSTNode* node = bst->root;
    while (node != NULL) {
        if (data == node->data) {
            return true;
        } else if (data < node->data) {
            node = node->left;
        } else if (data > node->data) {
            node = node->right;
        }
    }
    return false;
}
```

### 删除

二叉搜索树的删除操作相对复杂，需要考虑三种情况：

1. 要删除的节点没有子节点（直接删除即可）
2. 要删除的节点有一个子节点（用子节点替换当前节点即可）
3. 要删除的节点有两个子节点（用左子树的最大节点或右子树的最小节点替换当前节点即可）

前两种情况比较简单，不用过分讨论，主要是第三种情况。

由于二叉搜索树特殊的性质，我们在删除某个有两个子节点的父节点时，需要考虑如何在删除后移动节点，以保证二叉搜索树的性质。

```
           8                   8                   8
         /   \               /   \               /   \
        4     12     →      4     14   或       4     10
       / \   /  \          / \   /             / \      \
      2   6 10   14       2   6 10            2   6     14
     
删除值为12的节点过程：
1. 发现节点12有两个子节点(10和14)
2. 将右子树的最小值(14)整个移动到12的位置，左子树(10)保持不变 
3. 或者左子树的最大值(10)整个移动到12的位置，右子树(14)保持不变
```

以上图为例，如果要删除节点 12，则需要用节点 14 替换节点 12，以保证二叉搜索树的性质。

根据上面的解释，在实现删除方法之前，我们需要两个辅助函数：

一个用来找到 BST 树的最小节点，一个用来找到 BST 树的最大节点。

```c
// 在二分搜索树中，一直向左子树遍历就可以找到最小的节点
BSTNode* find_min_node(BSTNode* node) {
    if (node == NULL) {
        return NULL;
    }
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// 在二分搜索树中，一直向右子树遍历就可以找到最大的节点
BSTNode* find_max_node(BSTNode* node) {
    if (node == NULL) {
        return NULL;
    }
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}
```

根据我们之前的解释，我们要找的是目标节点的右子树的最小节点，或者左子树的最大节点，也就是：

```c
BSTNode* leftMax = find_max_node(node->left);
BSTNode* rightMin = find_min_node(node->right);
```

有了上面这些辅助函数，我们就可以实现删除操作了。

#### 递归版本

```c

void bst_delete(BST* bst, int data) {
    bst->root = bst_delete_node(bst->root, data);
}

BSTNode* bst_delete_node(BSTNode* node, int data) {
    if (node == NULL) {
        return NULL;
    }
    if (data < node->data) {
        // 如果要删除的元素在左子树，则递归向下去左子树里寻找
        node->left = bst_delete_node(node->left, data);
    } else if (data > node->data) {
        // 如果要删除的元素在右子树，则递归向下去右子树里寻找
        node->right = bst_delete_node(node->right, data);
    } else {
        // 如果左子树为空，则直接用右子树替换当前节点
        // 如果当前节点是叶子节点，也会走到这里，而且返回值也是 NULL，不影响结果
        if (node->left == NULL) {
            return node->right;
        } else if (node->right == NULL) {
            // 如果右子树为空，则直接用左子树替换当前节点
            return node->left;
        } else {
            // 如果左右子树都不为空，则用右子树的最小节点替换当前节点
            BSTNode* min_node = find_min_node(node->right);
            // 用右子树的最小节点替换当前节点
            node->data = min_node->data;
            // 替换后，需要把右子树的最小节点删除，以保证二叉搜索树的性质
            node->right = bst_delete_node(node->right, min_node->data);

            // 或者，这里也可以用左子树的最大节点替换当前节点
            // 都能保证二叉搜索树的性质，但是这两种方式最终的树结构不一样
            // BSTNode* max_node = find_max_node(node->left);
            // node->data = max_node->data;
            // node->left = bst_delete_node(node->left, max_node->data);
        }
    }
    return node;
}
```

#### 迭代版本

迭代版本的思路与递归版本类似，但是代码实现要复杂很多。

```c
void bst_delete_iter(BST* bst, int data) {
    BSTNode* node = bst->root;
    BSTNode* parent = NULL;
    
    // 查找要删除的节点
    while (node != NULL && node->data != data) {
        parent = node;
        if (data < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    
    // 如果没找到节点，直接返回
    if (node == NULL) {
        return;
    }
    
    // 情况1和2：节点有0个或1个子节点
    if (node->left == NULL || node->right == NULL) {
        BSTNode* child = (node->left != NULL) ? node->left : node->right;
        
        // 如果是根节点
        if (parent == NULL) {
            bst->root = child;
        }
        // 如果不是根节点
        else if (parent->left == node) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(node);
    }
    // 情况3：节点有两个子节点
    else {
        // 找到右子树中的最小节点及其父节点
        BSTNode* successor_parent = node;
        BSTNode* successor = node->right;
        
        while (successor->left != NULL) {
            successor_parent = successor;
            successor = successor->left;
        }
        
        // 复制后继节点的值到当前节点
        node->data = successor->data;
        
        // 处理后继节点的连接关系
        if (successor_parent == node) {
            // 如果后继节点就是要删除节点的右子节点
            successor_parent->right = successor->right;
        } else {
            // 如果后继节点在右子树的左侧
            successor_parent->left = successor->right;
        }
        
        // 删除后继节点
        free(successor);
    }
}
```

### 深度优先遍历

从根节点出发，沿着树的深度遍历树的节点，尽可能深的搜索树的分支的遍历方式。

深度优先遍历有三种方式：前序遍历、中序遍历、后序遍历。

#### 递归版本

```c
void preorder_traversal(BSTNode* node) {
    printf("%d ", node->data);
    preorder_traversal(node->left);
    preorder_traversal(node->right);
}

void inorder_traversal(BSTNode* node) {
    inorder_traversal(node->left);
    printf("%d ", node->data);
    inorder_traversal(node->right);
}

void postorder_traversal(BSTNode* node) {
    postorder_traversal(node->left);
    postorder_traversal(node->right);
    printf("%d ", node->data);
}
```

#### 迭代版本

迭代版本的实现思路是使用栈来模拟递归调用栈，通过栈来保存遍历过程中的节点，从而实现非递归的深度优先遍历。

```c
void preorder_iter(BSTNode* root) {
    if (root == NULL) return;
    
    BSTNode* stack[100];
    int top = -1;
    stack[++top] = root;
    
    while (top >= 0) {
        BSTNode* node = stack[top--];
        printf("%d ", node->data);
        
        // 先压入右子节点，再压入左子节点，这样出栈时就是先左后右
        if (node->right) stack[++top] = node->right;
        if (node->left) stack[++top] = node->left;
    }
}

void inorder_iter(BSTNode* root) {
    if (root == NULL) return;
    
    BSTNode* stack[100];
    int top = -1;
    BSTNode* current = root;
    
    while (current || top >= 0) {
        // 将所有左子节点入栈
        while (current) {
            stack[++top] = current;
            current = current->left;
        }
        
        // 处理栈顶节点
        current = stack[top--];
        printf("%d ", current->data);
        
        // 转向右子树
        current = current->right;
    }
}

void postorder_iter(BSTNode* root) {
    if (root == NULL) return;
    
    BSTNode* stack[100];
    int top = -1;
    BSTNode* current = root;
    BSTNode* lastVisited = NULL;
    
    while (current || top >= 0) {
        // 将所有左子节点入栈
        while (current) {
            stack[++top] = current;
            current = current->left;
        }
        
        current = stack[top];  // 查看栈顶元素
        
        // 如果右子树为空或已经访问过，则可以访问当前节点
        if (current->right == NULL || current->right == lastVisited) {
            printf("%d ", current->data);
            lastVisited = current;
            top--;
            current = NULL;
        } else {
            // 否则转向右子树
            current = current->right;
        }
    }
}
```

### 广度优先遍历

广度优先遍历（BFS）是一种从根节点开始，沿着树的宽度遍历树的节点，也就是自顶向下横向遍历。

广度优先遍历通常使用队列来实现，因为队列的先进先出（FIFO）特性可以很好地模拟广度优先遍历的顺序。

```c
void bfs_traversal(BSTNode* root) {
    if (root == NULL) return;
    
    BSTNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    while (front < rear) {
        BSTNode* node = queue[front++];
        printf("%d ", node->data);
        
        if (node->left) queue[rear++] = node->left;
        if (node->right) queue[rear++] = node->right;
    }
}
```

利用队列实现广度优先遍历的思路如下：

1. 先将根节点入队，并维护队首队尾指针；
2. 当队列不为空时，从队首取出一个节点，访问该节点，并将其左右子节点入队；
    - 在这里访问节点的时候，访问的就是当前层的节点
    - 然后通过访问左右子节点，将下一层的节点入队，同时维护队尾指针，保证循环的进行
3. 重复步骤2，直到队列为空。

通过这种方式，可以依次访问树的每一层节点，从而实现广度优先遍历。

#### 递归版本

广度优先队列也可以使用递归来实现，思路是使用递归函数来打印每一层的节点，然后依次访问这些节点，并将其左右子节点入队，从而实现广度优先遍历。

```c
// 获取树的高度
int get_height(BSTNode* root) {
    if (root == NULL) return 0;
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

// 打印指定层的所有节点
void print_level(BSTNode* root, int level) {
    if (root == NULL) return;
    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
    }
}

// 递归版本的广度优先遍历
void bfs_recursive(BSTNode* root) {
    int height = get_height(root);
    for (int level = 1; level <= height; level++) {
        print_level(root, level);
    }
}
```

这个递归实现：

1. 首先获取树的高度
2. 然后逐层打印节点
3. 对每一层使用递归来访问该层的所有节点

但是这个实现的时间复杂度是 O(n²)，而迭代版本的时间复杂度是 O(n)，所以在实际应用中还是推荐使用迭代（队列）版本。
