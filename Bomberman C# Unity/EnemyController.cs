using System.Collections;
using UnityEngine;
using UnityEngine.AI;

public class EnemyController : MonoBehaviour
{
    public NavMeshAgent agent;
    public GameObject player;
    public float enemyDistanceRun = 16f;
    public int explosionCounter = 0;

    int moveX = 0, moveZ = 0;
    Vector3 rndPos = new Vector3(0f, 0f, 0f);
    bool escapeFromPlayer = false;

    private void Awake()
    {
        player = RefManager.playerRef;
        StartCoroutine(MoveRandom(0.5f));
    }

    IEnumerator MoveRandom(float secs)
    {
        yield return new WaitForSeconds(secs);

        moveX = Random.Range(-15, 16);
        moveZ = Random.Range(-10, 11);

        rndPos = new Vector3(moveX, 0f, moveZ);
        agent.SetDestination(rndPos);

        if (GameManager.instance.enemiesAlive > 2)
            StartCoroutine(MoveRandom(1f));
        else
            escapeFromPlayer = true;
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("explosion"))
            explosionCounter++;
        if (other.tag == "player")
            GameManager.instance.PlayerDeath();
    }

    void Update()
    {
        if (escapeFromPlayer)
        {
            float distance = Vector3.Distance(transform.position, player.transform.position);

            if (distance < enemyDistanceRun)
            {
                Vector3 dirToPlayer = transform.position - player.transform.position;
                Vector3 newPos = transform.position + dirToPlayer;

                agent.SetDestination(newPos);
            }
        }
    }
}
