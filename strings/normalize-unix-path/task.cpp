#include <string>
#include <vector>

using namespace std;

string normalize(string_view path) {
  vector<string> cup;
  size_t i = 0;
  bool Absolute = !path.empty() && path[0] == '/';

  while (i < path.size()) {
    while (i < path.size() && path[i] == '/') {
      i++;
    }
    size_t start = i;
    while (i < path.size() && path[i] != '/') {
      i++;
    }
    string part = string(path.substr(start, i - start));
    if (part == "..") {
      if (!cup.empty() && (Absolute || (!Absolute && cup.back() != ".."))) {
        cup.pop_back();
      } else if (!Absolute) {
        cup.push_back("..");
      }
    } else if (!part.empty() && part != ".") {
      cup.push_back(part);
    }
  }
  string result;
  if (Absolute) {
    result = "/";
  } else {
    result = "";
  }
  for (const auto& dir : cup) {
    result += dir + "/";
  }
  if (!result.empty() && result.back() == '/') {
    result.pop_back();
  }
  if (result.empty()) {
    if (Absolute) {
      return "/";
    } else {
      return ".";
    }
  } else {
    return result;
  }
}
