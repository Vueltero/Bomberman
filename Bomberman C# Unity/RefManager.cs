using UnityEngine;

public class RefManager : MonoBehaviour
{
    static RefManager instance;
    public GameObject player, explosion;

    void Awake() => instance = this;

    public static GameObject playerRef { get { return instance.player; } }
    public static GameObject explosionRef { get { return instance.explosion; } }
}
