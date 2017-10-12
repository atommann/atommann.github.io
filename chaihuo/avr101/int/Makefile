TARGET = int

all:
	#pandoc -s --toc int.md -o int.html
	# markdown_py -x extra -x toc tuto.md -f hello.html
	# markdown_py -x extra -x tidy tuto.md -f tuto.html
	# markdown_py -x extra -x meta_data tuto.md -f tuto.html

	pandoc -s -S --toc -c pandoc.css $(TARGET).md -o $(TARGET).html
	#pandoc -s -S --toc -c buttondown.css int.md -o int.html
docx:
	pandoc -s -S $(TARGET).md -o $(TARGET).docx
