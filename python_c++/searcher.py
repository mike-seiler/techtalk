import search_helper
import hashlib
import sys

class Searcher(object):
  def __init__(self, data):
    self.search_helper_data =  search_helper.load(data)

  def search(self,substring):
    return search_helper.search(self.search_helper_data, substring)

  def __del__(self):
    search_helper.destroy(self.search_helper_data)


def other_cpu_task(word):
  return hashlib.sha256(word).hexdigest()


def main():
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
    h = other_cpu_task(word)
  print "Searching inside of the dictionary took: %f" % (time.time() - start)

if __name__ == "__main__":
  if len(sys.argv) > 1 and sys.argv[1] == 'profile':
    print >> sys.stderr, 'Profiling', sys.argv[0]
    import cProfile
    cProfile.run('main()','profile.out')
  else:
    main()
