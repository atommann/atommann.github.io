all:
	#pandoc -s --toc tuto.md -o tuto.html
	# markdown_py -x extra -x toc tuto.md -f hello.html
	# markdown_py -x extra -x tidy tuto.md -f tuto.html
	# markdown_py -x extra -x meta_data tuto.md -f tuto.html

	#pandoc -s -S --toc -c pandoc.css filter.md -o filter.html
	pandoc -s --webtex -S --toc -c pandoc.css filter.md -o filter.html
docx:
	pandoc -s -S filter.md -o filter.docx
