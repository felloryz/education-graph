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

        /* СЧИТЫВАНИЕ ИЗ КОНСОЛИ*/
        char str[7];
        while((c = getchar()) != '\n') {
            str[i] = c;
            i++;
        }
        //printf("i = %d\n", i);

        /* ПРЕКРАЩЕНИЕ СЧИТЫВАНИЯ РЁБЕР*/
        if(str[0] == '-' && str[1] == '1') {
            break;
        }

        /* НАЙТИ ПОЗИЦИИ РАЗДЕЛИТЕЛЯ*/
        while(str[j] != '-') {
            j++;
        }
        //printf("j = %d\n", j);

        /* ПОЛУЧЕНИЕ ПЕРВОЙ ВЕРШИНЫ*/
        k = j-1;
        while(k != -1) {
            a = a + m*(str[k] - '0');
            m = 10*m;
            k--;
        }
        //printf("a = %d\n", a);

        /* ПОЛУЧЕНИЕ ВТОРОЙ ВЕРШИНЫ*/
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

int vertice_counter(node_t* head) {
    int n = 0;
    while(head != NULL) {
        n++;
        head = head->next;
    }
    return n;
}

int edge_counter(node_t* head) {
    int n = 0;
    node_t* tmp = head;
    while(head != NULL) {
        n++;
        head = head->next;
    }
    //printf("n = %d\n", n);

    int arr[n*2];
    for(int i = 0; i < n*2; i = i + 2) {
        arr[i] = tmp->vertice1;
        arr[i+1] = tmp->vertice2;
        tmp = tmp->next;
    }

    /*for(int i = 0; i < n*2; i++) {
        printf("%d ", arr[i]);
    }*/

    for(int i = 0; i < n*2 - 1; i++) {
        for(int j = i + 1; j < n*2; j++) {
            if(arr[i] != -1 && arr[i] == arr[j]) {
                arr[j] = -1;
            }
        }
    }

    //printf("\n");
    /*for(int i = 0; i < n*2; i++) {
        printf("%d ", arr[i]);
    }*/

    int k = 0;
    for(int i = 0; i < n*2; i++) {
        if(arr[i] != -1) k++;
    }
    //printf("\n");
    //printf("%d", k);

    return k;
}

int connectivity_check(int e, int v) {
    if(v > (e-1)*(e-2)*0.5) {
        return 1;
    } else return -1;
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

    if (connectivity_check(edge_counter(head), vertice_counter(head)) == 1)
        printf("OK");
    else
        printf("not OK");

    system("dot -Tpng graph.dot -o graph.png");
    system("graph.png");

    return 0;
}
