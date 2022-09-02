using System.Collections;
using UnityEngine;

public class Explosion : MonoBehaviour
{
    public BoxCollider boxCollider;

    private void Awake() => StartCoroutine(DestroyAfter(0.6f));

    IEnumerator DestroyAfter(float secs)
    {
        FindObjectOfType<AudioManager>().Play("explosion");
        yield return new WaitForSeconds(secs);
        GameManager.instance.placedBomb = false;
        Destroy(gameObject);
    }

    private void OnTriggerEnter(Collider other)
    {
        switch (other.tag)
        {
            case "player":
                //kill player
                GameManager.instance.PlayerDeath();
                break;
            case "softBlock":
                //destroy softBlock
                FindObjectOfType<AudioManager>().Play("blockDeath");
                Destroy(other.gameObject);
                GameManager.instance.IncrementScore(100);
                break;
            case "enemy":
                //destroy enemy
                FindObjectOfType<AudioManager>().Play("enemyDeath");
                GameManager.instance.IncrementScore(1500);
                GameManager.instance.enemiesAlive--;

                //to fix a bug when the enemy collides with more than one explosion
                int aux = other.gameObject.GetComponent<EnemyController>().explosionCounter;
                if (aux > 1)
                {
                    GameManager.instance.IncrementScore((-1500 * aux) + 1500);
                    GameManager.instance.enemiesAlive += aux - 1;
                }
                if (GameManager.instance.enemiesAlive == 0)
                    GameManager.instance.LevelWon();

                Destroy(other.gameObject);
                break;
        }
    }
}
