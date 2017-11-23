#include <iostream>
#include <algorithm>

using namespace std;

struct Point
{
	float x;
	float y;
	Point(){}
	Point(float xx, float yy)
	{
		this->x = xx;
		this->y = yy;
	}
};

Point lineLineIntersection(Point A, Point B, Point C, Point D)
{
	//	Ecuatia dreptei AB reprezentata ca a1x + b1y = c1
	float a1 = B.y - A.y;
	float b1 = A.x - B.x;
	float c1 = a1*(A.x) + b1*(A.y);

	// Ecuatia dreptei CD reprezentata ca a2x + b2y = c2
	float a2 = D.y - C.y;
	float b2 = C.x - D.x;
	float c2 = a2*(C.x) + b2*(C.y);

	float determinant = a1*b2 - a2*b1;

	float x = (b2*c1 - b1*c2) / determinant;
	float y = (a1*c2 - a2*c1) / determinant;
	return Point(x, y);

}
bool onSegment(Point p, Point q, Point r)
{
	// Primeste 3 puncte coliniare si verifica daca punctul q se afla pe segmentul determinat de punctele p si r
	//	! - Punctele trebuie sa fie coliniare

	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

// Test de orientare
// 0 --> coliniare
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// Verificam daca punctele se intersecteaza
int doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Toate orientarile de care avem nevoie pt a verifica intersectia
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);


	if (o1 != o2 && o3 != o4)
		return 1;	// Se intersecteaza

    if(!orientation(p1,p2,q1) && !orientation(p1,q2,q1))
        return 0;   // Sunt coliniare

	// p1, q1 si p2 sunt coliniare si p2 se afla pe segmentul p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return 1;

	// p1, q1 si q2  sunt coliniare si q2 se afla pe segmentul p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return 1;

	// p2, q2 si p1 sunt coliniare si p1se afla pe segmentul p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return 1;

	// p2, q2 si q1 sunt coliniare si q1se afla pe segmentul p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return 1;

	return -1; // Nu se intersecteaza
}

int main()
{
	 Point p1(0,0);
     Point q1(2,2);
	 Point p2(3,3);
	 Point q2(1,1);
    int result = doIntersect(p1, q1, p2, q2);
	if (result == 1)
	{
		// Determinam punctele de intersectie
		Point result = lineLineIntersection(p1, q1, p2, q2);
		cout << " Segmentele se intersecteaza in punctul : " << result.x << " " << result.y;

	} else if(result == 0)
	{
	    cout << "Segmentele sunt coliniare.\n";
	    if(onSegment(p1,p2,q1) && onSegment(p1,q2,q1))
        {
            //cout << "Intersectia este segmentul [p2,q2]";
            cout << "Intersectia este segmentul [(" << p2.x << "," << p2.y << ")(" << q2.x << "," << q2.y << ")]";
        }
        else if(onSegment(p2,p1,q2) && onSegment(p2,q1,q2))
        {
            //cout << "Intersectia este segmentul [p1,q1]";
            cout << "Intersectia este segmentul [(" << p1.x << "," << p1.y << ")(" << q1.x << "," << q1.y << ")]";
        }
        else if (onSegment(p1,p2,q1) && !onSegment(p1,q2,q1))
        {
            //cout << "Intersectia este segmentul [p2,q1]";
            cout << "Intersectia este segmentul [(" << p2.x << "," << p2.y <<")(" << q1.x << "," << q1.y << ")]\n";
        }
        else if(onSegment(p2,p1,q2) && !onSegment(p2,q1,q2))
        {
            //cout << "Intersectia este segmentul [p1,q2]";
            cout << "Intersectia este segmentul [(" << p1.x << "," << p1.y << ")(" << q2.x << "," << q2.y << ")]\n";
        }
	} else
	{
        cout << "Segmentele nu se intersecteaza.\n";
	}

	return 0;
}
