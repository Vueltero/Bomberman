using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    public float moveSpeed = 5;

    public GameObject bomb, Environment;
    
    public Animator animator;
    public RuntimeAnimatorController upIdle, downIdle, leftIdle, rightIdle, up, down, left, right;

    int lastAnim = 2;
    //1 = up; 2 = down; 3 = left; 4 = right;

    private void FixedUpdate()
    {
        if (!GameManager.instance.playerDied)
        {
            float x = Input.GetAxisRaw("Horizontal") * moveSpeed;
            float z = Input.GetAxisRaw("Vertical") * moveSpeed;

            int isDiagonal = x * z != 0 ? 0 : 1;

            if (isDiagonal != 0)
            {
                if (x > 0)
                {
                    animator.runtimeAnimatorController = right;
                    lastAnim = 4;
                }
                else if (x < 0)
                {
                    animator.runtimeAnimatorController = left;
                    lastAnim = 3;
                }
                if (z > 0)
                {
                    animator.runtimeAnimatorController = up;
                    lastAnim = 1;
                }
                else if (z < 0)
                {
                    animator.runtimeAnimatorController = down;
                    lastAnim = 2;
                }
            }

            if (x == 0 && z == 0)
            {
                switch (lastAnim)
                {
                    case 1: animator.runtimeAnimatorController = upIdle; break;
                    case 2: animator.runtimeAnimatorController = downIdle; break;
                    case 3: animator.runtimeAnimatorController = leftIdle; break;
                    case 4: animator.runtimeAnimatorController = rightIdle; break;
                }
            }

            transform.position += new Vector3(x, 0, z) * isDiagonal * moveSpeed * Time.deltaTime;
        }
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space) && !GameManager.instance.placedBomb)
        {
            //place bomb
            FindObjectOfType<AudioManager>().Play("bombSet");
            GameObject bombObj;
            bombObj = Instantiate(bomb, transform.position, transform.rotation);
            bombObj.transform.SetParent(Environment.transform, false);
            GameManager.instance.placedBomb = true;
        }
    }
}
