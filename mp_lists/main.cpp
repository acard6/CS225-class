#include "List.h"

using namespace std;

int main() {
  List<int> exList;
  exList.insertFront(3);
  exList.insertBack(2);
  exList.insertFront(8);
  exList.insertFront(2);
  exList.insertBack(1);

  cout << exList << endl;

  return 0;
}
