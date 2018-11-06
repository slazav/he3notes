# define this do build pictures (fig+tex) and texts (pdflatex)
PICS  ?=
TEXTS ?=

# redefine if needed
IMGDIR   ?= img
FIG_PREF ?= img_

##################################
PICS_T  = ${PICS:%=${FIG_PREF}%.pdf}
#%.png: ${IMGDIR}/%.fig
#	fig2dev -Lpng -j -m3.75 $< $@
${IMGDIR}/%.eps: ${IMGDIR}/%.fig
	fig2dev -Lpstex -m1 -j $< $@
${IMGDIR}/%.tex: ${IMGDIR}/%.fig
	fig2dev -Lpstex_t -m1 -p ${@:.tex=.eps} -j $< $@

# tex wrapper for tex+fig image
# for this file we can not use pdflatex
${FIG_PREF}%.tex: ${IMGDIR}/%.tex
	echo "\
	\documentclass[a4paper]{article}\
	\usepackage{amssymb}\
	\usepackage{euscript}\
	\usepackage{graphicx}\
	\usepackage{color}\
	\usepackage{epsfig}\
	\usepackage{fullpage}\
	\pagestyle{empty}\
	\begin{document}\
	\begin{figure}[p]\input{$<}\end{figure}\
	\end{document}" > $@

# Convert tex+fig file into pdf
${FIG_PREF}%.dvi: ${FIG_PREF}%.tex ${IMGDIR}/%.tex ${IMGDIR}/%.eps
	latex $<
	rm -f ${<:%.tex=%.log} ${<:%.tex=%.aux}
${FIG_PREF}%.ps: ${FIG_PREF}%.dvi ${IMGDIR}/%.tex ${IMGDIR}/%.eps
	dvips $<
${FIG_PREF}%.eps: ${FIG_PREF}%.ps
	eps2eps $< $@
${FIG_PREF}%.pdf: ${FIG_PREF}%.eps
	epstopdf $<


##################################
TEXTS_T = ${TEXTS:=.pdf}

%.pdf: %.tex ${PICS_T} ../brands.tex
	pdflatex $<
	pdflatex $<

all: ${PICS_T} ${TEXTS_T}

##################################
clean:
	rm -f *.aux *.log *.nav *.out *.snm *.toc *.dvi *.eps *.bak *.bbl *.blg
	rm -f ${PICS_T} tmp_fig.* img/*.eps img/*.tex
