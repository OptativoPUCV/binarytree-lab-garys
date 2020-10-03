#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;

struct TreeNode {
    void* key;
    void * value;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->key = key;
    new->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * tree = (TreeMap *)calloc(1,sizeof(TreeMap));
    tree->lower_than = lower_than;
    //new->lower_than = lower_than;
    return tree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if(searchTreeMap(tree,key) == NULL){
    if(((*(int*)key) > (*(int*)(tree->current->key))) && (tree->current->right == NULL)){
      tree->current->right = createTreeNode(key,value);
      tree->current->right->parent = tree->current;
      tree->current = tree->current->right;
    }
    else{
      if(((*(int*)key) < (*(int*)(tree->current->key))) && (tree->current->left == NULL)){
        tree->current->left = createTreeNode(key,value);
        tree->current->left->parent = tree->current;
        tree->current = tree->current->left;
      }
    }
  }
}

TreeNode * minimum(TreeNode * x){
  while(1){
    if(x->left == NULL){
      return x;
    }
    else{
      x = x->left;
    }
  }
}


void removeNode(TreeMap * tree, TreeNode* node) {
  tree->current = node->parent;
  if((node->left == NULL) && (node->right == NULL)){
    node = NULL;
  }
  else{
    if(((node->right != NULL) && (node->left == NULL))){
      node->parent->right = node->right;
      free(node);
    }
    else{
      if(((node->left != NULL) && (node->right == NULL))){
        node->parent->right = node->left;
        free(node);
      }
    }
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




void * searchTreeMap(TreeMap * tree, void* key) {
    tree->current = tree->root;
    while(1){
      if((*(int*)key) == (*(int*)(tree->current->key))){
        return tree->current->value;
      }
      else{
        if((tree->current->left == NULL) && (tree->current->right == NULL)){
          return NULL;
        }
        else{
          if(((*(int*)key) > (*(int*)(tree->current->key))) && (tree->current->right != NULL)){
            tree->current = tree->current->right;
          }
          else{
            if(tree->current->left != NULL){
              tree->current = tree->current->left;
            }
          }
        }
      }
    }
}


void * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

void * firstTreeMap(TreeMap * tree) {
    return NULL;
}

void * nextTreeMap(TreeMap * tree) {
    return NULL;
}
