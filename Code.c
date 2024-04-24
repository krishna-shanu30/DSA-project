#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char value;
    struct Node* left;
    struct Node* right;
};

struct Node* create_node(char value) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int operate(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return 0;
}

struct Node* build_expression_tree(char* expr, int* index) {
    char c = expr[*index];
    *index += 1;
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        struct Node* left = build_expression_tree(expr, index);
        struct Node* right = build_expression_tree(expr, index);
        struct Node* node = create_node(c);
        node->right = right;
        node->left = left;
        return node;
    }
    struct Node* node = create_node(c);
    return node;
}

int eval_expression_tree(struct Node* node) {
    if (node->left == NULL && node->right == NULL) return node->value - '0';
    int a = eval_expression_tree(node->left);
    int b = eval_expression_tree(node->right);
    int value = operate(a, b, node->value);
    return value;
}

int main() {
    char expr[] = "A+B*C/D";
    int index = 0;
    struct Node* root = build_expression_tree(expr, &index);
    int result = eval_expression_tree(root);
    printf("Result: %d\n", result);
    return 0;
}
