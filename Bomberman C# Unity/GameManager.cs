using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public float emptyTilesPercentage = 40;
    public float unbreakableTilesPercentage = 20;
    public float breakableTilesPercentage = 40;

    void Start()
    {
        
    }

    void Update()
    {
        
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
        float emptyTiles = Mathf.Floor(147 * (emptyTilesPercentage / 100));
        float unbreakableTiles = Mathf.Floor(147 * (unbreakableTilesPercentage / 100));
        float breakableTiles = Mathf.Floor(147 * (breakableTilesPercentage / 100));

        //generate random position
        int rndX = Random.Range(1, 13);
        int rndY = Random.Range(1, 8);

        int unbreakableTilesCounter = 0;

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
                rndX = Random.Range(1, 13);
                rndY = Random.Range(1, 8);
            }
        }

        int breakableTilesCounter = 0;

        rndX = Random.Range(0, 14);
        rndY = Random.Range(0, 9);

        while (breakableTilesCounter != breakableTiles)
        {
            //try to place a breakable
            if (map[rndX, rndY] != 'B' && map[rndX, rndY] != 'p' && map[rndX, rndY] != 'e')
            {
                map[rndX, rndY] = 'D';
                breakableTilesCounter++;
            }
            rndX = Random.Range(0, 14);
            rndY = Random.Range(0, 9);
        }

        //spawn map


        //spawn enemies
        rndX = Random.Range(0, 14);
        rndY = Random.Range(0, 9);

        if (map[rndX, rndY] == 'r' || map[rndX, rndY] == 'b') //if it is empty
        {
            //spawn enemy there
        }
    }
}
