#include <LEDA/geo/point.h>
#include <LEDA/geo/random_point.h>
#include <vector>
#include <LEDA/geo/circle.h>
#include <LEDA/core/array.h>
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

circle min_enclose2(list <point> &L, point def_pt1)
{
    // last element of L1 is the difining point
    point def_pt2 = L.pop_back();
    //L.permute(); // not required    
    //cout << L << endl;
    circle C;
    C = dia_circle(def_pt1, def_pt2);
    for (int i = 0; i < L.length(); i++)
    {
        point new_p = L[L.get_item(i)];
        if (C.outside(new_p))
        {
            if (is_acute(def_pt1, def_pt2, new_p))
                C = circle(def_pt1, def_pt2, new_p);
        }
    }
    return C;
}
circle min_enclose1(list <point> &L)
{
    // last element of L1 is the difining point
    point def_pt = L.pop_back();
    L.permute();    
    //cout << L << endl;

    circle C;
    point pt1 = L[L.get_item(0)];
    C = dia_circle(def_pt, pt1);

    for (int i = 1; i < L.length(); i++)
    {
        point new_p = L[L.get_item(i)];
        if (C.outside(new_p))
        {
            list <point> Lcpy = L;
            list <point> L1, L2;
            list_item it = Lcpy.get_item(i);
            Lcpy.split(it, L1, L2, behind);
            //cout << L1 << endl;
            //cout << L << endl;
            C = min_enclose2(L1, def_pt);
            //cout << "One: " << i  << " " << C.radius() << endl;
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
    array <point> al(L.length());
    list_item it = L.first();
    int cnt = 0;
    for (it = L.first(); it != NULL; it = L.succ(it))
    {
        al[cnt] = L[it];
        cnt++;
    }
    cout << "Inserted into array: " << al.high() << endl;
    std::ofstream myfile;
    myfile.open("points.txt");
    for (int i = 0; i < L.length(); i++)
    {
        point p = al[i];
        myfile << p.xcoord() << " " << p.ycoord() << endl; 
    }
    myfile.close();
    //al.permute();//TODO
    point p1 = al[0];
    point p2 = al[1];
    circle C = dia_circle(p1, p2);
    //cout << C.center() << endl;
    int outside_pts = 0;
    for (int i = 2; i < L.length(); i++)
    {
        if (i % 10000 == 0)
        {
            cout << "Completed: " << i << " Points Outside: " << outside_pts << endl;
        }
        point new_p = al[i];
        if (C.outside(new_p))
        {
            outside_pts++;
            array <point> al2(i+1);
            for (int j = 0; j <= i; j++)
                al2[j] = al[j];
            cout << al << endl << al2 << endl;
            list <point> Lcpy = L;
            list <point> L1, L2;
            list_item it = Lcpy.get_item(i);
            Lcpy.split(it, L1, L2, behind);
            //cout << L1 << endl;
            //cout << L << endl;
            C = min_enclose1(L1);
            //cout << "Circle after inserting " << ": " << C.center() << ", " << C.radius() << endl;
        }
    }
    myfile.open("circle.txt");
    myfile << C.center().xcoord() << " " << C.center().ycoord() <<" " << C.radius(); 
}
