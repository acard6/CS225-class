/* Your code here! */
#include "maze.h"
#include "cs225/PNG.h"
#include "dsets.h"
#include <math.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <map>


SquareMaze::SquareMaze(){
    width_ = 0;
    height_ = 0;
    dset = new DisjointSets();
    walls = new vector<pair<bool, bool>>;
}

SquareMaze::~SquareMaze(){
    height_ = 0;
    width_ = 0;
    delete dset;
    dset = NULL;
    delete walls;
    walls = NULL;
}

void SquareMaze::makeMaze(int width, int height){
    width_ = width;
    height_ = height;
    int size = width_ * height_;
    dset->addelements(size);
    for (int i=0; i<size; i++){
        walls->push_back(pair<bool,bool> (true, true));
    }

    /**
    for (int i=0; i<size-1; i++){
        vector<int> dir;
        
        if ( (i+1) % width_ != 0 && (dset->find(i+1) != dset->find(i))){
            dir.push_back(0);
        }
        if (!(i+width_ >= size) && (dset->find(i+width_) != dset->find(i))){ 
            dir.push_back(1);
        }
        if (!(i % width_ != 0) && (dset->find(i-1) != dset->find(i))){
            dir.push_back(2);
        }
        if (!(i < width_) && (dset->find(i-width_) != dset->find(i))){
            dir.push_back(3);
        }

        if (dir.size() == 0){continue;}
        int path = rand() % dir.size();

        if (dir[path] == 0){
            dset->setunion(i, i+1);
            (*walls)[i].first = false;
        }else if (dir[path] == 1){
            dset->setunion(i, i+width_);
            (*walls)[i].second = false;
        }else if (dir[path] == 2){
            dset->setunion(i, i-1);
            (*walls)[i-1].first = false;
        }else if (dir[path] == 3){
            dset->setunion(i, i-width_);
            (*walls)[i-width].second = false;
        }
    }*/

    for (int i=0; i<size-1; i++){
        int x = rand() % width_;
        int y = rand() % height_;
        bool exists = rand() % 2;
        if (exists){
            if ((*walls)[x+y*width_].first && x<width_-1 && 
            (dset->find(x+y*width_) != dset->find(x+y*width_+1))){
                (*walls)[x+y*width_].first = false;
                dset->setunion(dset->find(x+y*width_), dset->find(x+y*width_+1));
            }
        }else{
            if ((*walls)[x+y*width_].second && y<height_-1 && 
            (dset->find(x+y*width_) != dset->find(x+(y+1)*width_))){
                (*walls)[x+y*width_].second = false;
                dset->setunion(dset->find(x+y*width_), dset->find(x+(y+1)*width_));            
            }
        }
    }

}	

bool SquareMaze::canTravel(int x, int y, int dir) const{
    if (dir == 0){
        if (x >= width_-1){return false;}
        return !(*walls)[x+y*width_].first;
    }
    if (dir == 1){
        if (y >= height_-1){return false;}
        return !(*walls)[x+y*width_].second;
    }
    if (dir == 2){
        if (x <1){return false;}
        return !(*walls)[x+y*width_-1].first;
    }
    if (dir == 3){
        if (y<1){return false;}
        return !(*walls)[x+(y-1)*width_].second;
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if (dir == 1){
        (*walls)[x+y*width_].second = exists;
    }
    else {
        (*walls)[x+y*width_].first = exists;
    }
}

vector<int> SquareMaze::solveMaze(){
int x, y, curr;
    vector<int> prev;
    vector<int> length;
    queue<int> q;
    prev.push_back(0);
    length.push_back(0);
    for (int i=0; i<width_ * height_; i++){
        prev.push_back(-1);
        length.push_back(0);
    }
    q.push(0);
    while (!q.empty()){
        curr = q.front();
        x = curr / width_;
        y = curr % width_;
        q.pop();
        if (canTravel(x,y,0)){
            if (prev[curr+1] == -1){
                q.push(curr+1);
                prev[curr+1] = curr;
                length[curr+1] = length[curr] + 1;
            }
        }
        if (canTravel(x,y,1)){
            if (prev[curr+width_] == -1){
                q.push(curr+width_);
                prev[curr+width_] = curr;
                length[curr+width_] = length[curr] + 1;
            }            
        }
        if (canTravel(x,y,2)){
            if (prev[curr-1] == -1){
                q.push(curr-1);
                prev[curr-1] = curr;
                length[curr-1] = length[curr] + 1;
            }
        }
        if (canTravel(x,y,3)){
            if (prev[curr-width_] == -1){
                q.push(curr-width_);
                prev[curr-width_] = curr;
                length[curr-width_] = length[curr] + 1;
            }
        }
    }
    int longest = width_ *(height_ - 1);
    for (int k=0; k<width_; k++){
        if (length[width_ * (height_ - 1) + k] > length[longest]){
            longest = width_ * (height_ - 1) + k;
        }
    }
    vector<int> soln;
    curr = longest;
    while (curr != 0){
        if (prev[curr] == curr - 1){
            soln.push_back(0);
        }
        if (prev[curr] == curr - width_){
            soln.push_back(1);
        }
        if (prev[curr] == curr + 1){
            soln.push_back(2);
        }
        if (prev[curr] == curr + width_){
            soln.push_back(3);
        }
        curr = prev[curr];
    }
    reverse(soln.begin(), soln.end());
    return soln;

}

PNG* SquareMaze::drawMaze() const{
    PNG* image = new PNG(width_ * 10 + 1, height_ * 10 + 1);
    for (int i=0; i<width_; i++){
        for (int j=0; j<height_; j++){
            if (j == 0){
                for (unsigned k=0; k<10; k++){
                    if ((i*10+k)<1 || (i*10+k)>9){
                        HSLAPixel& pixel = image->getPixel(i*10+k,0);
                        pixel.l = 0;
                    }
                }
            }
            if (i == 0){
                for (unsigned k=0; k<10; k++){
                    HSLAPixel& pixel = image->getPixel(0, 10*j+k);
                    pixel.l = 0;
                }
            }
            if (!canTravel(i,j,0)){
                for (unsigned k=0; k<=10; k++){
                    HSLAPixel& pixel = image->getPixel((i+1)*10, j*10+k);
                    pixel.l = 0;
                }
            }
            if (!canTravel(i,j,1)){
                for (unsigned k=0; k<=10; k++){
                    HSLAPixel& pixel = image->getPixel(i*10+k, (j+1)*10);
                    pixel.l = 0;
                }
            }
        }
    }
    return image;
}

PNG * SquareMaze::drawMazeWithSolution(){
    PNG* image = drawMaze();
    vector<int> soln = solveMaze();
    pair<int, int> p(5,5);
    for (auto i: soln){
        if (i == 0){
            for (int k=0; k<10; k++){
                HSLAPixel& pixel = image->getPixel(p.first, p.second);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                p.first++;
            }
        }
        if (i == 1){
            for (int k=0; k<10; k++){
                HSLAPixel& pixel = image->getPixel(p.first, p.second);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                p.second++;
            }
        }
        if (i == 2){
            for (int k=0; k<10; k++){
                HSLAPixel& pixel = image->getPixel(p.first, p.second);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                p.first--;            
            }
        }
        if (i == 3){
            for (int k=0; k<10; k++){
                HSLAPixel& pixel = image->getPixel(p.first, p.second);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                p.second--;    
            }
        }
    }
    HSLAPixel& pixel = image->getPixel(p.first, p.second);
    pixel.h = 0;
    pixel.s = 1;
    pixel.l = 0.5;

    p.first -= 4;
    p.second += 5;
    for (int i=p.first; i<p.first+9; i++){
        HSLAPixel& pixel = image->getPixel(i, height_ * 10);
        pixel.l = 1;
    }
    return image;
}
