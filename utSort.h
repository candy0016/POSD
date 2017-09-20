#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include <sstream>
#include <string>

using namespace std;

TEST (Sort, sortByIncreasingPerimeter) {
	Rectangle rect1(3, 8, 2, 10); //area 20 peri 24
	Rectangle rect2(1, 10, 5, 6); //area 30 peri 22
	Triangle tri({1, 1}, {4, 1}, {4, 5}); //area 6 peri 12

	list<Shape *> shapes;
  	shapes.push_back(&rect1);
  	shapes.push_back(&rect2);
  	shapes.push_back(&tri);

	Sort sortT;
	sortT.sortByIncreasingPerimeter(&shapes);

	stringstream ss1, ss2;
	ss1 << "12 22 24 ";

	for(list<Shape*>::iterator it=shapes.begin(); it!=shapes.end(); it++){
		ss2 << (*it)->perimeter() << " ";
	}

	//cout<<"This should be number(12 22 24):  "<<ss2;
	ASSERT_EQ(ss1.str(), ss2.str());
}

TEST (Sort, sortByDecreasingPerimeter) {
    Rectangle rect1(3, 8, 2, 10); //area 20 peri 24
	Rectangle rect2(1, 10, 5, 6); //area 30 peri 22
	Triangle tri({1, 1}, {4, 1}, {4, 5}); //area 6 peri 12

	list<Shape *> shapes;
  	shapes.push_back(&rect1);
  	shapes.push_back(&rect2);
  	shapes.push_back(&tri);

	Sort sortT;
	sortT.sortByDecreasingPerimeter(&shapes);

	stringstream ss1, ss2;
	ss1 << "24 22 12 ";

	for(list<Shape*>::iterator it=shapes.begin(); it!=shapes.end(); it++){
		ss2 << (*it)->perimeter() << " ";
	}

	ASSERT_EQ(ss1.str(), ss2.str());

}

TEST (Sort, sortByIncreasingArea) {
    Rectangle rect1(3, 8, 2, 10); //area 20 peri 24
	Rectangle rect2(1, 10, 5, 6); //area 30 peri 22
	Triangle tri({1, 1}, {4, 1}, {4, 5}); //area 6 peri 12

	list<Shape *> shapes;
  	shapes.push_back(&rect1);
  	shapes.push_back(&rect2);
  	shapes.push_back(&tri);

	Sort sortT;
	sortT.sortByIncreasingArea(&shapes);

	stringstream ss1, ss2;
	ss1 << "6 20 30 ";

	for(list<Shape*>::iterator it=shapes.begin(); it!=shapes.end(); it++){
		ss2 << (*it)->area() << " ";
	}

	ASSERT_EQ(ss1.str(), ss2.str());
}

TEST (Sort, sortByDecreasingArea) {
    Rectangle rect1(3, 8, 2, 10); //area 20 peri 24
	Rectangle rect2(1, 10, 5, 6); //area 30 peri 22
	Triangle tri({1, 1}, {4, 1}, {4, 5}); //area 6 peri 12

	list<Shape *> shapes;
  	shapes.push_back(&rect1);
  	shapes.push_back(&rect2);
  	shapes.push_back(&tri);

	Sort sortT;
	sortT.sortByDecreasingArea(&shapes);

	stringstream ss1, ss2;
	ss1 << "30 20 6 ";

	for(list<Shape*>::iterator it=shapes.begin(); it!=shapes.end(); it++){
		ss2 << (*it)->area() << " ";
	}

	ASSERT_EQ(ss1.str(), ss2.str());
}

TEST (Sort, sortByIncreasingCompactness) {
    Rectangle rect1(3, 8, 3, 5); //area 15 peri 16   com  0.9375
	Rectangle rect2(1, 10, 10, 10); //area 100 peri 40   com  2.5
	Triangle tri({1, 1}, {4, 1}, {4, 5}); //area 6 peri 12   com 0.5

	list<Shape *> shapes;
  	shapes.push_back(&rect1);
  	shapes.push_back(&rect2);
  	shapes.push_back(&tri);

	Sort sortT;
	sortT.sortByIncreasingCompactness(&shapes);

	stringstream ss1, ss2;
	ss1 << "0.5 0.9375 2.5 ";

	for(list<Shape*>::iterator it=shapes.begin(); it!=shapes.end(); it++){
		ss2 << ((*it)->area() / (*it)->perimeter()) << " ";
	}

	ASSERT_EQ(ss1.str(), ss2.str());
}

#endif
