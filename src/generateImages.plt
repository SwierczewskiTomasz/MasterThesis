reset
set terminal png size 2048,2048 enhanced background rgb 'white'
set output "./out/test.png"
test
set output "./out/vertices.png"
set xrange[-10:110]
set yrange[-10:110]
set xlabel "x"
set ylabel "y"
set title "Punkty w 2D"
plot "./out/outputVertices.txt"
set output "./out/test_triangles.png"
plot "./out/test.txt" with lines
set output "./out/triangles.png"
set terminal png size 2048,2048 enhanced background rgb 'white'
plot "./out/outputTriangles.txt" with lines