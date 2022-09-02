using UnityEngine;
using Unity.AI.Navigation;

public class NavMeshBaker : MonoBehaviour
{
    [SerializeField]
    NavMeshSurface[] navMeshSurfaces;

    private void Start()
    {
        for (int i = 0; i < navMeshSurfaces.Length; i++)
            navMeshSurfaces[i].BuildNavMesh();
    }
}
