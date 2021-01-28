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
# plot "./out/outputTriangles.txt" with lines
set terminal png size 4096,4096 enhanced background rgb 'white'
set view 75,25,1
rgb(r,g,b) = 65536*int(r) + 256*int(g) + int(b)
# splot "./out/outputTriangles.txt" using 1:2:3:(rgb($4,$5,$6)) with lines lc rgb variable
# set hidden3d back offset 0 trianglepattern 3 undefined 1 altdiagonal bentover
# set border 0x7F linecolor rgb "#555555"
set view equal xyz
# set style fill transparent solid 0.5 noborder
set pm3d nohidden3d
splot "./out/outputTriangles.txt" using 1:2:3:(rgb($4,$5,$6)) with lines lc rgb variable


set terminal gif size 1000,1000 animate delay 5 loop 0 optimize
set output "./out/rot.gif"

n = 1500
do for [i=1:n] {
   set view 60, i*360.0/n
   splot "./out/outputTriangles.txt" using 1:2:3:(rgb($4,$5,$6)) with lines lc rgb variable notitle
}

# set output "./out/Hilbert_1.png"
# plot "./out/Hilbert_1.txt" with lines
# set output "./out/Hilbert_2.png"
# plot "./out/Hilbert_2.txt" with lines
# set output "./out/Hilbert_3.png"
# plot "./out/Hilbert_3.txt" with lines
# set output "./out/Hilbert_4.png"
# plot "./out/Hilbert_4.txt" with lines
# set output "./out/Hilbert_5.png"
# plot "./out/Hilbert_5.txt" with lines
# set output "./out/Hilbert_6.png"
# plot "./out/Hilbert_6.txt" with lines
# set output "./out/Hilbert_7.png"
# plot "./out/Hilbert_7.txt" with lines