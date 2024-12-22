# Music Player App

- [x] a web-based application using HTML, SQL and JavaScript
- [x] a CS50's [Final Project](https://cs50.harvard.edu/x/2024/project/)
- [x] Video Demo:  <https://youtu.be/zHFBVluKg28>

## Description:

  This project is an interactive web-based music player designed to provide users with a seamless music listening experience. Built using HTML, CSS, SQL, and JavaScript, the application features a music player interface that allows users to play, pause, navigate through songs, shuffle the playlist, and delete tracks. It is also mobile-friendly, ensuring accessibility across devices and enhancing user convenience.

### Technical Overview

  From a technical perspective, the project is structured using a combination of front-end and back-end technologies to ensure functionality and responsiveness. The key components include:

1. [HTML](index.html)

    HTML serves as the backbone of the project, providing the structure and content for the web application. The design utilizes ```<div>``` elements to separate and organize various sections of the music player, such as the control panel, playlist, and album art display. Semantic HTML enhances accessibility and readability for users and developers alike.

2. [CSS](styles.css)

    CSS handles the visual aesthetics of the application. Reusable variables defined with ```:root``` ensure concise and maintainable code. Responsive design is achieved through ```@media``` queries, enabling the interface to adapt seamlessly to different screen sizes, including mobile devices. Custom styles ensure an intuitive and visually appealing user experience.

3. [JavaScript](script.js)

    JavaScript drives the application's interactivity. Event listeners ```.addEventListener``` handle user actions such as play, pause, and shuffle. Functions dynamically update the song title and album art when a new track is played. Notably, online songs are embedded via Spotify's ```iframe``` API, allowing previews while respecting copyright. For locally stored MP3 files, the player fully supports play and pause functionality.

### Features and Functionality

The application is designed with the user in mind, offering several features to make music listening simple and enjoyable:

1. Core Music Player Controls

    - Play/Pause: Users can easily start and stop songs.
    - Next/Previous: Navigation buttons enable seamless movement between tracks.
    - Shuffle: A shuffle feature randomizes the playlist for a fresh experience.

2. Playlist Management

    Users can view the playlist below the music player controls. The playlist allows for:
   
    - Deleting unwanted tracks.
    - Scrolling through the list on both desktop and mobile.

4. Dynamic Song Handling

    - Spotify Integration: Online songs are embedded using Spotify’s iframe API, providing previews. Full playback requires users to log in on Spotify’s platform.
    - MP3 Playback: Locally stored MP3 files can be played and paused directly, offering greater flexibility for users.

5. Album Cover Art and Metadata

    The player prominently displays album cover art, song titles, and artist names, creating a visually engaging interface. These elements are dynamically updated as users interact with the playlist.

6. Mobile-Friendly Design

    The application has been optimized for mobile devices, ensuring a consistent and functional experience across various screen sizes. CSS media queries ensure elements are resized and repositioned appropriately for smaller screens.

### Challenges and Limitations

While the project is functional and user-friendly, there are some unresolved challenges and potential areas for improvement:

1. SQL Implementation

   The current version does not fully utilize SQL for data storage. Adding a database would enable features like saving playlists and tracking user preferences.

2. Spotify API Limitations

   Spotify’s iframe only allows song previews unless the user is logged in on a separate Spotify page. Exploring alternative APIs might provide more flexibility.

3. Playlist Persistence

   Currently, the playlist resets when the page is reloaded. Incorporating local or server-side storage could allow users to save their playlists.

4. Advanced Audio Controls
    Features such as adjusting playback speed, looping, or visual equalizers could enhance the listening experience.

### Future Developments

Moving forward, the project has several potential enhancements:

  - Database Integration: Fully implement SQL for user-specific features.
  - Customizable Playlists: Allow users to create, rename, and manage multiple playlists.User Authentication: Add login functionality to save preferences and enable cloud-based storage.
  - Offline Support: Use service workers to enable offline playback of locally stored songs.
  - Enhanced Visuals: Introduce animations and themes to create a more immersive interface.

### Conclusion

This music player project combines essential technical skills and creative design to deliver a functional and visually appealing application. By leveraging HTML, CSS, and JavaScript, it showcases a harmonious integration of front-end and back-end technologies. While there is room for growth, the current implementation highlights the potential for developing robust, user-centered web applications. The project stands as both a practical tool for music enthusiasts and a testament to the developer’s technical capabilities.


#### Others

1. A short [video](https://youtu.be/zHFBVluKg28); and submit this [form](https://forms.cs50.io/d5009db5-ee7d-43f1-8214-87cebc1a554f)!

    - The video begins with an opening section that displays:
      - project title: Music Player App
      - name: Han Wang
      - GitHub username: WHan7naHW
      - edX username: Hannahw007
      - city and country: Oulu, Finland
      - the date of recording this video: Dec. 22nd, 2024
    - It then goes on to demonstrate the project in action. 

2. A ```README.md``` text file that explains the project; and ```submit50``` to cs50.

3. The [gradebook](cs50.me/cs50x); and my [Certificate. 


---
💡 ```This was CS50x!``` 🥰
