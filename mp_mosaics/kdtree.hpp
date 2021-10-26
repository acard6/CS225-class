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
      //Swallowing load and loads of compiler errors
      return;
    }
    else{
      //vector<*Point<Dim>> ptrPoints;
      int middle = floor((newPoints.size() - 1) / 2);
      Point<Dim> midPoint = newPoints[middle];

    }
}

template <int Dim>
vector<Point<Dim>> KDTree<Dim>::KDN(const vector<Point<Dim>>& newPoints, int dim){
  if (newPoints.size() != 0){
    return;
  }
  else{
    return;
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

