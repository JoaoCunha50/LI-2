#include <dungeon.h>

int WallCount(Terreno **map, int r, int col, int row)
{
    int x, y;
    int wall_count = 0;

    for (y = col - r; y <= col + r; y++)
    {
        for (x = row - r; x <= row + r; x++)
        {
            if ((y >= 1) && (y < MAP_HEIGHT - 1) && (x >= 1) && (x < MAP_WIDTH - 1))
            {
                if (map[y][x].ch == '#')
                {
                    wall_count++;
                }
            }
        }
    }
    return wall_count;
}

Terreno **mapborder(Terreno **map)
{
    int x, y;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            if (y == 0 || y == MAP_HEIGHT - 1)
            {
                map[y][x].ch = '#';
                map[y][x].walkable = false;
            }
            if (y == 1 || y == MAP_HEIGHT - 2)
            {
                map[y][x].ch = '#';
                map[y][x].walkable = false;
            }
        }
    }
    for (x = 0; x < MAP_WIDTH; x++)
    {
        for (y = 0; y < MAP_HEIGHT; y++)
        {
            if (x == 0 || x == MAP_WIDTH - 1)
            {
                map[y][x].ch = '#';
                map[y][x].walkable = false;
            }
            if (x == 1 || x == MAP_WIDTH - 2)
            {
                map[y][x].ch = '#';
                map[y][x].walkable = false;
            }
        }
    }
    return map;
}

Terreno **generate_map()
{
    int i, j;
    Terreno **map = calloc(MAP_HEIGHT, sizeof(Terreno *));

    if (map == NULL)
        printf("Error no memory allocated");

    for (i = 0; i < MAP_HEIGHT; i++)
    {
        map[i] = calloc(MAP_WIDTH, sizeof(Terreno));
        if (map[i] == NULL)
            printf("Error no memory allocated");
    }

    for (i = 2; i < MAP_HEIGHT - 2; i++)
    {
        for (j = 2; j < MAP_WIDTH - 2; j++)
        {
            if (rand() % 100 < 45)
            {
                map[i][j].ch = '#';
                map[i][j].walkable = false;
            }
            else
            {
                map[i][j].ch = '.';
                map[i][j].walkable = true;
            }
        }
    }

    mapborder(map);

    int fst = 4, snd = 3;

    for (int k = 0; k < fst; k++)
    {
        for (i = 0; i < MAP_HEIGHT; i++)
        {
            for (j = 0; j < MAP_WIDTH; j++)
            {
                if (WallCount(map, 1, i, j) >= 5 || WallCount(map, 2, i, j) <= 2)
                {
                    map[i][j].ch = '#';
                    map[i][j].walkable = false;
                }
                else
                {
                    map[i][j].ch = '.';
                    map[i][j].walkable = true;
                }
            }
        }
    }

    mapborder(map);

    for (int k = 0; k < snd; k++)
    {

        for (i = 0; i < MAP_HEIGHT; i++)
        {
            for (j = 0; j < MAP_WIDTH; j++)
            {
                if (WallCount(map, 1, i, j) >= 5)
                {
                    map[i][j].ch = '#';
                    map[i][j].walkable = false;
                }
                else
                {
                    map[i][j].ch = '.';
                    map[i][j].walkable = true;
                }
            }
        }
    }

    mapborder(map);

    return map;
}

Posicao setupMap(Terreno **map)
{
    Posicao pos_inicial;
    int x, y;
    do
    {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
        pos_inicial.x = x;
        pos_inicial.y = y;
    } while (map[y][x].walkable == false || (WallCount(map, 3, y, x) != 0));
    return pos_inicial;
}

Posicao setupMapi(Terreno **map)
{
    Posicao pos_inicial_i;
    int x, y;
    do
    {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
        pos_inicial_i.y = y;
        pos_inicial_i.x = x;

    } while (map[y][x].walkable == false || (x == pos_inicial.x && y == pos_inicial.y));
    return pos_inicial_i;
}

Posicao level_entry(Terreno **map)
{
    Posicao pos_lvl;
    int x, y;
    do
    {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
        pos_lvl.y = y;
        pos_lvl.x = x;

    } while (map[y][x].walkable == false || (x == pos_inicial.x && y == pos_inicial.y) || (x == pos_inicial_i.x && y == pos_inicial_i.y));
    return pos_lvl;
}

int next_level(Entidade *player, int input)
{
    if (input == 'e' && ((player->pos.y == pos_lvl.y) && (player->pos.x == pos_lvl.x)))
    {
        trigger = 5;
        return 1;
    }
    else
        return 0;
}

Posicao *plus_damage_obj(Terreno **map)
{

    Posicao *pos_damage = calloc(5, sizeof(Posicao));
    int x, y;

    for (int i = 0; i < 5; i++)
    {

        do
        {
            x = rand() % MAP_WIDTH;
            y = rand() % MAP_HEIGHT;
            pos_damage[i].y = y;
            pos_damage[i].x = x;

        } while (map[y][x].walkable == false || (x == pos_inicial.x && y == pos_inicial.y) || (x == pos_inicial_i.x && y == pos_inicial_i.y) || (x == pos_lvl.x && y == pos_lvl.y));
    }
    return pos_damage;
}

Posicao *traps(Terreno **map)
{

    Posicao *pos_traps = calloc(30, sizeof(Posicao));
    int x, y;

    for (int i = 0; i < 30; i++)
    {

        do
        {
            x = rand() % MAP_WIDTH;
            y = rand() % MAP_HEIGHT;
            pos_traps[i].y = y;
            pos_traps[i].x = x;

        } while (map[y][x].walkable == false || (x == pos_inicial.x && y == pos_inicial.y) || (x == pos_inicial_i.x && y == pos_inicial_i.y) || (x == pos_lvl.x && y == pos_lvl.y) || ((x == (pos_traps->x + 1) && (x == pos_traps->x - 1) && (y == pos_traps->y + 1) && (y == pos_traps->y - 1))));
    }
    return pos_traps;
}

Posicao *fruits(Terreno **map)
{

    Posicao *pos_fruit = calloc(3, sizeof(Posicao));
    int x, y;

    for (int i = 0; i < 3; i++)
    {

        do
        {
            x = rand() % MAP_WIDTH;
            y = rand() % MAP_HEIGHT;
            pos_fruit[i].y = y;
            pos_fruit[i].x = x;

        } while (map[y][x].walkable == false || (x == pos_inicial.x && y == pos_inicial.y) || (x == pos_inicial_i.x && y == pos_inicial_i.y) || (x == pos_lvl.x && y == pos_lvl.y) || ((x == (pos_fruit->x + 20) && (x == pos_fruit->x - 20) && (y == pos_fruit->y + 20) && (y == pos_fruit->y - 20))));
    }
    return pos_fruit;
}

void FreeMapa(Terreno **map)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        free(map[i]);
    }
    free(map);
}