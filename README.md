## Practical Dynamic Programming algorithm application: the human family

This program implements the DNA alignment algorithm that uses O(n^2) space described in https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm

The following scoring scheme is used to measure simularity

|   | A  | C  | G  | T  | -  |
|:-:|----|----|----|----|----|
| A | 5  | -1 | -2 | -1 | -3 |
| C | -1 | 5  | -3 | -2 | -4 |
| G | -2 | -3 | 5  | -2 | -2 |
| T | -1 | -2 | -2 | 5  | -1 |
| - | -3 | -4 | -2 | -1 | *  |


The program is written in c++ and can be run by running the bash script, `run.sh`