MKDIR=pdfmake
FILE=$(MKDIR)/main.tex
PDF=$(MKDIR)/main.pdf
PDFFILE=ACMtemplastes.pdf

all: $(PDF)

$(PDF): $(FILE)
	xelatex -output-directory=$(MKDIR) $(FILE)
	cp $(PDF) $(PDFFILE)

edit: $(FILE)
	vim $(FILE)

view: $(PDFFILE)
	evince $(PDFFILE)
