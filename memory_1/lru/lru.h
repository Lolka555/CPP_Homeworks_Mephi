#include <unordered_map>
#include <list>

template <typename K, typename V>
class LruCache {
private:
  size_t max_size_c;
  std::list<std::pair<K, V>> keys;
  std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> data;

public:
  LruCache(size_t max_size): max_size_c(max_size) {}

  void Put(const K& key, const V& value){
    if(data.find(key) != data.end()){
      keys.splice(keys.end(), keys, data[key]);
      keys.rbegin()->second = value;
    }else{
      if(keys.size() == max_size_c){
        data.erase(keys.front().first);
        keys.pop_front();
      }
      keys.emplace_back(key, value);
      data[key] = std::prev(keys.end());
    }
  }

  bool Get(const K& key, V* value){
    if (data.find(key) != data.end()) {
      keys.splice(keys.end(), keys, data[key]);
      *value = data[key]->second;
      return true;
    }
    return false;
  }
};