#pragma once
#include "GameNode.h"


struct block
{
    bool is_mine = false;
    bool is_hide = true;
    int around_mines = -1;
};

class MainGame :
    public GameNode
{
public:
    MainGame();
    ~MainGame();

    // GameNode을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;

    void Click();

    bool CheckMap(int row, int col);
    bool CheckMine(int row, int col);



private:
    vector<vector<block>> map;

    int comp = 0;
    int comp_count = 0;

    int map_size_x = 9;
    int map_size_y = 9;
    int mine_count = 10;
};

