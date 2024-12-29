## Trie

字典树是一棵多叉树，用来高效地处理字符串数据，比如前缀搜索、单词搜索等。

字典树是典型的空间换时间的例子，以存储小写英文单词为例，通过在每个节点都持有 26 个指针，来快速地进行前缀搜索。

### 思路

如前所述，字典树的本质是一棵多叉树，每个节点都持有 26 个指针，用来存储可能的 26 个英文字母。

1. 通过 ASCII 码与数组角标的对应关系，我们可以对字母进行 'a' 的偏移，来用下标代表具体的字母，而不需要显式地存储；
2. 由于多个单词可能会共用前缀，通过增加 is_word 的标记来区分某个节点位置是否存储了某个单词，还是只是某个单词的字母而已；

字典树的核心大概就是这样，基于此，我们就可以实现一个字典树。

### 实现

#### 添加

从根节点开始，对目标单词的每个字母进行验证，查看是否存在该字母的节点。

如果不存在就进行插入，如果存在就继续向下，直到单词遍历完成，把每个字母都插入到树中，同时标记该单词的末尾节点即可完成插入。

```c
void insert_node(TrieNode* node, char* word, int depth) {
  if (node == NULL) return; // 防御性编程

  // 如果到达字符串的末尾，标记该节点为单词结尾
  if (word[depth] == '\0') {
    node->is_word = true;
    return;
  }

  // 计算当前字符对应的索引
  int index = word[depth] - 'a';

  // 如果子节点不存在，创建一个新的 TrieNode
  if (node->children[index] == NULL) {
    node->children[index] = (TrieNode*)malloc(sizeof(TrieNode));
    memset(node->children[index], 0, sizeof(TrieNode)); // 初始化新节点
  }

  // 递归处理下一个字符
  insert_node(node->children[index], word, depth + 1);
}

void insert(Trie* trie, char* word) {
  if (trie == NULL || word == NULL) return; // 防御性编程
  insert_node(trie->root, word, 0);
}
```

### 查找

查找的逻辑与插入基本一致，这里使用迭代的方式实现。

从根节点开始向下查找每个字母，如果某个字母没找到，说明树里不存在该单词；如果找到了末尾都存在，但是对应的节点没有 is_word 标记，也说明没有插入过该单词，是其他单词的前缀。

```c
bool contains(Trie* trie, const char* word) {
  TrieNode* curr = trie->root;
  for (int i = 0; word[i] != '\0'; i++) {
    int index = word[i] - 'a';
    if (curr->children[index] != NULL) {
      curr = curr->children[index];
    } else {
      return false;
    }
  }
  return curr->is_word;
}
```

### 删除

从字典树中删除一个节点的流程相对复杂一些，整体思路是：

1. 从根节点开始向下，一直到目标单词的最后一个字母；
2. 确定该字母是否有标记单词，如果有就取消标记，从树中移除；如果没有说明单词不存在，不需要删除；
3. 标记删除后，需要逐层向上回溯，检查：当前节点是否有存储其他单词，或者；是否有子节点；
4. 如果既没有存储其他单词，也不包含其他子节点，说明这个字母只是被刚刚删掉的这个单词添加的，就可以删除该节点；
5. 否则，不可以删除节点，退出即可；

具体实现的时候，无论是递归或者迭代，思路是完全相同的。

#### 迭代

```c
bool delete(Trie* trie, char* word) {
  TrieNode* curr = trie->root;
  TrieNode* path[100]; // 存储路径上的节点信息 
  int indexes[100]; // 存储索引信息
  int depth = 0; // 记录向下遍历到的字典树深度，在倒序回溯的时候使用

  // 1. 先尝试在树里找到这个单词，看看是不是有插入过
  for (int i = 0; word[i] != '\0'; i++) {
    int index = word[i] - 'a';
    if (curr->childred[index] == NULL) {
      // 单词不存在，直接返回即可
      return false;
      // 继续向下遍历，找到对应的单词
      curr = curr->children[index];
      // 同时，维护路径、下标和深度信息
      path[depth] = curr;
      indexes[depth] = index; 
      depth++;
    }
  }

  if (is_word_or_empty(curr)) {

  }

  // 2. 检查找到的这个位置是不是有单词，没有的话就可以直接返回
  if (!curr->is_word) return false;
  
  // 3. 标记当前位置不再存储对应的单词
  curr->is_word = false;

  // 4. 检查当前节点是不是有子节点
  // 如果有子节点就不能删除该节点，标记删除单词以后就可以结束了
  for (int i = 0; i < 26; i++) {
    if (curr->children[i] != NULL) {
      return true;
    }
  }

  // 4. 根据向下寻找单词的时候记录的信息，对整个路径上的节点进行检查
  for (int i = depth - 1; i >= 0; i--) {
    // 经过前面的检查，可以确认【当前节点的子节点】既不是单词尾，也没有子节点，可以放心删除了
    // path[depth] 是第 depth 层对应的那个单词节点，indexes[depth] 存储的是对应的字母角标
    // 所以通过 path[i]->children[indexes[i]] 就可以找到目标节点
    free(path[i]->children[indexes[i]]);
    path[i]->children[indexes[i]] = NULL;

    // 之后还要检查一下当前节点的情况，决定是否要提前退出，终止删除逻辑
    if (path[i]->is_word) {
      return true;
    }
    for (int j = 0; j < 26; j++) {
      if (path[i]->children[j] != NULL)
        return true;
    }
  }

  return true;
}
```

#### 递归

由于字典树的树形结构，还是递归的方式更直观，也更好理解一些。

核心逻辑就是一直向下递到单词尾，然后判断单词是否存在，以及节点是否存在子节点，并将这个结果通过返回值告知上层调用。

在向上归的时候，根据下层调用的返回值，在上层做特定的逻辑处理，从而完成自顶向下的深度遍历以及自底向上的回溯处理。

整个过程有点类似 BOM 的事件传递，向下传递后向上冒泡，过程中可能被任何 target 消费后停止传播。

```c
bool is_empty(TrieNode* node) {
  for (int i = 0; i < 26; i++) {
    if (node->children[i] == NULL) {
      return false;
    }
  }
  return true;
}

bool delete(TrieNode* node, char* word, int depth) {
  // 递归到底的情况：到达单词末尾
  if (word[depth] == '\0') {
    if (node->is_word) {
      // 将当前单词从字典树里删除
      node->is_word = false;
      // 删除单词后需要在这里维护 size 信息
      trie->size--;
      // 然后检查当前节点是否还有其他子节点，有子节点就不能删除当前节点了
      // 通过返回值的方式，把节点的情况告知上层调用
      return is_empty(node);
    }
    // 单词作为其他单词的前缀出现，树中不存在目标单词，直接退出即可
    return false;
  }

  // 从根节点开始，向下递归检查，并根据下层调用的返回值来决定当前节点能否被释放
  int index = word[depth] - 'a';
  // // 检查子节点能不能被删除
  if (delete(node->children[index], word, depth + 1)) {
    // 当前节点的子节点既没有存储单词，也没有任何子节点，可以被安全释放
    free(node->children[index]);
    node->children[index] = NULL;

    // 然后需要检查当前节点的情况，仍然以返回值的性质告知上层调用
    return !node->is_word && is_empty(node);
  }

  // 子节点返回 false，证明要么存储了其他单词，要么还有其他子节点，不能删除
  // 所以这里也 false，表明对当前节点执行删除操作，因为子节点被占用
  return false;
}
```