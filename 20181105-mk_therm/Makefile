PICS = \

TEXTS = therm

##################################
PICS_T  = ${PICS:%=full_%.eps}
#%.png: pics/%.fig
#	fig2dev -Lpng -j -m3.75 $< $@
pics/%.eps: pics/%.fig
	fig2dev -Lpstex -m1 -j $< $@
pics/%.tex: pics/%.fig
	fig2dev -Lpstex_t -m1 -p ${@:.tex=.eps} -j $< $@
full_%.eps: pics/%.tex pics/%.eps
	epstex2eps $< $@
	epstopdf --outfile=tmp.pdf $@
	pdftops tmp.pdf $@
	rm -f tmp.pdf

##################################
TEXTS_T = ${TEXTS:=.pdf}
#%.pdf: %.ps
#	ps2pdf $<
#%.ps: %.dvi
#	dvips $<
#%.dvi: %.tex ${PICS_T}
#	latex $<
#	latex $<

%.pdf: %.tex ${PICS_T}
	pdflatex $<
	pdflatex $<

all: ${PICS_T} ${TEXTS_T}

##################################
clean:
	rm -f *.aux *.log *.nav *.out *.snm *.toc *.dvi *.eps *.bak *.bbl *.blg
	rm -f ${PICS_T} tmp_fig.* pics/*.eps pics/*.tex
