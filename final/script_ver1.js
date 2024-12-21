const playlistSongs = document.getElementById("playlist-songs");
const playButton = document.getElementById("play");
const pauseButton = document.getElementById("pause");
const nextButton = document.getElementById("next");
const previousButton = document.getElementById("previous");
const shuffleButton = document.getElementById("shuffle");

const allSongs = [{
        id: 0,
        title: "Intro",
        artist: "Zhou Shen",
        duration: "0:53",
        src: "https://open.spotify.com/track/0V97BmOeUZ5h4Fq5Kktgjp?si=fc4131078898438d",
    },
    {
        id: 1,
        title: "Mirage",
        artist: "Zhou Shen",
        duration: "3:46",
        src: "https://open.spotify.com/track/1PR9aOkY0dyRRL81YXv9a4?si=296b6ab479f0424c",
    },
    {
        id: 2,
        title: "Restart",
        artist: "Zhou Shen",
        duration: "4:07",
        src: "https://open.spotify.com/track/2oqxzDXVxzYQBzD6C925kp?si=04d286e022634d4f",
    },
    {
        id: 3,
        title: "The Memory Store",
        artist: "Zhou Shen",
        duration: "3:04",
        src: "https://open.spotify.com/track/5ErelV4OwVFqUY977ynUTz?si=a60b97fbedc842e6",
    },
    {
        id: 4,
        title: "The Giver",
        artist: "Zhou Shen",
        duration: "3:43",
        src: "https://open.spotify.com/track/7x7QkNCR5iW3P9FJZ3D9Pq?si=96f3bc605db94855",
    },
    {
        id: 5,
        title: "Shao Guan Wo (Watch Ur Manners)",
        artist: "Zhou Shen",
        duration: "3:59",
        src: "https://open.spotify.com/track/5a4SBwm8Q4Wjlr0Mckt8eP?si=38f875acc76b4024",
    },
    {
        id: 6,
        title: "Say Hi",
        artist: "Zhou Shen",
        duration: "4:00",
        src: "https://open.spotify.com/track/3XeJaSwhAx04xGKRhjhkt3?si=d278c37e33974907",
    },
    {
        id: 7,
        title: "Fix You",
        artist: "Zhou Shen",
        duration: "5:03",
        src: "https://open.spotify.com/track/4Q1bQNnbXm1dhG0ZarfMED?si=3ac20461f8974964",
    },
    {
        id: 8,
        title: "Wala li longla,
        artist: "Zhou Shen",
        duration: "3:10",
        src: "https://open.spotify.com/track/3imYB01GqqIpjdK0FQpVmQ?si=39c6cb1fb8344c6b",
    },
    {
        id: 9,
        title: "Shen",
        artist: "Zhou Shen",
        duration: "4:33",
        src: "https://open.spotify.com/track/7JkOiIkfGsPVLvxDyJZRnJ?si=24fb9e2c30a54b83",
    },
    {
        id: 10,
        title: "Life is Like a Box of Chocolates",
        artist: "Zhou Shen",
        duration: "3:37",
        src: "https://open.spotify.com/track/1WfaoEdzjV4Gj8rxkSi5eh?si=a40bea6b389b45e3",
    },
];

const audio = new Audio();
let userData = {
    songs: [...allSongs],
    currentSong: null,
    songCurrentTime: 0,
};

const playSong = (id) => {
    const song = userData?.songs.find((song) => song.id === id);
    if (!song) {
        console.error("Song not found:", id);
        return;
    }

    // Container for the player
    const playerContainer = document.getElementById("audio-player");
    playerContainer.innerHTML = ""; // Clear existing content

    // Handle Spotify or MP3
    if (song.src.includes("spotify.com/track/")) {
        const trackId = song.src.split('/track/')[1]?.split('?')[0];
        if (!trackId) {
            console.error("Invalid Spotify link:", song.src);
            return;
        }

        const spotifyIframe = document.createElement("iframe");
        spotifyIframe.src = `https://open.spotify.com/embed/track/${trackId}`;
        spotifyIframe.width = "100%";
        spotifyIframe.height = "80";
        spotifyIframe.frameBorder = "0";
        spotifyIframe.allow = "encrypted-media";
        spotifyIframe.title = `Spotify preview of ${song.title} by ${song.artist}`;

        playerContainer.appendChild(spotifyIframe);
    } else {
        // Reset audio element
        audio.src = song.src;
        audio.currentTime = 0;
        audio.play();
        playerContainer.appendChild(audio);
    }

    userData.currentSong = song;
    highlightCurrentSong();
    setPlayerDisplay();
    setPlayButtonAccessibleText();
};


const pauseSong = () => {
    if (userData?.currentSong?.src.includes("open.spotify.com")) {
        // Spotify iframe does not support external pause
        console.log("Pause functionality is disabled for Spotify tracks.");
    } else {
        userData.songCurrentTime = audio.currentTime;
        playButton.classList.remove("playing");
        audio.pause();
    }
};

const playNextSong = () => {
    if (userData?.currentSong === null) {
        playSong(userData?.songs[0].id);
    } else {
        const currentSongIndex = getCurrentSongIndex();
        const nextSong = userData?.songs[currentSongIndex + 1];

        playSong(nextSong.id);
    }
};

const playPreviousSong = () => {
    if (userData?.currentSong === null) return;
    else {
        const currentSongIndex = getCurrentSongIndex();
        const previousSong = userData?.songs[currentSongIndex - 1];

        playSong(previousSong.id);
    }
};

const shuffle = () => {
    userData?.songs.sort(() => Math.random() - 0.5);
    userData.currentSong = null;
    userData.songCurrentTime = 0;

    renderSongs(userData?.songs);
    pauseSong();
    setPlayerDisplay();
    setPlayButtonAccessibleText();
};

const deleteSong = (id) => {
    if (userData?.currentSong?.id === id) {
        userData.currentSong = null;
        userData.songCurrentTime = 0;

        pauseSong();
        setPlayerDisplay();
    }

    userData.songs = userData?.songs.filter((song) => song.id !== id);
    renderSongs(userData?.songs);
    highlightCurrentSong();
    setPlayButtonAccessibleText();

    if (userData?.songs.length === 0) {
        const resetButton = document.createElement("button");
        const resetText = document.createTextNode("Reset Playlist");

        resetButton.id = "reset";
        resetButton.ariaLabel = "Reset playlist";
        resetButton.appendChild(resetText);
        playlistSongs.appendChild(resetButton);

        resetButton.addEventListener("click", () => {
            userData.songs = [...allSongs];

            renderSongs(sortSongs());
            setPlayButtonAccessibleText();
            resetButton.remove();
        });

    }

};

const setPlayerDisplay = () => {
    const playingSong = document.getElementById("player-song-title");
    const songArtist = document.getElementById("player-song-artist");
    const currentTitle = userData?.currentSong?.title;
    const currentArtist = userData?.currentSong?.artist;

    playingSong.textContent = currentTitle ? currentTitle : "";
    songArtist.textContent = currentArtist ? currentArtist : "";
};

const highlightCurrentSong = () => {
    const playlistSongElements = document.querySelectorAll(".playlist-song");
    const songToHighlight = document.getElementById(
        `song-${userData?.currentSong?.id}`
    );

    playlistSongElements.forEach((songEl) => {
        songEl.removeAttribute("aria-current");
    });

    if (songToHighlight) songToHighlight.setAttribute("aria-current", "true");
};

const renderSongs = (array) => {
    const songsHTML = array
        .map((song) => {
            return `
      <li id="song-${song.id}" class="playlist-song">
      <button class="playlist-song-info" onclick="playSong(${song.id})">
          <span class="playlist-song-title">${song.title}</span>
          <span class="playlist-song-artist">${song.artist}</span>
          <span class="playlist-song-duration">${song.duration}</span>
      </button>
      <button onclick="deleteSong(${song.id})" class="playlist-song-delete" aria-label="Delete ${song.title}">
          <svg width="20" height="20" viewBox="0 0 16 16" fill="none" xmlns="http://www.w3.org/2000/svg"><circle cx="8" cy="8" r="8" fill="#4d4d62"/>
          <path fill-rule="evenodd" clip-rule="evenodd" d="M5.32587 5.18571C5.7107 4.90301 6.28333 4.94814 6.60485 5.28651L8 6.75478L9.39515 5.28651C9.71667 4.94814 10.2893 4.90301 10.6741 5.18571C11.059 5.4684 11.1103 5.97188 10.7888 6.31026L9.1832 7.99999L10.7888 9.68974C11.1103 10.0281 11.059 10.5316 10.6741 10.8143C10.2893 11.097 9.71667 11.0519 9.39515 10.7135L8 9.24521L6.60485 10.7135C6.28333 11.0519 5.7107 11.097 5.32587 10.8143C4.94102 10.5316 4.88969 10.0281 5.21121 9.68974L6.8168 7.99999L5.21122 6.31026C4.8897 5.97188 4.94102 5.4684 5.32587 5.18571Z" fill="white"/></svg>
        </button>
      </li>
      `;
        })
        .join("");

    playlistSongs.innerHTML = songsHTML;
};

const setPlayButtonAccessibleText = () => {
    const song = userData?.currentSong || userData?.songs[0];

    playButton.setAttribute(
        "aria-label",
        song?.title ? `Play ${song.title}` : "Play"
    );
};

const getCurrentSongIndex = () => userData?.songs.indexOf(userData?.currentSong);

playButton.addEventListener("click", () => {
    if (userData?.currentSong === null) {
        playSong(userData?.songs[0].id);
    } else if (!userData?.currentSong?.src.includes("open.spotify.com")) {
        audio.play();
    }
});

pauseButton.addEventListener("click", pauseSong);

nextButton.addEventListener("click", playNextSong);

previousButton.addEventListener("click", playPreviousSong);

shuffleButton.addEventListener("click", shuffle);

audio.addEventListener("ended", () => {
    const currentSongIndex = getCurrentSongIndex();
    const nextSongExists = userData?.songs[currentSongIndex + 1] !== undefined;

    if (nextSongExists) {
        playNextSong();
    } else {
        userData.currentSong = null;
        userData.songCurrentTime = 0;
        pauseSong();
        setPlayerDisplay();
        highlightCurrentSong();
        setPlayButtonAccessibleText();

    }
});

const sortSongs = () => {
    userData?.songs.sort((a, b) => a.id - b.id); // Sort by ID in ascending order
    return userData?.songs;
};


renderSongs(sortSongs());
setPlayButtonAccessibleText();
