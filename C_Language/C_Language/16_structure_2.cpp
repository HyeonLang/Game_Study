// 16_structure_2.cpp

/*
   ����ü
   - ����ڰ� ���� �ڷ����� ���� ���ο� �ڷ����� �����ϴ� ��
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h> // Sleep

/*
   ����
    struct �̸�
    {
      �ڷ��� �����̸� // ���, ���������� �θ���.
      �ڷ��� �����̸�
      ...

    }
    - �⺻���� ���� ���
    - C������(.c) �̷��� �����ϸ� ����ü�� ���鶧����
    structŰ���带 ����ؾ� ��
    - typedef�� ����Ͽ� �ذ� ����
*/

struct Human
{
    char name[50];
    char gender[50];
    int age;
    float height;
};

//Human h; // .c������ ����
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
Monster m; // ������ �����ϸ� .c������ struct Ű���� ���� ����

typedef struct // ����ü �̸��� ������ �͸� ����ü
{
    char name[50];
    int hp;
    int atk;
    int exp;
    int gold;
}Player;

Player p1;

// ����ü �ʱ�ȭ
Player p2 = { "���ΰ�", 500,100,0,50 };

// .c(C���)������ ������ ����
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

    // . : ��� ���� ������
    h.age;

    Human hu[num];

    for (int i = 0; i < num; i++)
    {
        printf("�̸� �Է� : ");
        scanf_s("%s", &hu[i].name, sizeof(hu[i].name));

        printf("���� �Է� : ");
        scanf_s("%s", &hu[i].gender, sizeof(hu[i].gender));

        printf("���� �Է� : ");
        scanf_s("%d", &hu[i].age);

        printf("Ű �Է� : ");
        scanf_s("%f", &hu[i].height);
    }

    for (int i = 0; i < num; i++)
    {
        printf("%d�� ��� �̸� : %s\n", i + 1, hu[i].name);
        printf("%d�� ��� ���� : %s\n", i + 1, hu[i].gender);
        printf("%d�� ��� ���� : %d\n", i + 1, hu[i].age);
        printf("%d�� ��� Ű : %f\n", i + 1, hu[i].height);
    }

}

void rpg()
{
    Monster monster_table[2] = {
        {"��� ����", 130, 30, 50},
        {"��� �ü�", 90, 50, 50}
    };

    Player p;

    printf("���ӿ� ���Ű� ȯ���մϴ�~~\n\n");
    printf("����� �̸���? : ");
    scanf_s("%s", &p.name, sizeof(p.name));

    p.hp = 300;
    p.atk = 50;
    p.exp = 0;
    p.gold = 0;

    printf("*********************** Ž�� ���� ***********************\n\n");

    srand(time(NULL));
    while (true)
    {
        system("cls");

        if (p.hp <= 0)
        {
            printf("%s ��� ���� ����...\n\n", p.name);
            break;
        }

        printf("���� �������ϴ�.\n\n");
        Sleep(700);

        int event_key = rand() % 5;

        switch (event_key)
        {
        case 0:
            printf("%s�� �������� �߰�! ��� +100\n\n", p.name);
            p.gold += 100;
            Sleep(700);

            printf("������� : %d -> %d\n\n", p.gold - 100, p.gold);
            Sleep(700);

            printf("���������� �̵��մϴ�.\n\n");
            Sleep(700);
            break;

        case 1:
            printf("%s�� ������ �칰 �߰�! HP +100\n\n", p.name);
            Sleep(700);

            printf("HP : %d -> %d\n\n", p.hp, p.hp + 100);
            p.hp += 100;
            Sleep(700);

            printf("���������� �̵��մϴ�.\n\n");
            Sleep(700);
            break;

        case 2:
            printf("%s�� ������ �������ϴ�! HP -70\n\n", p.name);
            Sleep(700);

            printf("HP : %d -> %d\n\n", p.hp, p.hp - 70);
            p.hp -= 70;
            Sleep(700);

            printf("���������� �̵��մϴ�.\n\n");
            Sleep(700);
            break;

        case 3:
        {
            Monster m = monster_table[rand() % 2];

            printf("%s����! ��������!\n\n", m.name);
            Sleep(700);

            while (true)
            {
                printf("%s�� ����\n\n", p.name);
                Sleep(700);

                printf("%s�� ü�� : %d -> %d\n\n", m.name, m.hp, m.hp - p.atk);
                Sleep(700);
                m.hp -= p.atk;

                if (m.hp <= 0)
                {
                    printf("%s �¸�!\n\n", p.name);
                    Sleep(700);

                    printf("exp : %d -> %d\n\n", p.exp, p.exp + m.exp);
                    Sleep(700);

                    printf("���������� �̵��մϴ�.\n\n");
                    Sleep(700);
                    break;
                }

                printf("%s�� ����\n\n", m.name);
                Sleep(700);

                printf("%s�� ü�� : %d -> %d\n\n", p.name, p.hp, p.hp - m.atk);
                Sleep(700);
                p.hp -= m.atk;

                if (p.hp <= 0)
                {
                    printf("%s �й�!\n\n", p.name);
                    Sleep(700);

                    printf("���������� �̵��մϴ�.\n\n");
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
   �ָ� ���� : text rpg ���׷��̵�

    1. ������ �̺�Ʈ�� �ϳ� ����� �߰��ϱ�
    2. ���� �ִ� �̺�Ʈ �ϳ� �����ؼ� ���׷��̵�
    3. ��带 �Ҹ��� �� �ִ� �̺�Ʈ �߰�
    4. �¸� ���� �߰�
    5. ���� �̺�Ʈ ���׷��̵�(������ �߰�, ����, ���, ȸ�� ��� �����Ӱ�)
*/