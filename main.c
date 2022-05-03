#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20
#define TRUE 1
#define FALSE 0

void equivalence(int m, int n);

typedef struct node* node_pointer;
typedef struct node{
    int data;
    node_pointer link;
};

int main(void)
{
    int m, n;

    printf("동치쌍의 수를 입력하세요: ");
    scanf("%d", &m);
    printf("변수의 수를 입력하세요(<=%d): ", MAX_SIZE);
    scanf("%d", &n);

    equivalence(m, n);
}

void equivalence(int m, int n)
{
    int BIT[MAX_SIZE]; //이미 출력된 객체 표시
    node_pointer SEQ[MAX_SIZE]; //헤더 노드 저장
    node_pointer av, ptr, t, top;
    int index;
    int i, j;

    for (int i = 0; i < n+1; i++)
    {
        //SEQ와 BIT 초기화
        BIT[i] = TRUE;
        SEQ[i] = NULL;
    }

    //1단계: 모든 입력을 처리
    for (int k = 0; k < m; k++)
    {
        printf("동치쌍을 입력하세요: ");
        scanf("%d %d", &i, &j);

        av = malloc(sizeof(node_pointer));
        av->data = j;
        av->link = SEQ[i]; //j를 리스트 i에 첨가
        SEQ[i] = av;

        av = malloc(sizeof(node_pointer));
        av->data = i;
        av->link = SEQ[j]; //i를 리스트 j에 첨가
        SEQ[j] = av;
    }

    //2단계: 모든 부류를 출력
    for (index = 1; index < n+1; index++)
    {
        if (BIT[index]) {
            printf("\nA new class: %5d", index);
            BIT[index] = FALSE; //출력시키는 부류를 표시
            ptr = SEQ[index];
            top = NULL; //스택 초기화
            for (;;) { //부류전체를 탐색
                while (ptr) { //리스트의 처리
                    j = ptr->data;
                    if (BIT[j]) {
                        printf("%5d", j);
                        BIT[j] = FALSE;
                        t = ptr->link; //스택에 push
                        ptr->link = top;
                        top = ptr;
                        ptr = t;
                    }
                    else
                        ptr = ptr->link;
                } //end of while(ptr)
                if (!top) //공백 스택
                    break;
                ptr = SEQ[top->data];
                top = top->link; //스택에서 제거
            } //end of for(;;)
        }//end of if (BIT[index])
    } //end of for (index = 0; index <n; index++)
}