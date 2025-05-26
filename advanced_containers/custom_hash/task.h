#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

struct SuperKey {
    std::string StrPart;
    int IntPart;
    float FloatPart;

    bool operator==(const SuperKey& rhs) const {
        return this->StrPart == rhs.StrPart && this->IntPart == rhs.IntPart && this->FloatPart == rhs.FloatPart;
    }
};


namespace std {
template <>
struct hash<SuperKey> {
  std::size_t operator()(const SuperKey& key) const {
    std::size_t h1 = std::hash<std::string>()(key.StrPart);
    std::size_t h2 = std::hash<int>()(key.IntPart);
    std::size_t h3 = std::hash<float>()(key.FloatPart);
    return h1 ^ (h2 << 1) ^ (h3 << 2);
  }
};
}

void PopulateHashMap(
    std::unordered_map<SuperKey, std::string>& hashMap,
    const std::vector<std::pair<SuperKey, std::string>>& toAdd
);

