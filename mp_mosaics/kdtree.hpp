/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] != second[curDim]){
      return (first[curDim] < second[curDim]);
    }else{
      return (first < second);
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int distFirst = 0; 
    int distSecond = 0;
    for (int k = 0; k < Dim; k++){
      distFirst += pow((target[k] - currentBest[k]),2);
      distSecond += pow((target[k] - potential[k]),2);
    }
    if (distFirst != distSecond){
      return (distSecond < distFirst);
    }else{
      return (potential < currentBest);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.empty()){
      root = NULL;
      size = 0;
      return;
    }
    else{
      vector<Point<Dim>> points = newPoints;
      size = 0;
      root = KDhelper(points,0, points.size()-1, 0);

    }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDhelper(vector<Point<Dim>>& newPoints, 
                                    int start, int end, int plane){  
  if (start > end){return NULL;}

  unsigned int mid = (start + end) / 2;
  Point<Dim> selected = quick_select(newPoints, start, end, mid, plane);
  KDTreeNode* subroot = new KDTreeNode(selected); 
  size++;
  if (subroot == NULL){return NULL;}
  plane = (plane + 1) % Dim;
  subroot->right = KDhelper(newPoints, mid+1, end, plane);
  subroot->left = KDhelper(newPoints, start, mid-1, plane);
  return subroot;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quick_select(vector<Point<Dim>>& newPoints, int start, int end, int k, int plane){
  if (start >= end){
    newPoints[start];
  }
  int pivotIndex = k;//(start + end) / 2;
  pivotIndex = partition(newPoints, start, end, pivotIndex, plane);
  if (k == pivotIndex){
    return newPoints[k];
  }else if (k < pivotIndex){
    return quick_select(newPoints, start, pivotIndex-1, k, plane);
  }else {
    return quick_select(newPoints, pivotIndex+1, end, k, plane);
  }

}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int start, int end, int piv, int plane){
  Point<Dim> pivotValue = newPoints[piv];
  swap(newPoints[end], newPoints[piv]);
  int storeIndex = start;
  for (int i = start; i < end; i++){
    if (smallerDimVal(newPoints[i], pivotValue, plane)){
      swap(newPoints[storeIndex], newPoints[i]);
      storeIndex++;
    } 
  }
  swap(newPoints[end], newPoints[storeIndex]);
  return storeIndex;
}

template <int Dim>
void KDTree<Dim>::copy_(const KDTreeNode* subroot, KDTreeNode* other){
  subroot = new KDTreeNode();
  subroot->point = other->point;
  copy_(subroot->left, other->left);
  copy_(subroot->right, other->right);
}

template <int Dim>
void KDTree<Dim>::delete_(KDTreeNode* subroot){
  if (subroot != NULL){
    if (subroot->left){
      delete_(subroot->left);
    }
    if (subroot->right){
      delete_(subroot->right);
    }
  }
  delete subroot;
  subroot = NULL;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy_(this->root, other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  delete_(root);
  copy_(this->root, rhs.root);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  delete_(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> best = root->point;
    WontYouBeMyNeighbor(root, query, best, 0);
    return best;
}

template <int Dim>
void KDTree<Dim>::WontYouBeMyNeighbor(const KDTreeNode* kdNode,const Point<Dim>& query, 
                                      Point<Dim>& currentBest, int plane) const{
  if (kdNode == NULL){
    return;
  }
  KDTreeNode* nearer; 
  KDTreeNode* further;
  if (smallerDimVal(query, kdNode->point, plane)){
    nearer = kdNode->left;
    further = kdNode->right;
  }else {
    nearer = kdNode->right;
    further = kdNode->left;
  }

  WontYouBeMyNeighbor(nearer, query, currentBest , (plane + 1) % Dim);
  if (shouldReplace(query, currentBest, kdNode->point)){
    currentBest = kdNode->point;
  }
  double radii = 0;
  for (int i=0; i<Dim; i++){
    radii += pow(currentBest[i]-query[i],2);
  }
  double dist = pow(kdNode->point[plane] - query[plane],2);
  if (radii >= dist){
    WontYouBeMyNeighbor(further, query, currentBest, (plane + 1) % Dim);
  }
}
