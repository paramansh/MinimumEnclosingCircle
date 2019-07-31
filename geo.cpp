#include <LEDA/geo/point.h>
#include <LEDA/geo/random_point.h>
#include <vector>
#include <LEDA/geo/circle.h>
#include <LEDA/geo/segment.h>
#include <assert.h>
#include <math.h>
#include <fstream>
#include <climits>
#if defined(LEDA_STD_IO_HEADERS)
using std::cout;
using std::cin;
using std::flush;
using std::endl;
#endif

using namespace leda;

bool is_acute(point a, point b, point c)
{
    float angle;
    segment s1, s2, s3;
    s1 = segment(a, c);
    s2 = segment(a, b);
    angle = s1.angle(s2);
    //cout << angle*180/LEDA_PI<< endl;
    if (angle >= LEDA_PI/2 && angle <= LEDA_PI * 3/2)
        return false;
    s1 = segment(b, a);
    s2 = segment(b, c);
    angle = s1.angle(s2);
    //cout << angle*180/LEDA_PI<< endl;
    //if (angle >= LEDA_PI/2)
    if (angle >= LEDA_PI/2 && angle <= LEDA_PI * 3/2)
        return false;
    s1 = segment(c, a);
    s2 = segment(c, b);
    angle = s1.angle(s2);
    //cout << angle*180/LEDA_PI<< endl;
    //if (angle >= LEDA_PI/2)
    if (angle >= LEDA_PI/2 && angle <= LEDA_PI * 3/2)
        return false;
    return true;
}

circle dia_circle(point a, point b)
{
    point centre = midpoint(a,b);
    circle C(centre, a);
    return C;
}

circle min_enclose2(std:: vector <point> &L, point def_pt1)
{
    // last element of L1 is the difining point
    point def_pt2 = L.back();
    L.pop_back();
    //L.permute(); // not required    
    //cout << L << endl;
    circle C;
    C = dia_circle(def_pt1, def_pt2);
    for (int i = 0; i < L.size(); i++)
    {
        point new_p = L[i];
        if (C.outside(new_p))
        {
            if (is_acute(def_pt1, def_pt2, new_p))
                C = circle(def_pt1, def_pt2, new_p);
        }
    }
    return C;
}
circle min_enclose1(std:: vector <point> &L)
{
    // last element of L1 is the difining point
    point def_pt = L.back();
    L.pop_back();
    std::random_shuffle(L.begin(), L.end());    
    //cout << L << endl;

    circle C;
    point pt1 = L[0];
    C = dia_circle(def_pt, pt1);

    for (int i = 1; i < L.size(); i++)
    {
        point new_p = L[i];
        if (C.outside(new_p))
        {
            std:: vector <int> :: iterator first, last;
            first = L.begin();
            last = L.begin() + i;
            std:: vector <point> tempvec(first, last);
            C = min_enclose2(tempvec, def_pt);
        }
    }
    return C;
}
int main() 
{
    list <point> L;
    int n;
    cout << "Enter Number of Points: ";
    cin >> n;
    //cout << "Enter square size: ";
    int sz;
    //cin >> sz;
    sz = 100000;
    random_points_in_square(n,sz, L);
    std::vector <point> vl;
    list_item it = L.first();
    for (it = L.first(); it != NULL; it = L.succ(it))
    {
        vl.push_back(L[it]);
    }
    cout << "Inserted into vector: " << vl.size() << endl;
    std::ofstream myfile;
    myfile.open("points.txt");
    for (int i = 0; i < vl.size(); i++)
    {
        point p = vl[i];
        myfile << p.xcoord() << " " << p.ycoord() << endl; 
    }
    myfile.close();
    std::random_shuffle(vl.begin(), vl.end());
    point p1 = vl[0];
    point p2 = vl[1];
    circle C = dia_circle(p1, p2);
    //cout << C.center() << endl;
    int outside_pts = 0;
    for (int i = 2; i < vl.size(); i++)
    {
        if (i % 10000 == 0)
        {
            cout << "Completed: " << i << " Points Outside: " << outside_pts << endl;
        }
        point new_p = vl[i];
        if (C.outside(new_p))
        {
            outside_pts++;
            std:: vector <int> :: iterator first, last;
            first = vl.begin();
            last = vl.begin() + i;
            std:: vector <point> tempvec(first, last);
            C = min_enclose1(tempvec);
        }
    }
    myfile.open("circle.txt");
    myfile << C.center().xcoord() << " " << C.center().ycoord() <<" " << C.radius(); 
}
