def load(data):
  return data

def search(data, substring):
  res = []
  for index, needle in data:
    if needle in substring:
      res.append(index)
  return res


def destroy(data):
  pass #let the python GC do its magic
