#include "searcher.h"
#include <iostream>
#include <fstream>
#include <time.h>


int main()
{
    std::vector <Pair> ghostery_mock = {{0, "doubleclick.com"}, {1, "advertising.com"}, {2, "valueclick.com"}};
    Searcher mysearcher = Searcher(ghostery_mock);
    std::vector <int> res;
    res = mysearcher.search("doubleclick.com/blah?click=advertising.com");

  std::vector <Pair> bigtest_mock;

  std::string line;
  std::ifstream fp ("/usr/share/dict/words");
  int cnt = 0;
  if (fp.is_open())
  {
    while ( fp.good() )
    {
      getline (fp,line);
      Pair line_pair = Pair(cnt, line);

      bigtest_mock.push_back(line_pair);
      cnt+=1;
    }
    fp.close();
  }else{
   std::cout << "Unable to open file"; 
  }

  mysearcher = Searcher(bigtest_mock);
  #define MAX_RUNS 1000

  clock_t start_time = clock();

  fp.seekg(0);
  for(int i = 0; i < MAX_RUNS; i++)
  {
    std::string word;
    getline (fp,word);
    mysearcher.search(word);
  }
  clock_t end_time = clock();
  std::cout <<  "Searching inside of the dictionary took: " << (end_time- start_time)/float(CLOCKS_PER_SEC) << std::endl;

  return 0;
}
