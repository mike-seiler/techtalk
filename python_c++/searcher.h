#include <string>
#include <vector>

typedef std::pair<int,std::string> Pair;


class Searcher
{
  private:
    std::vector <Pair> data;
  public:
    Searcher(std::vector<Pair> _data): data(_data)
    {
    }

    std::vector <int>
    search(const std::string & haystack)
    {
      std::vector <int> res;
      for(auto it = data.begin(); it != data.end(); ++it){
        unsigned long found = haystack.find(it->second);
        if (found!=std::string::npos)
        {
          res.push_back(it->first);
        }

      }
      return std::move(res);
    }

    ~Searcher(void)
    {
    }
};
