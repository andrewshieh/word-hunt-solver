# Word Hunt Solver

A simple, lightweight, no-frills solver for Word Hunt. Word Hunt is an
iMessage game where two players compete to form as many words as possible
from a 4x4 letter grid in 80s by connecting adjacent letters together.

The solver uses a trie to support fast word inserting and prefix searching,
then runs depth first search starting from each tile to find all valid words
on the board. The output is a printed list starting with the highest-scoring
words.

## Installation

- Clone: `git clone https://github.com/andrewshieh/word-hunt-solver.git`
- Change directory: `cd word-hunt-solver`
- Then compile: `g++ -std=c++11 -o solver solver.cpp`

```
Usage: ./solver <board>

Board:         Input:
a b c d        ./solver abcdefghijklmnop
e f g h
i j k l
m n o p
```