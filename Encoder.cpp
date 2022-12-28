#include "Encoder.h"

using namespace std;

// Constructor Encoder and build a tree
Encoder::Encoder(shared_ptr<vector<int>> &vec) {
  if (vec->size() > 26 || vec->size() < 0 || vec->size() < 26) {
    throw invalid_argument("Error More than 26 letter frequencies or less than "
                           "0 letter frequencies");
    return;
  }
  char alphabet[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                       'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                       's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '-'};
  priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Compare> store;
  for (int i = 0; i < vec->size(); i++) {
    if ((*vec)[i] == 0) {
      throw invalid_argument("0 Frequency Error");
      return;
    }
    if ((*vec)[i] != 0 && (*vec)[i] > 0) {
      shared_ptr<Node> node =
          make_shared<Node>(alphabet[i], (*vec)[i], nullptr, nullptr);
      store.push(node);
    }
  }

  // push in the delimiter into the priority queue
  store.push(make_shared<Node>(alphabet[26], INT_MAX, nullptr, nullptr));

  // build a tree
  while (store.size() != 1) {
    shared_ptr<Node> r = store.top();
    store.pop();
    shared_ptr<Node> l = store.top();
    store.pop();
    // compare the case where the frequencies of each letter are equal
    if (r->freq == l->freq) {
      shared_ptr<Node> temp = l;
      shared_ptr<Node> temp1 = r;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      while (temp1->left != nullptr) {
        temp1 = temp1->left;
      }
      if (temp->letter > temp1->letter) {
        shared_ptr<Node> tem = l;
        l = r;
        r = tem;
      }
    }
    int sum = l->freq + r->freq;
    store.push(make_shared<Node>(' ', sum, l, r));
  }
  // set the last value in pq as the root
  root = store.top();
}

//Encode function
shared_ptr<vector<char>> Encoder::Encode(string str) {
  shared_ptr<vector<char>> ret;
  vector<char> sub;
  string binary = "";
  string storeStr;
  char st;
  unordered_map<char, string> result;
  std::bitset<8> bits;

  for (int i = 0; i < str.size(); i++) {
    st = str[i];
    //throw exception if there is uppercase and space 
    if (st >= 'A' && st <= 'Z' || st == ' ' || st >= '0' && st <= '9') {
      throw invalid_argument("uppercase letter or space is not allowed");
      return 0;
    }
    // call recursive Encode to find the binary bits in tree for specific letter
    recursiveEncode(root, result, st, binary);
  }
  recursiveEncode(root, result, '-', binary);

  for (int i = 0; i < str.size(); i++) {
    storeStr += result[str[i]];
  }
  //turn binary bits into 8 bits, add bits if needed. 
  while (storeStr.size() > 0) {
    string letter = {};
    char temp = 0x00;
    if (storeStr.size() > 8) {
      for (int i = 0; i < 8; i++) {
        letter += storeStr[i];
      }
    } else
      for (int i = 0; i < storeStr.size(); i++) {
        letter += storeStr[i];
      }
    istringstream in(letter);
    while (in >> bits) {
      if (storeStr.size() < 8) {
        int len = 8 - storeStr.size();
        bits = bits << len;
      }
      temp = temp | char(bits.to_ulong());
      sub.push_back(temp);
    }
    if (storeStr.size() > 8)
      storeStr.erase(storeStr.begin(), storeStr.begin() + 8);
    else
      storeStr.erase(storeStr.begin(), storeStr.end());
  }
  //set return(ret) as shared ptr of vector
  ret = make_shared<vector<char>>(sub);
  return ret;
}

//Decode Function
string Encoder::Decode(shared_ptr<vector<char>> &vect) {
  string result;
  string vec;
  shared_ptr<Node> curr = root;
  for (int i = 0; i < vect->size(); i++) {
    bitset<8> temp(vect->at(i));
    vec += (temp.to_string());
  }
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] == '0') {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
    if (curr->left == nullptr && curr->right == nullptr) {
      if (curr->letter == '-') {
        return result;
      } else {
        result.push_back(curr->letter);
        curr = root;
      }
    }
  }
  return result;
}

// recursive for encode function
void Encoder::recursiveEncode(shared_ptr<Node> root,
                              unordered_map<char, string> &result, char st,
                              std::string binary) {
  if (root == nullptr)
    return;
  if (st == root->letter) {
    result[st] = binary;
  }
  recursiveEncode(root->right, result, st, binary + '1');
  recursiveEncode(root->left, result, st, binary + '0');
}
