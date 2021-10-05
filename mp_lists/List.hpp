/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * curr = head_;
  ListNode * previous;
  while (curr != NULL){
    previous = curr;
    curr = curr -> next;
    delete previous;
  }
  previous = NULL;
  length_ = 0;
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
    head_ = newNode;
  }else{
    head_ = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  

  length_ = length_ + 1;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = tail_;
  newNode -> next = NULL;

  if (tail_ != NULL) {
    tail_ -> next = newNode;
    tail_ = newNode;
  }else{
    tail_ = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }

  length_ = length_ + 1;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (splitPoint >= length_){
    return head_;
  }

  ListNode* curr = start;
  int count = 0;
  while (count < splitPoint){
    curr =  curr->next;
    count++;
  }

  tail_ = curr->prev;
  curr->prev->next = NULL;
  curr->prev = NULL;
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* start = head_;
  ListNode* end = start;
  ListNode* middle;
  ListNode* temp;

  int blocks = length_ / 3;
  for (int i=0; i<blocks; i++){
    middle = start->next;
    end = middle->next;
    temp = end;

    middle->prev = start->prev;
    start->next = end->next;
    start->prev = end;
    end->next = start;

    start = temp;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  ListNode* curr = startPoint;
  ListNode* after = curr->next;
  ListNode* begin = startPoint->prev;
  curr->next = endPoint->next;
  curr->prev = after;
  curr = after;

  while (curr != endPoint){
    after = curr->next;
    curr->next = curr->prev;
    curr->prev = after;
    curr = after;
  }

  endPoint->next = endPoint->prev;
  endPoint->prev = begin;

  if (head_ != startPoint){
    begin->next = curr;
  }if (head_ == startPoint){
    head_ = endPoint;
  }

  if (tail_ != endPoint){
    startPoint->next->prev = startPoint;
  }if (tail_ == endPoint){
    tail_ = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode* start = head_;
  ListNode* end = start;

  while (start != NULL){
    int i = 1;
    while (i < n){
      if (end != tail_){
        end = end->next;
      }
      i++;
    }
    reverse(start,end);
    start = start->next;
    end = start;
    
  }

}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* newStart;

  if (first->data < second->data){
    newStart = first;
    first = first->next;
  }else{
    newStart = second;
    second = second->next;
  }

  ListNode* temp = newStart;
  while (first != NULL && second != NULL){
    if (first->data < second->data){
      temp->next = first;
      first->prev = temp;
      first = first->next;
    }else {
      temp->next = second;
      second->prev = temp;
      second = second->next;
    }
    temp = temp->next;
  }

  if (first == NULL && second != NULL){
    //end of the first but second still has more
    temp->next = second;
    second->prev = temp;
  }

  if (first != NULL && second == NULL){
    //end of the second but first still has more
    temp->next = first;
    first->prev = temp;
  }
  return newStart;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1){return start;}
  ListNode* start2 = split(start, chainLength/2);
  return merge(mergesort(start,chainLength/2),mergesort(start2,chainLength/2+chainLength%2));

}
