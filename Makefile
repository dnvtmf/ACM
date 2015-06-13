MKDIR=pdfmake
FILE=main.tex
PDF=main.pdf
PDFFILE=ACMtemplastes.pdf
all:
	(cd $(MKDIR);make;cp $(PDF) ../$(PDFFILE))

edit: $(MKDIR)/$(FILE)
	vim $(MKDIR)/$(FILE)

texmaker:
	texmaker $(MKDIR)/$(FILE)

view:
	evince $(PDFFILE)

clean:
	(cd $(MKDIR); make clean)
