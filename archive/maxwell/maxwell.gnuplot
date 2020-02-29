set ylabel 'log_{10}(N)'
set xlabel 'v^2, eps/m'
set title 'maxwell distribution checking plot, bin=5 sqrt(eps/m)'
set yrange[-0.5:4]

f(x) = a * x + b

fit f(x) 'maxwell.plotdata' u 1:2 via a, b

plot 'maxwell.plotdata' u 1:2, f(x)

pause -1