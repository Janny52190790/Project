# Author Identification
For this assignment, you will be creating a program that attempts to identify the most likely authors for an anonymous sample of text given a large database of texts with known authors.
## Building
```
$ make
```
## Running
```
$ ./identify [d:K:n:l:emcv] [-d database] [-k matches] [-n noisefile] [-l limit]
```
## Command line options
```
-d : Specify path to database of authors and texts. The default is lib.db.
-n : Specify path to file of noise words to filter out. The default is noise.txt.
-k : Specify the number of matches. The default is 5.
-l : Specify the number of noise words to filter out. The default is 100.
-e : Set the distance metric to use as the Euclidean distance. The default is default metric.
-m : Set the distance metric to use as the Manhattan distance.
-c : Set the distance metric to use as the cosine distance.
-h : Display program help and usage.
```
text create cite from Audrey's pseudocode
pq cite from asgn3.pdf and assignment 3 and assignment 6 and instructions from Miles.
cite the hash table from class slides.
```
scan_build usage:
make clean
scan-build --use-cc=clang make
```
