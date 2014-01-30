import hello

print hello.hello()
assert(hello.hello() == 'Hello World')


print hello.hello_to_you("Max")
try:
  print hello.hello_to_you(["Max"])
except TypeError, e:
  print 'Caught Type error %s' % repr(e)
