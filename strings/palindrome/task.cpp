#include <vector>
#include <string>
#include <algorithm>
#include "task.h"


std::vector<char> letters = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
};

std::vector<char> letters_low = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z'
};

std::vector<char> letters_big = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
};

bool isalpha(unsigned char c) {
  auto it = find(letters.begin(), letters.end(), c);
  if(it != letters.end()){
    return true;
  }else{
    return false;
  }
}

unsigned char tolower(unsigned char c) {
  if(isalpha(c)){
    auto it = find(letters_big.begin(), letters_big.end(), c);
    if(it != letters_big.end()){
      return letters_low[it - letters_big.begin()];
    }else{
      return c;
    }
  }
  else{
    return c;
  }
}


bool is_palindrome(const std::string& s) {
  std::string words;
  for(size_t i = 0; i < s.size(); i++){
    if(isalpha(s[i])){
      words += tolower(s[i]);
    }
  }
  std::string rev = words;
  reverse(rev.begin(), rev.end());
  if (words == rev){
    return true;
  }
  else {
    return false;
  }
}
