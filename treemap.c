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
  TreeNode * aux;
  if((node->left == NULL) && (node->right == NULL)){
    tree->current = node->parent;
    if(tree->current->left == node){
      tree->current->left = NULL;
      free(node);
    }
    else{
      tree->current->right = NULL;
      free(node);
    }
  }
  else{
    if(((node->right != NULL) && (node->left == NULL))){
      if(node->parent->right == node){
        node->parent->right = node->right;
        node->parent->right->parent = node->parent;
        free(node);
      }
      else{
        node->parent->left = node->right;
        node->parent->right->parent = node->parent;
        free(node);
      }
    }
    else{
      if(((node->left != NULL) && (node->right == NULL))){
        if(node->parent->left == node){
          node->parent->left = node->left;
          node->parent->right->parent = node->parent;
          free(node);
        }
        else{
          node->parent->right = node->left;
          node->parent->right->parent = node->parent;
          free(node);
        }
      }
      else{
        if((node->right != NULL) && (node->left != NULL)){
          aux = minimum(node);
          printf("%d\n",(*(int*)(aux->key)));
          node->key = aux->key;
          node->value = aux->value;
          if((aux->left == NULL) && (aux->right == NULL)){
            if(aux->parent->left == aux){
              aux->parent->left = NULL;
              free(aux);
            }
            else{
              aux->parent->right = NULL;
              free(aux);
            }
          }
          else{
            if(((aux->right != NULL) && (aux->left == NULL))){
              if(aux->parent->right == aux){
                aux->parent->right = aux->right;
                aux->parent->right->parent = aux->parent;
                free(aux);
              }
              else{
                aux->parent->left = aux->right;
                aux->parent->right->parent = aux->parent;
                free(aux);
              }
            }
            else{
              if(((aux->left != NULL) && (aux->right == NULL))){
                if(aux->parent->left == aux){
                  aux->parent->left = aux->left;
                  aux->parent->right->parent = aux->parent;
                  free(aux);
                }
                else{
                  aux->parent->right = aux->left;
                  aux->parent->right->parent = aux->parent;
                  free(aux);
                }
              }
            }
          }
        }
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
  tree->current = tree->root;
  TreeNode * aux = tree->root;
  while(1){
    if(((*(int*)key) < (*(int*)(tree->current->key))) && (tree->current->key > aux->key)){
      aux = tree->current;
    }
    if((*(int*)key) == (*(int*)(tree->current->key))){
      aux = tree->current;
      return aux->value;
    }
    else{
      if((tree->current->left == NULL) && (tree->current->right == NULL)){
        if(((*(int*)key) > (*(int*)(aux->key)))){
          return NULL;
        }
        return aux->value;
      }
      else{
        if(((*(int*)key) > (*(int*)(tree->current->key))) && (tree->current->right != NULL)){
          tree->current = tree->current->right;
        }
        else{
          if((tree->current->left != NULL)){
            tree->current = tree->current->left;
          }
        }
      }
    }
  }
}

void * firstTreeMap(TreeMap * tree) {
    tree->current = tree->root;
    while(1){
      if(tree->current->left != NULL){
        tree->current = tree->current->left;
      }
      else{
        return tree->current->key;
      }
    }
    
}

void * nextTreeMap(TreeMap * tree) {
  printf("%d\n",(*(int*)(tree->current->key)));
  if(tree->current->right != NULL){
    tree->current = tree->current->right;
    while(1){
      printf("%d\n",(*(int*)(tree->current->key)));
      if(tree->current->left == NULL){
        return tree->current->value;
      }
      else{
        tree->current = tree->current->left;
      }
    }
  }
  else{
    TreeNode * aux = tree->current;
    while(1){
      if(tree->current == tree->root){
        return tree->current->value;
      }
      else{
        if((*(int*)tree->current->key) > (*(int*)(aux->key))){
          aux = tree->current;
          return tree->current->value;
        }
        tree->current = tree->current->parent;
      }
    }
  }
  return tree->current->value;
}
