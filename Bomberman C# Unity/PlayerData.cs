[System.Serializable]
public class PlayerData
{
    public int highScore;

    public PlayerData(GameManager gameManager) =>  highScore = gameManager.highScore;
}
