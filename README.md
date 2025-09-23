# readstc2103
This programs read Bepicolombo data and
perform science data analysis and engineering
data analysis.
###
readstc2103.c
###
this program read a fits file and prints out the content on the standard output
to compile on Linux:
`gcc readstc2103.c -o readstc2103.c -L$CFITSIO_HOME -lcfitsio`
###
to execute
###
`./readfits <fitsfile> > asciifile.txt`
###
readascii.c
###
this program reads an ascii file created with the program readstc2103.c
and reads all the data of the sectors binary table and plot an histogram
given the raw(packet) number. It needs gnuplot installed.
to compile on Linux:
###
`gcc readascii.c -o readascii`
###
to execute
`./readascii asciifile.txt <rownum>'
