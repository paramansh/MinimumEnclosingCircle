To run:
g++ -I$LEDAROOT/incl -L$LEDAROOT minimum_enclosing_circle.cpp -lleda -lX11 -lm

circle.txt -> output minmum enclosing circle from minimum_enclosing_circle.cpp
points.txt -> set of points used in construction of the above circle.

visualize.ipynb -> plots circle, points in the files circles.txt and points.txt

minimum_enclosing_circle_stats.cpp -> util file for generating stats
stats.sh -> outputs the average number of points which come outside the circle, that is the number of expansions.
