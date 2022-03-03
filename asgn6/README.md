#Something I haven’t solved yet
It is really wired that I could not enqueue binary files but all other files are fine.

# Assignment 6 - Huffman Coding
Huffman coding is a method to reduce the size of data/message.

## Automate compilation by using Makefile
```
$ make
```

## Cleaning
```
$ make clean
```

## Running

```
$ ./encode -i <infile> -o <outfile>
```
```
$ ./decode -i <infile> -o <outfile>
```
## the command-line options your program accepts
## encode
• -h: Prints out a help message describing the purpose of the program and the command-line options it accepts, exiting the program afterwards. Refer to the reference program in the resources repo for an idea of what to print.\
• -i infile: Specifies the input file to encode using Huffman coding. The default input should be set as stdin.\
• -o outfile: Specifies the output file to write the compressed input to. The default output should be set as stdout.\
• -v: Prints compression statistics to stderr.\
## decode
• -h: Prints out a help message describing the purpose of the program and the command-line options it accepts, exiting the program afterwards. Refer to the reference program in the resources repo for an idea of what to print.\
• -i infile: Specifies the input file to decode using Huffman coding. The default input should be set as stdin.\
• -o outfile: Specifies the output file to write the decompressed input to. The default output should be set as stdout.\
• -v: Prints decompression statistics to stderr.\
