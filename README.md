# Huffman-Coding

Huffman coding is an efficient method of compressing data and assigning codes to characters such that the code's length depends on the corresponding character's relative frequency. 

A recent analysis of the network has indicated that the characters in use on the network are only those in the lowercase Latin (ascii) alphabet. This Huffman code is a new encoding method to reduce the cost and improve performance for data compression. 

The encoder is a 2-pass encoder, while the decoder is one-pass and uses the Huffman code table of the compressed file to decode the data. The two encode generates a Huffman tree and then encode the data. 

# Abstract Data Type Usage:

- Priority Queue
- Smart Pointer or shared_ptr of vector

# How does it work?

The programs can encode and decode text file consisting of 128 ASCII alphabet.

Encode:
* Construct Priority Queue and then Huffman Tree;
* Calculate Huffman Encode Table;

Decode:
* Recreate Huffman Tree based on Huffman Encode Table;
* Decode the file based on the tree .

You can check out documentation inside Encoder.cpp, which includes the encoder and decode functions to help you understand Huffman's algorithm's inner workings.

#Hint: If you need a collection of letter frequencies to experiment with see 
https://en.wikipedia.org/wiki/Letter_frequency 
https://iq.opengenus.org/huffman-encoding/
