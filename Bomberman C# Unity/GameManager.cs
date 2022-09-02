using System.Collections;
using UnityEngine;
using TMPro;

//Game made by Agustin Vuelta
//Frolicode - Unity Developer Assignment
//Test - Bomberman Game Prototype
public class GameManager : MonoBehaviour
{
    public float emptyTilesPercentage = 40;
    public float unbreakableTilesPercentage = 20;
    public float breakableTilesPercentage = 40;

    public int score, highScore;

    public GameObject wall, softBlock, enemy, player;
    public GameObject Walls, Enemies;

    public static GameManager instance;

    public TextMeshProUGUI scoreText, highScoreText, stageText;

    public int enemiesAlive = 5;

    public bool placedBomb = false;

    public Animator animator;
    public RuntimeAnimatorController death, idle;

    public GameObject gameOverScreen, levelWonScreen;
    public bool playerDied = false;

    int stage = 1, playSongID = 1;

    void Awake() => instance = this;

    void Start()
    {
        LoadSave();
        GenerateLevel();
        BackgroundMusic.instance.PlaySong(1);
    }

    private void LoadSave()
    {
        PlayerData data = SaveSystem.LoadPlayer();
        if (data != null)
            highScore = data.highScore;
        else
            highScore = 0;

        highScoreText.text = "High Score: " + highScore.ToString();
    }

    public void SavePlayer() =>  SaveSystem.SavePlayer(this);

    private void GenerateLevel()
    {
        //initial map state
        string initialLevel = "peerrrrrrrrrrrrebbbbbbbbbbbbbrebbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrbbbbbbbbbbbbbrrrrrrrrrrrrrrrr";
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

    public void IncrementScore(int number)
    {
        score += number;
        scoreText.text = "Score: " + score.ToString();

        if (score > highScore)
        {
            highScore = score;
            SavePlayer();
            highScoreText.text = "High Score: " + highScore.ToString();
        }
    }

    public void Close()
    {
        Debug.Log("app is closing");
        Application.Quit();
    }

    public void PlayerDeath()
    {
        BackgroundMusic.instance.StopSong();
        playSongID = 1;
        playerDied = true;
        animator.runtimeAnimatorController = death;
        StartCoroutine(PlayerLose(0.6f));
    }

    IEnumerator PlayerLose(float secs)
    {
        yield return new WaitForSeconds(secs);
        FindObjectOfType<AudioManager>().Play("gameOver");
        player.SetActive(false);
        gameOverScreen.SetActive(true); //show game over screen
    }

    public void GenerateNewLevel()
    {
        foreach (Transform child in Walls.transform)
            Destroy(child.gameObject);
        foreach (Transform child in Enemies.transform)
            Destroy(child.gameObject);

        player.transform.position = new Vector3(-7.53f, 0.6f, 4.94f); //reset player position
        animator.runtimeAnimatorController = idle;
        player.SetActive(true);

        GenerateLevel();
        BackgroundMusic.instance.PlaySong(playSongID);

        gameOverScreen.SetActive(false);

        if (playerDied)
        {
            FindObjectOfType<AudioManager>().StopPlaying("gameOver");
            playerDied = false;
            score = 0;
            scoreText.text = "Score: 0";
        }
        enemiesAlive = 5;
    }

    public void LevelWon()
    {
        BackgroundMusic.instance.StopSong();
        FindObjectOfType<AudioManager>().Play("levelWin");
        levelWonScreen.SetActive(true);
        stage++;
        stageText.text = "STAGE " + stage + "\nGAME START";

        StartCoroutine(NewLevel(2f));
    }

    IEnumerator NewLevel(float secs)
    {
        yield return new WaitForSeconds(secs);
        GenerateNewLevel();
        levelWonScreen.SetActive(false);

        playSongID++;
        if (playSongID > 3) playSongID = 1;
        BackgroundMusic.instance.PlaySong(playSongID);
    }
}
