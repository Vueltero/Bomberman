using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public float emptyTilesPercentage = 40;
    public float unbreakableTilesPercentage = 20;
    public float breakableTilesPercentage = 40;

    public int score;

    public GameObject wall, softBlock, enemy;
    public GameObject Walls, Enemies;

    void Start()
    {
        LoadSave();
        GenerateLevel();
    }

    private void LoadSave()
    {
        PlayerData data = SaveSystem.LoadPlayer();
        if (data != null)
        {
            score = data.score;
        }
        else
        {
            score = 0;
        }
    }

    public void SavePlayer()
    {
        SaveSystem.SavePlayer(this);
    }

    private void GenerateLevel()
    {
        //initial map state
        string initialLevel = "perrrrrrrrrrrrrebbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrrrrrrrrrrrrrrr";
        //p = player
        //e = empty
        //r = posible breakable
        //b = possible breakable or unbreakable
        //B = unbreakable
        //D = breakable
        //E = enemy

        char[,] map = new char[15,10];
        int mapX = 0, mapY = 0;

        //create map matrix
        foreach (char letter in initialLevel)
        {
            map[mapX, mapY] = letter;
            mapX++;
            if (mapX == 15)
            {
                mapX = 0;
                mapY++;
            }
        }

        //calculate number of tiles
        //float emptyTiles = Mathf.Floor(147 * (emptyTilesPercentage / 100));
        float unbreakableTiles = Mathf.Floor(147 * (unbreakableTilesPercentage / 100));
        float breakableTiles = Mathf.Floor(147 * (breakableTilesPercentage / 100));

        //generate unbreakables positions
        int unbreakableTilesCounter = 0;
        //generate random position
        int rndX = Random.Range(1, 14); //in an int random.range, min is inclusive, and max is exclusive
        int rndY = Random.Range(1, 9);

        while (unbreakableTilesCounter != unbreakableTiles)
        {
            //try to place an unbreakable
            if (map[rndX, rndY] != 'B') //'B' would mean it already has an unbreakable
            {
                int unbreakableCounter = 0;

                //check in a 3x3 area if there are more than 2 unbreakable tiles
                //this is to make all paths of the level reachable (no closed pathways)
                if (unbreakableCounter < 2 && map[rndX - 1, rndY - 1] == 'B')
                    unbreakableCounter++;
                if (unbreakableCounter < 2 && map[rndX, rndY - 1] == 'B')
                    unbreakableCounter++;
                if (unbreakableCounter < 2 && map[rndX + 1, rndY - 1] == 'B')
                    unbreakableCounter++;

                if (unbreakableCounter < 2 && map[rndX - 1, rndY] == 'B')
                    unbreakableCounter++;
                if (unbreakableCounter < 2 && map[rndX, rndY] == 'B')
                    unbreakableCounter++;
                if (unbreakableCounter < 2 && map[rndX + 1, rndY] == 'B')
                    unbreakableCounter++;

                if (unbreakableCounter < 2 && map[rndX - 1, rndY + 1] == 'B')
                    unbreakableCounter++;
                if (unbreakableCounter < 2 && map[rndX, rndY + 1] == 'B')
                    unbreakableCounter++;
                if (unbreakableCounter < 2 && map[rndX - 1, rndY + 1] == 'B')
                    unbreakableCounter++;

                if (unbreakableCounter < 2) //it can place an unbreakable
                {
                    map[rndX, rndY] = 'B';
                    unbreakableTilesCounter++;
                }
            }
            rndX = Random.Range(1, 14);
            rndY = Random.Range(1, 9);
        }

        //generate breakables positions
        int breakableTilesCounter = 0;
        rndX = Random.Range(0, 15);
        rndY = Random.Range(0, 10);

        while (breakableTilesCounter != breakableTiles)
        {
            if (map[rndX, rndY] != 'D')
            {
                //try to place a breakable
                if (map[rndX, rndY] != 'B' && map[rndX, rndY] != 'p' && map[rndX, rndY] != 'e')
                {
                    map[rndX, rndY] = 'D';
                    breakableTilesCounter++;
                }
            }
            rndX = Random.Range(0, 15);
            rndY = Random.Range(0, 10);
        }

        //generate enemies positions
        int enemyCounter = 0;
        rndX = Random.Range(0, 15);
        rndY = Random.Range(0, 10);

        while (enemyCounter != 5)
        {
            if (map[rndX, rndY] != 'E')
            {
                //try to place an enemy
                if (map[rndX, rndY] == 'r' || map[rndX, rndY] == 'b') //if it's on an empty space
                {
                    map[rndX, rndY] = 'E';
                    enemyCounter++;
                }
            }
            rndX = Random.Range(0, 15);
            rndY = Random.Range(0, 10);
        }

        //spawn map & enemies
        GameObject newObject;
        float posX = 0, posZ = 0;

        enemyCounter = 0;

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                char letter = map[j, i];

                switch (letter)
                {
                    case 'B':
                    {
                        newObject = Instantiate(wall, new Vector3(posX, 0, posZ), transform.rotation);
                        newObject.transform.SetParent(Walls.transform, false);
                        newObject.name = "block[" + i + ", " + j + "]";
                        break;
                    }
                    case 'D':
                    {
                        newObject = Instantiate(softBlock, new Vector3(posX, 0, posZ), transform.rotation);
                        newObject.transform.SetParent(Walls.transform, false);
                        newObject.name = "block[" + i + ", " + j + "]";
                        break;
                    }
                    case 'E':
                    {
                        enemyCounter++;
                        newObject = Instantiate(enemy, new Vector3(posX, 0, posZ), transform.rotation);
                        newObject.transform.SetParent(Enemies.transform, false);
                        newObject.name = "enemy-" + enemyCounter;
                        break;
                    }
                }
                posX += 1;
                if (posX >= 15)
                {
                    posX = 0;
                    posZ -= 1;
                }
            }
        }
    }
}
