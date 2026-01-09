all: best_fit best_fit_decreasing first_fit first_fit_decreasing next_fit worst_fit worst_fit_decreasing

best_fit: best_fit.c
	gcc best_fit.c -o best_fit

best_fit_decreasing: best_fit_decreasing.c
	gcc best_fit_decreasing.c -o best_fit_decreasing

first_fit: first_fit.c
	gcc first_fit.c -o first_fit

first_fit_decreasing: first_fit_decreasing.c
	gcc first_fit_decreasing.c -o first_fit_decreasing

next_fit: next_fit.c
	gcc next_fit.c -o next_fit

worst_fit: worst_fit.c
	gcc worst_fit.c -o worst_fit

worst_fit_decreasing: worst_fit_decreasing.c
	gcc worst_fit_decreasing.c -o worst_fit_decreasing

clean:
	rm -f best_fit best_fit_decreasing first_fit first_fit_decreasing next_fit worst_fit worst_fit_decreasing
