reset
# set terminal png size 2048,2048 enhanced background rgb 'white'
# set output "./out/test.png"
# test
# set output "./out/vertices.png"
# set xrange[-100000:1100000]
# set yrange[-100000:1100000]
set xrange[-100:1100]
set yrange[-100:1100]
set xlabel "x"
set ylabel "y"
# set title "Punkty w 3D"
# plot "./out/outputVertices.txt"
# set output "./out/test_triangles.png"
# plot "./out/test.txt" with lines
set output "./out/triangles.png"
set terminal png size 1250,1250 enhanced background rgb 'white'
set palette defined (0 'black', 0.25 '#221103', 0.34 '#442206', 0.38 '#663311', 0.4 '#884415', 0.42 '#AA551C', 0.45 '#CC6622', 0.5 '#EE7735', 0.56 '#FFFF77', 1 'white')
stats './out/outputVerticesDensity.txt' using 5
set logscale cb
set cbrange[STATS_min:STATS_max]
set view map
# set cbrange[2e-12:2e-11]
splot "./out/outputVerticesDensity.txt" using 1:2:5 with pm3d palette
# set view 60,45
# set sample 5000,5000; set isosample 5000,5000
# set pm3d depthorder noborder interpolate 2,2
# # set pm3d noclipcb
# set style fill transparent solid 0.5
# # set hidden3d
# set cbrange[0:50]
# set cblabel "point density"
# splot "./out/outputVerticesDensity.txt" with pm3d # with points pt 7 ps 0.5 lc palette
# plot "./out/outputTriangles.txt" with lines
# set terminal png size 4096,4096 enhanced background rgb 'white'
# set view 75,25,1
# rgb(r,g,b) = 65536*int(r) + 256*int(g) + int(b)
# splot "./out/outputTriangles.txt" using 1:2:3:(rgb($4,$5,$6)) with lines lc rgb variable
# set hidden3d back offset 0 trianglepattern 3 undefined 1 altdiagonal bentover
# set border 0x7F linecolor rgb "#555555"
# set view equal xyz
# set style fill transparent solid 0.5 noborder
# set pm3d nohidden3d
# splot "./out/outputTriangles.txt" using 1:2:3:(rgb($4,$5,$6)) with lines lc rgb variable


# set terminal gif size 1000,1000 animate delay 5 loop 0 optimize
# set output "./out/rot.gif"

# n = 1500
# do for [i=1:n] {
#    set view 60, i*360.0/n
#    splot "./out/outputTriangles.txt" using 1:2:3:(rgb($4,$5,$6)) with lines lc rgb variable notitle
# }

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