using System.Collections;
using UnityEngine;

public class Bomb : MonoBehaviour
{
    public BoxCollider boxCollider;
    public GameObject explosion;

    private void Awake() => explosion = RefManager.explosionRef;

    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "player")
            boxCollider.isTrigger = false;
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "player")
            StartCoroutine(Explode(3)); //explode bomb in 3 seconds
    }

    //create 3x3 area explosion
    IEnumerator Explode(int secs)
    {
        yield return new WaitForSeconds(secs);

        Vector3 bombPos = transform.position;

        Instantiate(explosion, bombPos + new Vector3(-1, 0, 1), transform.rotation);
        Instantiate(explosion, bombPos + new Vector3(0, 0, 1), transform.rotation);
        Instantiate(explosion, bombPos + new Vector3(1, 0, 1), transform.rotation);

        Instantiate(explosion, bombPos + new Vector3(-1, 0, 0), transform.rotation);
        Instantiate(explosion, bombPos + new Vector3(0, 0, 0), transform.rotation);
        Instantiate(explosion, bombPos + new Vector3(1, 0, 0), transform.rotation);

        Instantiate(explosion, bombPos + new Vector3(-1, 0, -1), transform.rotation);
        Instantiate(explosion, bombPos + new Vector3(0, 0, -1), transform.rotation);
        Instantiate(explosion, bombPos + new Vector3(1, 0, -1), transform.rotation);

        Destroy(gameObject);
    }
}
