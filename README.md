# Tetris
A copy of the classic arcade game tetris made for your terminal!

## Project story:
Like most good things in life this coding project began with an infinite amount of boredom. 

It all started with a friend of mine had brought his nintendo 3DS in class and was playing tetris (cause obviously tetris is way more important than a lecture about the binary system).

Seeing him play tetris jokingly one of us said why don't we try to recreate tetris. 

So the same way Issac Newton was so bored he stared at a falling apple and decided to invent gravity, we decided that instead of being bored during a lecture about stuff we already knew why not recreate tetris from scratch, cause what else is there to do right?

And then in slow motion with some really cool 2000s hacker movie editing with dramatic music we both pulled out our laptops and got to work. 

Okay maybe there wasn't any slow motion, or dramatic music but you get the point.

Each of us started our own repository and decided to make it a competion.

Fast forward a couple of days later we both completed our project. Not to say improvements can't be made but it works and they are both pretty fun to play if you're bored tbh.

You can check out his version [here.](https://github.com/Tsotciri/tetris)


## My experience:
This project actually turned out to be quite simpler than I was expecting. The algorith wasn't that hard to come up with and I can proudly say that the amount of AI used is minimal since i wanted to add an extra level of difficulty to this. 

It took me less than a day (as you can see by the commits too) to create the basic functionality of the game.

On the second day I did some fine tuning of the game fixing some bugs with the rotation etc. and i also made it an actual terminal game instead of an infinite scroll of print statements by adding logic which overides the previous board and redraws it again.

Finally on the third day i added arrow movement and also a score system.

So yeah thats about it, three days of nothing but boredom can lead to the recreation of a timeless arcade game for the terminal.

It was a fun side quest to say the least.

## How to run:
1. Prepare your environment: Make sure you have a C compiler (like gcc) as well as git on your machine.
2. In the terminal go to the directory you want to install the game
3. clone this repository
    ```bash
    git clone https://github.com/mitzCanCode/Tetris.git
    ```
4. Navigate to the created directory
    ```bash
    cd Tetris
    ```
5. Compile the game
    ```bash
    gcc Code/blocks.c Code/board.c Code/main.c -o {name-you-want-the-executable-to-have}
    ```

### Optional:

Create an alias to running the game so you can call it from anywhere in your terminal.

Example in bash or zsh:
1. Open your <i>.bashrc</i> (or <i>.zshrc</i> if you use zsh) in a text editor:
    ```bash
    nano ~/.bashrc
    ```
2. Add this some where in your <i>.bashrc</i> (or <i>.zshrc</i> if you use zsh)
    ```bash
    alias tetris='/full/path/to/executable/of/the/game'
    ```
3. Save and close the file. Then reload the shell:
    ```bash
    source ~/.bashrc
    ```