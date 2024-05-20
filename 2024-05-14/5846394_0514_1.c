#include <stdio.h>
#include <stdlib.h> // exit 함수를 사용하기 위해 필요

#define MAX_LIST_SIZE 100 // 리스트의 최대크기

typedef int element; // 항목의 정의

typedef struct {
    element array[MAX_LIST_SIZE]; // 배열 정의
    int size; // 현재 리스트에 저장된 항목들의 개수
} ArrayListType;

// 오류 처리 함수
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 리스트 초기화 함수
void init(ArrayListType* L)
{
    L->size = 0;
}
// 리스트가 비어 있으면 1을 반환
// 그렇지 않으면 0을 반환
int is_empty(ArrayListType* L)
{
    return L->size == 0;
}
// 리스트가 가득 차 있으면 1을 반환
// 그렇지 않으면 0을 반환
int is_full(ArrayListType* L)
{
    return L->size == MAX_LIST_SIZE;
}

// 리스트 출력
void print_list(ArrayListType* L)
{
    for (int i = 0; i < L->size; i++)
        printf("%d->", L->array[i]);
    printf("NULL\n");
}

void insert_last(ArrayListType* L, element item)
{
    if (L->size >= MAX_LIST_SIZE) {
        error("리스트 오버플로우");
    }
    L->array[L->size++] = item;
    printf("이동 횟수: 0번 (마지막에 추가되므로 이동 없음)\n");
}

void insert(ArrayListType* L, int pos, element item)
{
    if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
        int moveCount = L->size - pos; // 이동해야 할 요소의 수
        for (int i = L->size - 1; i >= pos; i--)
            L->array[i + 1] = L->array[i];
        L->array[pos] = item;
        L->size++;
        printf("이동 횟수: %d번\n", moveCount);
    }
    else if (is_full(L)) {
        error("리스트 오버플로우");
    }
    else {
        error("잘못된 위치");
    }
}

element delete(ArrayListType* L, int pos)
{
    if (pos < 0 || pos >= L->size)
        error("위치 오류");
    element item = L->array[pos];
    int moveCount = L->size - pos - 1; // 이동해야 할 요소의 수
    for (int i = pos; i < L->size - 1; i++)
        L->array[i] = L->array[i + 1];
    L->size--;
    printf("이동 횟수: %d번\n", moveCount);
    return item;
}

int main(void)
{
    ArrayListType list;

    init(&list);
    int choice, item, pos;

    while (1) {
        printf("\n메뉴 :\n");
        printf("1. 리스트에 추가 \n");
        printf("2. 리스트에서 삭제 \n");
        printf("3. 리스트 출력\n");
        printf("0. 프로그램 종료 ");
        printf("선택 : ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (is_full(&list)) {
                printf("리스트가 꽉 찼습니다.\n");
            }
            else {
                printf("추가할 항목의 값을 입력하세요: ");
                scanf("%d", &item);
                printf("추가할 위치를 입력하세요 (마지막에 추가하려면 %d 입력): ", list.size);
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
                printf("리스트가 비어 있습니다.\n");
            }
            else {
                printf("삭제할 항목의 위치를 입력하세요: ");
                scanf("%d", &pos);
                delete(&list, pos);
                printf("%d 위치의 항목을 삭제했습니다.\n", pos);
            }
            break;
        case 3:
            print_list(&list);
            break;
        case 0:
            return 0;
        default:
            printf("잘못된 선택입니다.\n");
        }
    }
}
