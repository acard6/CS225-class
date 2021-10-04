#include "List.h"

using namespace std;

int main() {
  List<unsigned> list;
  list.insertFront(3);
  list.insertBack(2);
  list.insertFront(8);
  list.insertFront(2);
  list.insertBack(1);

  list.tripleRotate();

  /**
  List<unsigned>::ListIterator iterB = list.begin();
  iterB++;
  cout << *iterB << endl;

  List<unsigned>::ListIterator iterE = list.end();
  iterE--;
  cout << *iterE << endl;
  */
  return 0;
}
