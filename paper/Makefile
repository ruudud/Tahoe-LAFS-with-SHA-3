###############################################################################
#
# Tahoe-LAFS with SHA-3 Candidates Paper Makefile
#
###############################################################################

# compiler

PDFLATEX = pdflatex

###############################################################################

main.pdf: main.tex title.tex
	pdflatex main.tex
	pdflatex main.tex
	rm -rf *.aux *.log *.toc *.out *.lof *.lot

problem:
	pdflatex problem_description.tex
	pdflatex problem_description.tex
	rm -rf *.aux *.log *.toc *.out *.lof *.lot

clean:
	rm -rf *.aux *.log *.toc *.pdf *.out *.lof *.lot

.PHONY: clean problem
