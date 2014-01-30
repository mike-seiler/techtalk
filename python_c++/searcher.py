import search_helper

class Searcher(object):
  def __init__(self, data):
    self.search_helper_data =  search_helper.load(data)

  def search(self,substring):
    return search_helper.search(self.search_helper_data, substring)

  def __del__(self):
    search_helper.destroy(self.search_helper_data)


if __name__ == "__main__":
  ghostery_mock = [(0, "doubleclick.com"), (1, "advertising.com"), (2, "valueclick.com")]
  searcher = Searcher(ghostery_mock)
  res = searcher.search("doubleclick.com/blah?click=advertising.com")
  assert( res == [0,1 ] )

  fp = open("/usr/share/dict/words", 'r')
  cnt = 0
  bigtest_mock = []
  for line in fp:
    bigtest_mock.append( ( cnt, line.lower().strip()) )
    cnt+=1

  searcher = Searcher(bigtest_mock)
  import time
  start = time.time()
  MAX_RUNS = 10**3
  fp = open("/usr/share/dict/words", 'r')
  for i in xrange(MAX_RUNS):
    word = fp.next().lower().strip()
    searcher.search(word)
  print "Searching inside of the dictionary took: %f" % (time.time() - start)



