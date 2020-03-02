f(x) = a * x + b
g(x) = c * x + d

fit f(x) 'diffusion_1.plotdata' u 1:2 via a, b
fit g(x) 'diffusion_2.plotdata' u 1:2 via c, d

plot 'diffusion.plotdata' u 1:2, f(x), g(x)


pause -1