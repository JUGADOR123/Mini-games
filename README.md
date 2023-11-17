# Chyaru Minigames!

Hello there, this repo is a collection of various minigames written in c++ that I have been working on.
down bellow is a description of each minigame included:


## Minigames

 - Rope Hanger: you have to guess a word letter by letter, but be careful! you have a limited amount of tries before you loose!
 - Minesweeper: The classic game where you go around and try not to explode, go looking out for the mines and try to find them all.
 - Jumping Squad: Fun for the whole family, try to reach the end by jumping spaces, but you know the computer knows every move and will fight with math.
 - Tetris: Good 'ol classic tetris, using different shapes try to make the most lines to win the highscore.
 - TypeSong: Try to write the song's lyric based on what you remember.
 - **More games to come!!!**


## Main.cpp

Here's the menu of the games, there are 8 options. 
 1. Play TypeSong
 2. Play Hanged
 3. Play Jump against Computer
 4. Play minesweeper
 5. Play Tetris
 6. Statistics
    It Shows the info of every registered player. 
 7. Information of a certain player
    It shows the info of the selected player.
 8. Quit

# All of the next files are classes. 
## Jugador.h

It is mean to be the info of a single player. 
containing nickname, best_score, worst_score and the games already played.

## TypeSong.h

It includes 12 popular songs, the tittle and the lyrics. 
We included a DP, making the lyrics written by the username the most similar possible to the original lyrics. 
For example: 
"Hello World" and "Hsssssssesssssssssssslssssssslssssssssssosssssssss orld" Would score every letter except the W. If the player gets a letter wrong, it won't affect the entire text. If we compare it letter by letter this case would get almost everything wrong. -> "Hello World" and "Hllo Wolrd".
The functions works this way: 
$f(i = letter i of the original lyrics, j = letter j of the user lyrics, or = original lyrics, ul = user lyrics) = letter[i]==letter ? f(i+1, j+1, ol, ul) + 1 : max(f(i+1, j, ol, ul), f(i, j+1, ol, ul))$

## Ahorcado.h

It has multiple sentences with 3 dificulties: Easy, Medium and Hard.
And a visual representation depending in the mistakes made by the moment. 
The function ronda_ahorcado can return 3 different values. 1 if the user made a mistake, 0 if the guessed the letter and -1 if the user completed the sentence. 

## SaltoContraComputadora.h

M = the maximun size of the jump 
N = the size of the line
We made an algorithm that makes the computer play in the most optimal way, there are certain cases in which the users can win. 
This algorithm is defined in the function salto_computadora. 
It will try to jump to some multiple of M related to N (from the final to the beginning).  

