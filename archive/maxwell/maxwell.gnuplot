set ylabel 'log_{10}(N)'
set xlabel 'v^2, eps/m'
set title 'maxwell distribution checking plot, bin=5 sqrt(eps/m)'
set yrange[-0.5:4]

plot 'maxwell.plotdata' u 1:2

pause -1