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

从字典树中删除一个节点的流程相对复杂一些。
