// 16_structure_2.cpp

/*
   구조체
   - 사용자가 여러 자료형을 묶어 새로운 자료형을 정의하는 것
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h> // Sleep

/*
   선언
    struct 이름
    {
      자료형 변수이름 // 멤버, 멤버변수라고 부른다.
      자료형 변수이름
      ...

    }
    - 기본적인 선언 방식
    - C에서는(.c) 이렇게 선언하면 구조체를 만들때마다
    struct키워드를 사용해야 함
    - typedef를 사용하여 해결 가능
*/

struct Human
{
    char name[50];
    char gender[50];
    int age;
    float height;
};

//Human h; // .c에서는 에러
struct Human h;

typedef int my_int;
my_int mi;

typedef unsigned int uint;

typedef float HP;

//HP hp;
//HP hp2;
//
//void SetHP(HP h);
//HP GetHP();

typedef struct _Monster
{
    char name[50];
    int hp;
    int atk;
    int exp;
}Monster;

struct _Monster a;
Monster m; // 별명을 지정하면 .c에서도 struct 키워드 생략 가능

typedef struct // 구조체 이름을 생략한 익명 구조체
{
    char name[50];
    int hp;
    int atk;
    int exp;
    int gold;
}Player;

Player p1;

// 구조체 초기화
Player p2 = { "주인공", 500,100,0,50 };

// .c(C언어)에서만 가능한 문법
//Player p3 = { .gold = 10 };

void input_human();
void rpg();

int main()
{
    //input_human();
    rpg();

    return 0;
}

void input_human()
{
    //struct Human
    //{
    //   char name[50];
    //   char gender[50];
    //   int age;
    //   float height;
    //};

    const int num = 2;

    Human h;

    // . : 멤버 접근 연산자
    h.age;

    Human hu[num];

    for (int i = 0; i < num; i++)
    {
        printf("이름 입력 : ");
        scanf_s("%s", &hu[i].name, sizeof(hu[i].name));

        printf("성별 입력 : ");
        scanf_s("%s", &hu[i].gender, sizeof(hu[i].gender));

        printf("나이 입력 : ");
        scanf_s("%d", &hu[i].age);

        printf("키 입력 : ");
        scanf_s("%f", &hu[i].height);
    }

    for (int i = 0; i < num; i++)
    {
        printf("%d번 사람 이름 : %s\n", i + 1, hu[i].name);
        printf("%d번 사람 성별 : %s\n", i + 1, hu[i].gender);
        printf("%d번 사람 나이 : %d\n", i + 1, hu[i].age);
        printf("%d번 사람 키 : %f\n", i + 1, hu[i].height);
    }

}

void rpg()
{
    Monster monster_table[2] = {
        {"고블린 전사", 130, 30, 50},
        {"고블린 궁수", 90, 50, 50}
    };

    Player p;

    printf("게임에 오신걸 환영합니다~~\n\n");
    printf("당신의 이름은? : ");
    scanf_s("%s", &p.name, sizeof(p.name));

    p.hp = 300;
    p.atk = 50;
    p.exp = 0;
    p.gold = 0;

    printf("*********************** 탐험 시작 ***********************\n\n");

    srand(time(NULL));
    while (true)
    {
        system("cls");

        if (p.hp <= 0)
        {
            printf("%s 사망 게임 종료...\n\n", p.name);
            break;
        }

        printf("한층 내려갑니다.\n\n");
        Sleep(700);

        int event_key = rand() % 5;

        switch (event_key)
        {
        case 0:
            printf("%s가 보물상자 발견! 골드 +100\n\n", p.name);
            p.gold += 100;
            Sleep(700);

            printf("소지골드 : %d -> %d\n\n", p.gold - 100, p.gold);
            Sleep(700);

            printf("다음층으로 이동합니다.\n\n");
            Sleep(700);
            break;

        case 1:
            printf("%s가 생명의 우물 발견! HP +100\n\n", p.name);
            Sleep(700);

            printf("HP : %d -> %d\n\n", p.hp, p.hp + 100);
            p.hp += 100;
            Sleep(700);

            printf("다음층으로 이동합니다.\n\n");
            Sleep(700);
            break;

        case 2:
            printf("%s가 함정에 빠졌습니다! HP -70\n\n", p.name);
            Sleep(700);

            printf("HP : %d -> %d\n\n", p.hp, p.hp - 70);
            p.hp -= 70;
            Sleep(700);

            printf("다음층으로 이동합니다.\n\n");
            Sleep(700);
            break;

        case 3:
        {
            Monster m = monster_table[rand() % 2];

            printf("%s조우! 전투시작!\n\n", m.name);
            Sleep(700);

            while (true)
            {
                printf("%s의 공격\n\n", p.name);
                Sleep(700);

                printf("%s의 체력 : %d -> %d\n\n", m.name, m.hp, m.hp - p.atk);
                Sleep(700);
                m.hp -= p.atk;

                if (m.hp <= 0)
                {
                    printf("%s 승리!\n\n", p.name);
                    Sleep(700);

                    printf("exp : %d -> %d\n\n", p.exp, p.exp + m.exp);
                    Sleep(700);

                    printf("다음층으로 이동합니다.\n\n");
                    Sleep(700);
                    break;
                }

                printf("%s의 공격\n\n", m.name);
                Sleep(700);

                printf("%s의 체력 : %d -> %d\n\n", p.name, p.hp, p.hp - m.atk);
                Sleep(700);
                p.hp -= m.atk;

                if (p.hp <= 0)
                {
                    printf("%s 패배!\n\n", p.name);
                    Sleep(700);

                    printf("다음층으로 이동합니다.\n\n");
                    Sleep(700);
                    break;
                }
            }
        }
        break;

        case 4:
            break;
        }
    }

}

/*
   주말 과제 : text rpg 업그레이드

    1. 본인이 이벤트를 하나 만들어 추가하기
    2. 원래 있던 이벤트 하나 선택해서 업그레이드
    3. 골드를 소모할 수 있는 이벤트 추가
    4. 승리 조건 추가
    5. 전투 이벤트 업그레이드(선택지 추가, 공격, 방어, 회복 등등 자유롭게)
*/