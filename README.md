# Text Compression Final
## About
This is my final project for our Data Structures class. The purpose of the project was to combine many of the structures that we had learned about into a text compression project.
The structures used were:
- Trees
- Priority Queues
- Hash Tables (Maps)
## How It Works
1. The program takes in a string. This would preferably be a long string.
2. A frequency table is used to find how many times each character appears in the string.
3. The characters are put in a priority queue so it can sort them based on their frequency.
4. A binary tree is constructed of all of the characters based on their frequency. Highest frequency are closer to the top and lowest frequency are at the bottom leaves.
5. Huffman coding is then used to assign each character a bit code by traversing the tree. It starts at the root of the tree and, for every character, it traverses the tree until it reaches the leaf. Every time it moves to the left child, a 0 is appended to that character's code. Every right child traversal appends a 1. In the end, the most frequent characters have the shortest bit codes and the least frequent have the longest.  
6. Once the codes have been determined, all it does is swap out the bits that would normally be stored for each of the characters with the code for that character. This way, in the case of e, it only has to store 3 bits each time instead of 8 (See example code).
7. In order to decode the bits, as long as it still has the same binary tree that it used to create the codes, it can simply traverse the tree, going left or right for each 0 and 1, until it reaches a leaf. It saves that character and then goes back to the tree root and continues.

## Example Output
```
Enter text:
This sentence is being used as an example.

Frequency Table:
 : 7
.: 1
T: 1
a: 3
b: 1
c: 1
d: 1
e: 7
g: 1
h: 1
i: 3
l: 1
m: 1
n: 4
p: 1
s: 5
t: 1
u: 1
x: 1

Priority Queue:
(., 1) -> (T, 1) -> (b, 1) -> (c, 1) -> (d, 1) -> (g, 1) -> (h, 1) -> (l, 1) -> (m, 1) -> (p, 1) -> (t, 1) -> (u, 1) -> (x, 1) ->  
(a, 3) -> (i, 3) -> (n, 4) -> (s, 5) -> ( , 7) -> (e, 7) ->  nullptr

Huffman encoding tree:
         (e, 7)
      ( e, 14)
         ( , 7)
   (tuaix.T e, 25)
                  (T, 1)
               (.T, 2)
                  (., 1)
            (x.T, 3)
               (x, 1)
         (ix.T, 6)
            (i, 3)
      (tuaix.T, 11)
            (a, 3)
         (tua, 5)
               (u, 1)
            (tu, 2)
               (t, 1)
(nbcdghlmpstuaix.T e, 42)
         (s, 5)
      (hlmps, 9)
               (p, 1)
            (mp, 2)
               (m, 1)
         (hlmp, 4)
               (l, 1)
            (hl, 2)
               (h, 1)
   (nbcdghlmps, 17)
               (g, 1)
            (dg, 2)
               (d, 1)
         (bcdg, 4)
               (c, 1)
            (bc, 2)
               (b, 1)
      (nbcdg, 8)
         (n, 4)

Huffman codes:
 : 110
.: 101110
T: 101111
a: 1001
b: 00100
c: 00101
d: 00110
e: 111
g: 00111
h: 01000
i: 1010
l: 01001
m: 01010
n: 000
p: 01011
s: 011
t: 10000
u: 10001
x: 10110

Uncompressed bit sequence:
010101000110100001101001011100110010000001110011011001010110111001110100011001010110111001100011011001010010000001101001011100  
110010000001100010011001010110100101101110011001110010000001110101011100110110010101100100001000000110000101110011001000000110  
000101101110001000000110010101111000011000010110110101110000011011000110010100101110

Encoded:
101111010001010011110011111000100001110000010111111010100111100010011110100000011111010001011111001101101001011110100100011011
1101101001010100101101001111101110     

Decoded:
This sentence is being used as an example.

Compressed to 47.619% of original size.
```
