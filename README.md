# Hangman Solver

Just a quick hangman solver I wrote to beat my friend.

## Installation

1. Download
2. `make build`
3. Run with `./hmsolv`
4. Exit with CTRL-C

## Usage

1. Generally you set the length of the word first with `length n`
2. You can specify letters that are known not to exist with `no l`
3. You can set a known character with `char n c` where n is 0 indexed to the word.
4. `analyze` spits out the most likely letters occuring in the remaining list.
5. `words` lists the remaining words in the world list.

## Todo

Some ideas I could implement in the future:

* Have a game mode where the computer picks a word and the user guesses.
* Human picks a world and the computer does a guess loop on it0 automatically.

