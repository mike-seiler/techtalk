class Counter{
  private:
    int counter;
  public:
    Counter(int _counter): counter(_counter){
    }

    Counter(): counter(0){
    }
    int increment(int incr){
      counter += incr;
      return counter;
    }
};
