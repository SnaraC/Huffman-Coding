#ifndef _ENCODER_
#define _ENCODER_

#include <algorithm>
#include <bitset>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>


using namespace std;

class Encoder {
public:
  struct Node {
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    int freq;
    char letter;
    // constructor node as setter
    Node(char letter1, int freq1, std::shared_ptr<Node> left1,
         std::shared_ptr<Node> right1) {
      this->letter = letter1;
      this->freq = freq1;
      this->left = left1;
      this->right = right1;
    }
  };
  // Compare struct use for priority queue
  struct Compare {
    bool operator()(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
      if (left->freq == right->freq)
        return right->letter > left->letter;
      return left->freq > right->freq;
    }
  };
  // public constructor passing array of letter frequencies.
  Encoder(std::shared_ptr<vector<int>> &vec);

  // Encode std::string into a sequence of bytes.
  std::shared_ptr<std::vector<char>> Encode(std::string);

  // Decode an array of bytes into a std::string.
  std::string Decode(std::shared_ptr<std::vector<char>> &vect);

  // recursive for encode function
  void recursiveEncode(std::shared_ptr<Node> root,
                       unordered_map<char, string> &result, char st,
                       std::string binary);

private:
  std::shared_ptr<Node> root;
};

#endif