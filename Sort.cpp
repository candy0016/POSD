#include "include/Sort.h"
#include <list>
#include "include/Shapes.h"

using namespace std;

struct ComparePerimeter{
	bool operator()(Shape *s1, Shape *s2) { return s1->perimeter() < s2->perimeter(); }
};

struct CompareArea{
	bool operator()(Shape *s1, Shape *s2) { return s1->area() < s2->area(); }
};

struct CompareCompactness{
	bool operator()(Shape *s1, Shape *s2) { 
		return (s1->area()/s1->perimeter()) < (s2->area()/s2->perimeter()); 
	}
};

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
	shapeList->sort(ComparePerimeter());
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
	shapeList->sort(ComparePerimeter());
	shapeList->reverse();
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList){
	shapeList->sort(CompareArea());
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList){
	shapeList->sort(CompareArea());
	shapeList->reverse();
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList){
	shapeList->sort(CompareCompactness());
}

