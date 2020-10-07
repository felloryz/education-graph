#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vertice1;
    int vertice2;
    struct node* next;
} node_t;

void push(node_t** head, int vertice1, int vertice2) {
    node_t* tmp = (node_t*)calloc(sizeof(node_t), 1);
    if(tmp == NULL) return;
    tmp->vertice1 = vertice1;
    tmp->vertice2 = vertice2;
    tmp->next = (*head);
    (*head) = tmp;
}

void print_to_file(node_t* head, FILE* file) {
    fprintf(file, "graph graphname {\n");
    while(head != NULL) {
        fprintf(file, "%d -- ", head->vertice1);
        fprintf(file, "%d;\n", head->vertice2);
        head = head->next;
    }
    printf("\n");
    fprintf(file, "}");
}

void add_edges(node_t** head) {
    while(1) {
        char c;
        int a = 0;
        int b = 0;
        int i = 0;
        int j = 0;
        int m = 1;
        int k, f;
        /* явхршбюмхе хг йнмянкх*/
        char str[7];
        while((c = getchar()) != '\n') {
            str[i] = c;
            i++;
        }
        //printf("i = %d\n", i);

        /* опейпюыемхе явхршбюмхъ п╗аеп*/
        if(str[0] == '-' && str[1] == '1') {
            break;
        }

        /* мюирх онгхжхх пюгдекхрекъ*/
        while(str[j] != '-') {
            j++;
        }
        //printf("j = %d\n", j);

        /* онксвемхе оепбни бепьхмш*/
        k = j-1;
        while(k != -1) {
            a = a + m*(str[k] - '0');
            m = 10*m;
            k--;
        }
        //printf("a = %d\n", a);

        /* онксвемхе брнпни бепьхмш*/
        f = i-1;
        m = 1;
        while(f != j) {
            b = b + m*(str[f] - '0');
            m = 10*m;
            f--;
        }
        //printf("b = %d\n", b);

        push(head, a, b);
    }
}

int main(void)
{
    node_t* head = NULL;

    FILE *file;
    file = fopen("graph.dot", "w");
    if (file == NULL) {
        printf("Error opening file");
        return -1;
    }

    printf("GRAPH var1 - Feodor Ryzhov IU4-32b\n");
    printf("Enter edges (example 1-2) (enter -1 to exit)\n");

    add_edges(&head);

    print_to_file(head, file);

    fclose(file);

    system("dot -Tpng graph.dot -o graph.png");
    system("graph.png");

    return 0;
}
