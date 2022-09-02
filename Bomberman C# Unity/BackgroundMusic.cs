using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackgroundMusic : MonoBehaviour
{
    public AudioClip song1, song2, song3;
    public static BackgroundMusic instance;

    void Awake() => instance = this;

    public void PlaySong(int songID)
    {
        switch (songID)
        {
            case 1:
                GetComponent<AudioSource>().Stop();
                GetComponent<AudioSource>().clip = song1;
                GetComponent<AudioSource>().Play();
                break;
            case 2:
                GetComponent<AudioSource>().Stop();
                GetComponent<AudioSource>().clip = song2;
                GetComponent<AudioSource>().Play();
                break;
            case 3:
                GetComponent<AudioSource>().Stop();
                GetComponent<AudioSource>().clip = song3;
                GetComponent<AudioSource>().Play();
                break;
        }
    }

    public void StopSong() => GetComponent<AudioSource>().Stop();
}
