# Assignment 2: C-Unplugged

<pre>
This is my first-ever project.
Instructions to run the program:

1) Executable is named: music.
2) Library -> Master list of all songs known till date and present in music player. (Can't be modified)
3) Album -> Each album will have multiple songs, and multiple albums are allowed based on taste of the user.
4) Playlist -> This will be a temporary data (or Queue).
5) At all the places (Library, Album, Playlist) the constraints are:<br>
    a. Song name with length constraint of 150 characters.<br>
    b. Artist (only 1) with length constraint of 150 characters<br>
    c. Duration of song will be in seconds.<br>
6) Commands:<br>
    I. Album Commands:-<br>
        <b>a. To CREATE new album =</b> CREATE album albumsalbum_name<br>
        <b>b. To APPEND song to any album (existing) =</b> APPEND song song_name-album album_name<br>
        <b>c. To DELETE song from an album =</b> DELETE song song_name-album album_name<br>
        <b>d. To DELETE a specific album =</b> DELETE album album_name<br>

    II. Playlist Commands:-<br> 
        <b>a. To APPEND song to playlist =</b> APPEND song song_name-playlist<br>
        <b>b. To APPEND specific album to playlist =</b> APPEND album album_name-playlist<br>

    III. View / List Commands:-<br>
        <b>a. To DISPLAY all songs in a Library =</b> DISPLAY library<br>
        <b>b. To DISPLAY List of all Albums =</b> DISPLAY albums<br>
        <b>c. To DISPLAY all songs in an Album =</b> DISPLAY album album_name<br>
        <b>d. To DISPLAY Playlist =</b> DISPLAY playlist<br>
        <b>e. To DISPLAY History =</b> DISPLAY history<br>

    IV.  PLAY / PAUSE / NEXT / PREVIOUS:-<br>
        <b>a. To PLAY specific song =</b> PLAY song song_name<br>
        <b>b. To PLAY specific Album from start=</b> PLAY album album_name<br>
        <b>c. To PLAY the playlist from start =</b> PLAY playlist<br>
        <b>d. To PLAY entire library from start =</b> PLAY library<br>
        <b>e. To go to NEXT song =</b> NEXT<br>
        <b>f. To go to PREVIOUS song =</b> PREVIOUS<br>
        <b>g. To go to REPLAY same song in playlist =</b> REPLAY<br>
        
    V. MISCELLANEOUS:-<br>
        <b>a. To EXIT playlist =</b> EXIT<br>
        <b>b. To QUIT program =</b> QUIT<br>
</pre>