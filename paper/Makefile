###############################################################################
#
# Tahoe-LAFS with SHA-3 Candidates Paper Makefile
#
###############################################################################

# compiler

PDFLATEX = pdflatex

###############################################################################

paper.pdf: main.tex
	pdflatex $<
	pdflatex $<
	rm -rf *.aux *.log *.toc *.out *.lof *.lot

.PHONY : clean 

clean :
	rm -rf *.aux *.log *.toc *.pdf *.out *.lof *.lot
