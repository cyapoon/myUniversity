#include <iostream>
#include "PointSet.h"
using namespace std;

PointSet::PointSet(int capacity)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's conversion constructor" << endl;

  // TODO #1: add your code here
  this->numPoints = 0;
  
  this->capacity = capacity;
  if(this->capacity == 0)
  {
    this->points = nullptr;
  }
  else
  {
    this->points = new Point[this->capacity];
  }

}

PointSet::PointSet(const Point points[], int numPoints)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's other constructor" << endl;

  // TODO #2: add your code here
  this->numPoints = numPoints;
  this->capacity = numPoints;
  this->points = new Point[this->capacity];
  for(int i = 0; i < numPoints;i++)
  {
    this->points[i] = points[i];
  }
  

}

PointSet::PointSet(const PointSet& s)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's copy constructor" << endl;

  // TODO #3: add your code here
  this->capacity = s.capacity;
  this->numPoints = s.numPoints;
  this->points = new Point[this->capacity];
  for(int i = 0; i < this->numPoints; i++)
  {
    this->points[i] = s.points[i]; 
  }

}

PointSet::~PointSet()
{
  // TODO #4: add your code here
  if(this->points != nullptr)
  {
    delete[] this->points;
    this->points = nullptr;
  }
  

}

void PointSet::addPoint(const Point& p)
{
  // TODO #5: add your code here
  if(this->numPoints < this->capacity)
  {
    this->points[numPoints] = p;
    this->numPoints += 1;
  }
  else
  {
    cout << "Insufficient array space" << endl;
  }

}

void PointSet::removeLastPoint()
{
  // TODO #6: add your code here
  if(this->numPoints == 0)
  {
    cout <<  "No points" << endl;
  }
  else
  {
    
    this->numPoints -= 1;
  }

}

// Return true if the all the points in the point set is collinear; return false otherwise
bool PointSet::isCollinear() const
{
  // TODO #7: add your code here
  if(this->numPoints <=2)
  {
    return true;
  }
  else
  {
    bool result= 1;
    for(int i = 0;i < this->numPoints-2; i++)
    {
      result *= isCollinear_3points(this->points[i], this->points[i+1], this->points[i+2]);
    }
    return result;
  }

}

// return true if 3 given points are on the same straight line
bool PointSet::isCollinear_3points(const Point p1, const Point p2, const Point p3) const
{
  // TODO #8: add your code here
  double p1_x = p1.getX();
  double p1_y = p1.getY();
  double p2_x = p2.getX();
  double p2_y = p2.getY();
  double p3_x = p3.getX();
  double p3_y = p3.getY();
  double area = 0.5*(p1_x*(p2_y-p3_y)+p2_x*(p3_y-p1_y)+p3_x*(p1_y-p2_y));
  if(area == 0)
  {
    return true;
  }
  else
  {
    return false;
  }

}

void PointSet::print() const
{
  // This function is already completed.
  if (numPoints == 0) {
    cout << "The PointSet is empty!" << endl;
    return;
  }
  cout << "Number of points: " << numPoints << endl;;
  cout << "points: " << endl;
  for(int i = 0; i < numPoints; i++)
  {
    points[i].print();
    cout << endl;
  }
}
