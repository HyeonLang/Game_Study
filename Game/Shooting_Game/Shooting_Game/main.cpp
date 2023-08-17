#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
#include <ctime>

#define ROW 30
#define COL 20
#define LIFE 5

#define UPGRAGE_BULLIT_COUNT 9
#define UPGRAGE_BULLIT_PROBABILITY 10

#define STRAT_BOSS_SCORE 50
#define ENEMY_COUNT_CYCLE 3
#define BOSS_LIFE 50

#define CLEAR_SCORE 100

enum obj { blank, wall, player, enemy, bullet, item, boss };
enum key { shot = 32, up = 72, right = 77, left = 75, down = 80 };

struct pos {
    int x;
    int y;
};
struct player {
    int score;
    int life;
    int bullit_count;
    struct pos pos;
};
struct boss {
    int life;
    struct pos pos;
};

//추가
void init_system();
void init_player(struct player* p);
void init_boss(struct boss* b);

bool play_game(obj* map, struct player* p, struct boss* b);
void end_game(int is_boss_clear, const struct player* p);

void eccept_key(obj* map, struct player* p);
void move_bullit(obj* map, struct player* p, struct boss* b);
void move_enemy(obj* map, struct player* p);
int init_boss(obj* map, const struct boss* b);
bool check_end(bool& is_boss_clear, struct player* p, struct boss* b);
void creat_enemy(int& enemy_count, int& is_boss, obj* map);
//추가 완료

void make_map(obj* map, const struct player* p);
void show_map(const obj* map);
void show_score(const struct player* p);
void show_obj(obj obj);
void swap_map_obj_AtoB(obj* map, pos* A, pos* B);

void gotoxy(int x, int y); // 커서 이동
void cursor(int n); // 커서 숨김

int main()
{
    init_system();

    obj map[ROW * COL] = { blank };
    struct player p;
    struct boss b;
    
    init_player(&p);
    init_boss(&b);
    make_map(map, &p);
    show_map(map);
    show_score(&p);

    srand(static_cast<unsigned int>(time(NULL)));

    bool is_boss_clear = play_game(map, &p, &b);
    end_game(is_boss_clear, &p);

    system("pause");
    return 0;
}

void init_system() {
    system("mode con cols=40 lines=35"); // 콘솔 크기 조절
    cursor(0); // 커서 숨김

    system("pause"); // 대기
    gotoxy(0, 0);
}

void init_player(struct player* p) {
     
    p->score = 0;
    p->life = LIFE;
    p->bullit_count = 0;
        
    p->pos.x = COL / 2;
    p->pos.y = ROW - 4;
    
}

void init_boss(struct boss* b) {
    
    b->life = BOSS_LIFE;
        
    b->pos.x = COL / 2;
    b->pos.y = 2;
    
}

bool play_game(obj* map, struct player* p, struct boss* b) {
    bool is_boss_clear = false;
    int is_boss = 0;
    int enemy_count = 0;
    srand(static_cast<unsigned int>(time(NULL)));

    while (true)
    {
        eccept_key(map, p);
        move_bullit(map, p, b);
        move_enemy(map, p);

        if (p->score > STRAT_BOSS_SCORE) {
            is_boss = init_boss(map, b);
        }

        if (check_end(is_boss_clear, p, b)) {
            break;
        }
        
        creat_enemy(enemy_count, is_boss, map);
    }

    return is_boss_clear;
}

void end_game(int is_boss_clear, const struct player* p) {
    if (is_boss_clear) {
        std::cout << std::endl << "!!게임을 클리어 하셨습니다!!" << std::endl;
        std::cout << "SCORE : " << p->score << std::endl;
    }
    else {
        std::cout << std::endl << "게임 클리어 실패..." << std::endl;
        std::cout << "SCORE : " << p->score << std::endl;
    }
}

void eccept_key(obj* map, struct player* p) {
    // 키 입력 대기
    clock_t start = clock();
    while (true)
    {
        if (_kbhit()) // 키가 눌리면 실행
        {
            enum key key = static_cast<enum key>(_getch());

            if (key == 224)
                key = static_cast<enum key>(_getch());

            pos move_pos = {
                move_pos.x = p->pos.x,
                move_pos.y = p->pos.y
            };

            if (key == right)
            {
                move_pos.x++;
            }
            else if (key == left)
            {
                move_pos.x--;
            }
            else if (key == up)
            {
                move_pos.y--;
            }
            else if (key == down)
            {
                move_pos.y++;
            }
            else if (key == shot)
            {
                // 총알이 장전 시 upgrade 총알을 발사
                if (p->bullit_count == 0) {
                    map[p->pos.x + (p->pos.y - 1) * COL] = bullet;
                    gotoxy(p->pos.x * 2, p->pos.y - 1);
                    show_obj(bullet);
                }
                else {
                    map[p->pos.x + (p->pos.y - 1) * COL] = bullet;
                    gotoxy(p->pos.x * 2, p->pos.y - 1);
                    show_obj(bullet);

                    if (map[p->pos.x + 1 + (p->pos.y - 1) * COL] != wall) {
                        map[p->pos.x + 1 + (p->pos.y - 1) * COL] = bullet;
                        gotoxy((p->pos.x + 1) * 2, p->pos.y - 1);
                        show_obj(bullet);
                    }

                    if (map[p->pos.x - 1 + (p->pos.y - 1) * COL] != wall) {
                        map[p->pos.x - 1 + (p->pos.y - 1) * COL] = bullet;
                        gotoxy((p->pos.x - 1) * 2, p->pos.y - 1);
                        show_obj(bullet);
                    }
                    p->bullit_count--;
                    show_score(p);
                }

            }

            obj move_obj = map[move_pos.x + move_pos.y * COL];

            if (move_obj == wall)
            {
                // 아무 동작도 수행하지 않음
            }
            else if (move_obj == blank)
            {
                swap_map_obj_AtoB(map, &p->pos, &move_pos);
                p->pos.x = move_pos.x;
                p->pos.y = move_pos.y;
            }
        }
        if ((static_cast<float>(clock() - start) / CLOCKS_PER_SEC) > 0.1f) // 0.1초 후 종료
            break;
    }
}

void move_bullit(obj* map, struct player* p, struct boss* b) {
    // 총알을 위로 이동
    for (int y = 0; y < ROW; y++)
    {
        for (int x = 0; x < COL; x++)
        {
            if (map[x + y * COL] == bullet && y > 0)
            {
                pos my_pos = {
                    my_pos.x = x,
                    my_pos.y = y
                };

                pos move_pos = {
                    move_pos.x = my_pos.x,
                    move_pos.y = my_pos.y - 1
                };

                obj move_obj = map[move_pos.x + move_pos.y * COL];

                if (move_obj == wall)
                {
                    map[my_pos.x + my_pos.y * COL] = blank;
                    gotoxy(my_pos.x * 2, my_pos.y);
                    std::cout << "  ";
                }
                else if (move_obj == blank || move_obj == item)
                {
                    swap_map_obj_AtoB(map, &my_pos, &move_pos);
                }
                else if (move_obj == enemy)
                {
                    int upgrage_pro = UPGRAGE_BULLIT_PROBABILITY;
                    if (rand() % upgrage_pro == 0) { // UPGRAGE_BULLIT_PROBABILITY 확률로 아이템 드랍
                        map[my_pos.x + my_pos.y * COL] = item;
                        gotoxy(my_pos.x * 2, my_pos.y);
                        std::cout << "++";

                        map[move_pos.x + move_pos.y * COL] = blank;
                        gotoxy(move_pos.x * 2, move_pos.y);
                        std::cout << "  ";

                        p->score++;
                        show_score(p);
                    }
                    else {
                        map[my_pos.x + my_pos.y * COL] = blank;
                        gotoxy(my_pos.x * 2, my_pos.y);
                        std::cout << "  ";
                        map[move_pos.x + move_pos.y * COL] = blank;
                        gotoxy(move_pos.x * 2, move_pos.y);
                        std::cout << "  ";
                        p->score++;
                        show_score(p);
                    }
                }
                else if (move_obj == boss)
                {
                    map[my_pos.x + my_pos.y * COL] = blank;
                    gotoxy(my_pos.x * 2, my_pos.y);
                    std::cout << "  ";
                    b->life--;
                }
            }
        }
    }
}

void move_enemy(obj* map, struct player* p) {
    // 적을 아래로 이동 - 벽 / 빈 공간 / 플레이어와의 충돌만 처리
        for (int y = ROW - 1; y >= 0; y--)
        {
            for (int x = COL - 1; x >= 0; x--)
            {
                if (map[x + y * COL] == boss)
                {
                    gotoxy(x * 2, y);
                    show_obj(boss);
                }
                if (map[x + y * COL] == item)
                {

                    pos my_pos = {
                        my_pos.x = x,
                        my_pos.y = y
                    };

                    pos move_pos = {
                        move_pos.x = my_pos.x,
                        move_pos.y = my_pos.y + 1
                    };


                    if (move_pos.y < ROW) // 배열 인덱스 계산 오류 방지를 위한 if 문 추가
                    {
                        obj move_obj = map[move_pos.x + move_pos.y * COL];

                        if (move_obj == wall)
                        {
                            map[my_pos.x + my_pos.y * COL] = blank;
                            gotoxy(my_pos.x * 2, my_pos.y);
                            std::cout << "  ";
                        }
                        else if (move_obj == blank || move_obj == item)
                        {
                            swap_map_obj_AtoB(map, &my_pos, &move_pos);
                        }
                        else if (move_obj == player)
                        {
                            map[my_pos.x + my_pos.y * COL] = blank;
                            gotoxy(my_pos.x * 2, my_pos.y);
                            std::cout << "  ";

                            p->bullit_count = UPGRAGE_BULLIT_COUNT;
                            show_score(p);
                        }
                    }
                }
                if (map[x + y * COL] == enemy)
                {
                    pos my_pos = {
                        my_pos.x = x,
                        my_pos.y = y
                    };

                    pos move_pos = {
                        move_pos.x = my_pos.x,
                        move_pos.y = my_pos.y + 1
                    };

                    if (move_pos.y < ROW) // 배열 인덱스 계산 오류 방지를 위한 if 문 추가
                    {
                        obj move_obj = map[move_pos.x + move_pos.y * COL];

                        if (move_obj == wall)
                        {
                            map[my_pos.x + my_pos.y * COL] = blank;
                            gotoxy(my_pos.x * 2, my_pos.y);
                            std::cout << "  ";
                        }
                        else if (move_obj == blank || move_obj == item)
                        {
                            swap_map_obj_AtoB(map, &my_pos, &move_pos);
                        }
                        else if (move_obj == player)
                        {
                            map[my_pos.x + my_pos.y * COL] = blank;
                            gotoxy(my_pos.x * 2, my_pos.y);
                            std::cout << "  ";

                            p->life--;
                            show_score(p);
                        }
                    }
                }
            }
        }
}

bool check_end(bool& is_boss_clear,struct player* p, struct boss* b) {
    if (p->life == 0) // 플레이어가 생명을 모두 잃었는지 확인
    {
        gotoxy(0, ROW + 2); // 커서를 아래로 이동
        return true; // 루프 종료
    }
    if (b->life < 0) {
        p->score += CLEAR_SCORE;
        is_boss_clear = true;
        show_score(p);
        gotoxy(0, ROW + 2); // 커서를 아래로 이동
        return true; // 루프 종료
    }
    return false;
}

int init_boss(obj* map, const struct boss* b) {
    map[b->pos.x + (b->pos.y) * COL] = boss;
    map[b->pos.x + 1 + (b->pos.y) * COL] = boss;
    map[b->pos.x + 2 + (b->pos.y) * COL] = boss;
    map[b->pos.x + -1 + (b->pos.y) * COL] = boss;
    map[b->pos.x + (b->pos.y + 1) * COL] = boss;
    map[b->pos.x + 1 + (b->pos.y + 1) * COL] = boss;
    map[b->pos.x + 2 + (b->pos.y + 1) * COL] = boss;
    map[b->pos.x + -1 + (b->pos.y + 1) * COL] = boss;
    return 1;
}

void creat_enemy(int& enemy_count, int& is_boss, obj* map) {
    // 적 생성 - 0.1 * 3초마다 생성 (0.3초)
    // 보스 모드시 0.1 * 2초마다 생성 (0.2초)
    if (enemy_count == ENEMY_COUNT_CYCLE)
    {
        pos put_pos;
        if (is_boss) {
            enemy_count = 1;
            put_pos = {
                put_pos.x = rand() % (COL - 2) + 1,
                put_pos.y = 4
            };
        }
        else {
            enemy_count = 0;
            put_pos = {
                put_pos.x = rand() % (COL - 2) + 1,
                put_pos.y = 1
            };
        }

        if (map[put_pos.x + put_pos.y * COL] == blank) // 공간이 빈 곳에 적 생성
        {
            map[put_pos.x + put_pos.y * COL] = enemy;
            gotoxy(put_pos.x * 2, put_pos.y);
            show_obj(enemy);
        }
    }
    else
    {
        enemy_count++;
    }
}

void make_map(obj* map, const struct player* p)
{
    for (int y = 0; y < ROW; y++)
    {
        for (int x = 0; x < COL; x++)
        {
            if (y == 0 || x == 0 || y == ROW - 1 || x == COL - 1)
            {
                map[x + y * COL] = wall;
            }
        }
    }

    map[p->pos.x + p->pos.y * COL] = player;
}

void show_map(const obj* map)
{
    for (int y = 0; y < ROW; y++)
    {
        for (int x = 0; x < COL; x++)
        {
            show_obj(map[x + y * COL]);
        }
        std::cout << std::endl;
    }
}

void show_score(const struct player* p)
{
    gotoxy(0, ROW);
    std::cout << "SCORE : " << p->score << "      ";
    std::cout << "LIFE : ";
    for (int life = 0; life < LIFE; life++)
    {
        if (life < p->life)
        {
            std::cout << "▲";
        }
        else
        {
            std::cout << "  ";
        }
    }
    std::cout << std::endl << "UP_BULLIT : " << p->bullit_count;
}

void show_obj(obj obj)
{
    if (obj == blank)
    {
        std::cout << "  ";
    }
    else if (obj == wall)
    {
        std::cout << "※";
    }
    else if (obj == player)
    {
        std::cout << "▲";
    }
    else if (obj == bullet)
    {
        std::cout << "＊";
    }
    else if (obj == enemy)
    {
        std::cout << "▼";
    }
    else if (obj == item)
    {
        std::cout << "++";
    }
    else if (obj == boss)
    {
        std::cout << "▼";
    }
}

void swap_map_obj_AtoB(obj* map, pos* A, pos* B)
{
    obj temp = map[B->x + B->y * COL];
    map[B->x + B->y * COL] = map[A->x + A->y * COL];
    map[A->x + A->y * COL] = temp;

    gotoxy(A->x * 2, A->y);
    show_obj(map[A->x + A->y * COL]);
    gotoxy(B->x * 2, B->y);
    show_obj(map[B->x + B->y * COL]);
}

void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursor(int n)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = n;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
