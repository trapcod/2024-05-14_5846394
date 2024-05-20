#include <stdio.h>
#include <stdlib.h> // exit �Լ��� ����ϱ� ���� �ʿ�

#define MAX_LIST_SIZE 100 // ����Ʈ�� �ִ�ũ��

typedef int element; // �׸��� ����

typedef struct {
    element array[MAX_LIST_SIZE]; // �迭 ����
    int size; // ���� ����Ʈ�� ����� �׸���� ����
} ArrayListType;

// ���� ó�� �Լ�
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// ����Ʈ �ʱ�ȭ �Լ�
void init(ArrayListType* L)
{
    L->size = 0;
}
// ����Ʈ�� ��� ������ 1�� ��ȯ
// �׷��� ������ 0�� ��ȯ
int is_empty(ArrayListType* L)
{
    return L->size == 0;
}
// ����Ʈ�� ���� �� ������ 1�� ��ȯ
// �׷��� ������ 0�� ��ȯ
int is_full(ArrayListType* L)
{
    return L->size == MAX_LIST_SIZE;
}

// ����Ʈ ���
void print_list(ArrayListType* L)
{
    for (int i = 0; i < L->size; i++)
        printf("%d->", L->array[i]);
    printf("NULL\n");
}

void insert_last(ArrayListType* L, element item)
{
    if (L->size >= MAX_LIST_SIZE) {
        error("����Ʈ �����÷ο�");
    }
    L->array[L->size++] = item;
    printf("�̵� Ƚ��: 0�� (�������� �߰��ǹǷ� �̵� ����)\n");
}

void insert(ArrayListType* L, int pos, element item)
{
    if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
        int moveCount = L->size - pos; // �̵��ؾ� �� ����� ��
        for (int i = L->size - 1; i >= pos; i--)
            L->array[i + 1] = L->array[i];
        L->array[pos] = item;
        L->size++;
        printf("�̵� Ƚ��: %d��\n", moveCount);
    }
    else if (is_full(L)) {
        error("����Ʈ �����÷ο�");
    }
    else {
        error("�߸��� ��ġ");
    }
}

element delete(ArrayListType* L, int pos)
{
    if (pos < 0 || pos >= L->size)
        error("��ġ ����");
    element item = L->array[pos];
    int moveCount = L->size - pos - 1; // �̵��ؾ� �� ����� ��
    for (int i = pos; i < L->size - 1; i++)
        L->array[i] = L->array[i + 1];
    L->size--;
    printf("�̵� Ƚ��: %d��\n", moveCount);
    return item;
}

int main(void)
{
    ArrayListType list;

    init(&list);
    int choice, item, pos;

    while (1) {
        printf("\n�޴� :\n");
        printf("1. ����Ʈ�� �߰� \n");
        printf("2. ����Ʈ���� ���� \n");
        printf("3. ����Ʈ ���\n");
        printf("0. ���α׷� ���� ");
        printf("���� : ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (is_full(&list)) {
                printf("����Ʈ�� �� á���ϴ�.\n");
            }
            else {
                printf("�߰��� �׸��� ���� �Է��ϼ���: ");
                scanf("%d", &item);
                printf("�߰��� ��ġ�� �Է��ϼ��� (�������� �߰��Ϸ��� %d �Է�): ", list.size);
                scanf("%d", &pos);
                if (pos == list.size) {
                    insert_last(&list, item);
                }
                else {
                    insert(&list, pos, item);
                }
            }
            break;
        case 2:
            if (is_empty(&list)) {
                printf("����Ʈ�� ��� �ֽ��ϴ�.\n");
            }
            else {
                printf("������ �׸��� ��ġ�� �Է��ϼ���: ");
                scanf("%d", &pos);
                delete(&list, pos);
                printf("%d ��ġ�� �׸��� �����߽��ϴ�.\n", pos);
            }
            break;
        case 3:
            print_list(&list);
            break;
        case 0:
            return 0;
        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }
}
