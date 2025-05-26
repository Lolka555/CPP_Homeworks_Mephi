#include <map>
#include <vector>
#include <string>

/*
 * Напишите реализацию оператора < для типа SuperKey,
 * чтобы ключи типа SuperKey можно было использовать в map.
 * Порядок должен быть таким,
 * чтобы все ключи с одинаковым значением поля StrPart шли друг за другом без пропусков.
 * Напишите функцию PopulateMap,
 * которая добавляет в map пары ключ-значение из данного вектора toAdd
 */

struct SuperKey {
    std::string StrPart;
    int IntPart;
    float FloatPart;

    bool operator==(const SuperKey& rhs) const {
        return this->StrPart == rhs.StrPart && this->IntPart == rhs.IntPart &&
             this->FloatPart == rhs.FloatPart;
    }
};

bool operator <(const SuperKey& lhs, const SuperKey& rhs);
/*
{
  if (!(lhs.StrPart == rhs.StrPart)){
    return lhs.StrPart < rhs.StrPart;
  }else if(!(lhs.IntPart == rhs.IntPart)){
    return lhs.IntPart < rhs.IntPart;
  }else{
    return lhs.FloatPart < rhs.FloatPart;
  }
}
 */
void PopulateMap(
    std::map<SuperKey, std::string>& map,
    const std::vector<std::pair<SuperKey, std::string>>& toAdd);
/*
{
  for (const auto& pair : toAdd) {
    map.insert(pair);
  }
}
 */