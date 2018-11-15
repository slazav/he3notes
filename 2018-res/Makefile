TEXTS = main

INCDIR = ../
include ${INCDIR}/Makefile.inc


main.tex:img_res.pdf

img_res.pdf: res.eps
	epstopdf $< --outfile=$@

res.eps: ./res_plot
	./res_plot