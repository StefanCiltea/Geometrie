// GrahamScan - Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Point {
public:
	double x, y;

	Point(double vx, double vy)
	{
		x = vx;
		y = vy;
	}
	Point()
	{
		x = y = 0.0;
	}
	bool operator ==(Point a)
	{
		return (a.x == this->x && a.y == this->y);
	}
	friend ostream& operator << (ostream& o, Point a)
	{
		o << "("<< a.x << "," << a.y << ")  ";
		return o;
	}
};

Point p0;	// Global variable of the bottom most point, global because used in compare function

int orientation(const Point a, const Point b, const Point c)
{
	/*
		Return value: 2 -> If left turn
					  1 -> If right turn
					  0 -> Colinear
	*/

	Point vab(b.x - a.x, b.y - a.y);
	Point vbc(c.x - b.x, c.y - b.y);

	double val = vab.x * vbc.y - vbc.x * vab.y;			// Cross product of the 2 vectors
	if (val == 0) return val;

	return ((val > 0) ? 2 : 1);

}

double distanceFromP0(const Point a)
{
	return ((p0.x - a.x)*(p0.x - a.x) + (p0.y - a.y)*(p0.y - a.y));		// ! Not the real square root but a valid distance function
}

int compare(const void* va, const void* vb)
{
	Point *a = (Point *)va;
	Point *b = (Point *)vb;

	int o = orientation(p0, *a, *b);

	if (!o)
	{
		return ((distanceFromP0(*a) <= distanceFromP0(*b)) ? -1 : 1);
	}

	return ((o == 2) ? -1 : 1);

}

// Utility
Point nextToTopList(list<Point> l)
{
	l.pop_back();
	return l.back();
}

list<Point> GrahamScan(Point *v,int vsize)
{
	list<Point> result;

	// We find the bottom most point and assign it to p0
	Point pmin = v[0];
	int mpos = 0;
	for (int i = 1; i < vsize; i++)
	{
		if (v[i].y < pmin.y)
		{
			mpos = i;
			pmin = v[i];
		}
		else if ((v[i].y == pmin.y) && (v[i].x < pmin.x))
		{
			mpos = i;
			pmin = v[i];
		}
	}

	// Swap
	Point aux = v[0];
	v[0] = v[mpos];
	v[mpos] = aux;

	p0 = pmin;

	// Now we sort the array of points according to polar angle with respect to p0
	qsort(v + 1, vsize - 1, sizeof(Point), compare);


	// Now we get rid of colinear points with p0 and chose the one that is at the largest distance from p0
	mpos = 1;
	for (int i = 1; i < vsize; i++)
	{
		while (i < vsize - 1 && orientation(p0, v[i], v[i + 1]) == 0)
			i++;

		v[mpos] = v[i];
		mpos++;							// Update the size
	}

	vsize = mpos;

	result.push_back(v[0]);
	result.push_back(v[1]);

	// Begin iteration
	for (int i = 2; i < vsize; i++)
	{
		while(orientation(nextToTopList(result), result.back(),v[i]) != 2)
		{
			// Keep removing back while it forms right turn with v[i]
			result.pop_back();
		}
		result.push_back(v[i]);
	}

	return result;
}

int main()
{
	Point pts[] = { { 0, 0 },{ 2,2 },{ 3, 3 },{1,1} };
	int n = sizeof(pts) / sizeof(Point);
	vector<Point> points(pts,pts+n);

	list<Point> l = GrahamScan(pts,n);
	//cout << l.size();
	//cout << n;
	if (l.size() == 2 || l.size() == 3)
	{
		cout << "I : ";
		for (list<Point>::iterator it = l.begin(); it != l.end(); it++)
			cout << (*it) << " ";

		cout << endl << "J : ";

		for (int i = 0; i < n; i++)
		{
			bool ok = false;
			for (list<Point>::iterator it = l.begin(); it != l.end(); it++)
				if (points[i] == (*it))
				{
					ok = true;
					break;
				}

			if (!ok)
				cout << points[i] << " ";
		}

	}
	else if (l.size() == 4)
	{
	    Point p4 = l.back();
	    l.pop_back();
	    Point p3 = l.back();
	    l.pop_back();
	    Point p2 = l.back();
	    l.pop_back();
	    Point p1 = l.back();
        l.pop_back();

		cout << "I : " << p1 << p3 << " " << endl;

		cout << endl << "J : " << p2 << " " << p4 << endl;


	}

    return 0;
}

