set xlabel 'log_{10}(1/upf)'
set ylabel 'log_{10}(<E^2>-<E>^2)'
set title 'dispersion vs ticktime plot'

f(x) = a * x + b
#g(x) = c * x + d

fit f(x) 'energy_dispersion_pured.plotdata' u 1:2 via a, b
#fit g(x) 'energy_dispersion.plotdata.old' u 1:2 via c, d

#plot 'energy_dispersion.plotdata' u 1:2:3 w yerrorbars, 'energy_dispersion.plotdata.old' u 1:2:3 w yerrorbars, f(x), g(x)
plot 'energy_dispersion.plotdata' u 1:2:3 w yerrorbars, f(x)

pause -1