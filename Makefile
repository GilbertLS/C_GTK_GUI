# Code by: Gilbert Lavergne-Shank
#         Jordan Laforest
#
# Last Modified: Mar 22, 2013

GTKMM = `pkg-config --cflags --libs gtkmm-3.0`
DEBUG = -g
SRC = src/
OBJ = main.o controller.o mainwindow.o stuwindow.o appwindow.o io.o form.o selectlist.o student.o application.o course.o work.o sumwindow.o undergrad.o grad.o sumlist.o uapplication.o gapplication.o

build: $(OBJ)
		g++ -o cuTAES $(OBJ) $(GTKMM)

queuetest: $(SRC)queuetest.cc $(SRC)Queue.h
		g++ $(DEBUG) -o queuetest $(SRC)queuetest.cc

main.o:		$(SRC)main.cc $(SRC)controller.h
		g++ -c $(DEBUG) $(SRC)main.cc $(GTKMM)

controller.o:	$(SRC)controller.cc $(SRC)controller.h $(SRC)mainwindow.h $(SRC)course.h $(SRC)student.h $(SRC)stuwindow.h $(SRC)appwindow.h $(SRC)io.h $(SRC)application.h $(SRC)appwindow.h $(SRC)undergrad.h $(SRC)grad.h $(SRC)uapplication.h
		g++ -c $(DEBUG) $(SRC)controller.cc $(GTKMM)

mainwindow.o:	$(SRC)mainwindow.cc $(SRC)mainwindow.h $(SRC)controller.h $(SRC)io.h $(SRC)student.h $(SRC)grad.h $(SRC)undergrad.h $(SRC)application.h 
		g++ -c $(DEBUG) $(SRC)mainwindow.cc $(GTKMM)

stuwindow.o:	$(SRC)stuwindow.cc $(SRC)stuwindow.h $(SRC)io.h $(SRC)form.h
		g++ -c $(DEBUG) $(SRC)stuwindow.cc $(GTKMM)

appwindow.o:	$(SRC)appwindow.cc $(SRC)appwindow.h $(SRC)io.h $(SRC)form.h
		g++ -c $(DEBUG) $(SRC)appwindow.cc $(GTKMM)

sumwindow.o:	$(SRC)sumwindow.cc $(SRC)sumwindow.h $(SRC)io.h $(SRC)sumlist.h
		g++ -c $(DEBUG) $(SRC)sumwindow.cc $(GTKMM)

selectlist.o:	$(SRC)selectlist.cc $(SRC)selectlist.h $(SRC)io.h $(SRC)modelcolumns.h
		g++ -c $(DEBUG) $(SRC)selectlist.cc $(GTKMM)

form.o:		$(SRC)form.cc $(SRC)form.h $(SRC)io.h
		g++ -c $(DEBUG) $(SRC)form.cc $(GTKMM)

io.o:		$(SRC)io.cc $(SRC)io.h
		g++ -c $(DEBUG) $(SRC)io.cc $(GTKMM)

student.o:	$(SRC)student.cc $(SRC)student.h
		g++ -c $(DEBUG) $(SRC)student.cc

application.o:	$(SRC)application.cc $(SRC)application.h $(SRC)Queue.h $(SRC)work.h $(SRC)course.h
		g++ -c $(DEBUG) $(SRC)application.cc

course.o:	$(SRC)course.cc $(SRC)course.h
		g++ -c $(DEBUG) $(SRC)course.cc

work.o:		$(SRC)work.cc $(SRC)work.h
		g++ -c $(DEBUG) $(SRC)work.cc

undergrad.o:	$(SRC)undergrad.cc $(SRC)undergrad.h $(SRC)student.h
		g++ -c $(DEBUG) $(SRC)undergrad.cc

grad.o:		$(SRC)grad.cc $(SRC)grad.h $(SRC)student.h
		g++ -c $(DEBUG) $(SRC)grad.cc

sumlist.o:	$(SRC)sumlist.cc $(SRC)sumlist.h $(SRC)modelcolumns.h $(SRC)selectlist.h
		g++ -c $(DEBUG) $(SRC)sumlist.cc $(GTKMM)

uapplication.o:	$(SRC)uapplication.cc $(SRC)uapplication.h $(SRC)Queue.h $(SRC)work.h $(SRC)course.h
		g++ -c $(DEBUG) $(SRC)uapplication.cc

gapplication.o:	$(SRC)gapplication.cc $(SRC)gapplication.h $(SRC)Queue.h $(SRC)work.h $(SRC)course.h
		g++ -c $(DEBUG) $(SRC)gapplication.cc

clean:
		rm -f *.o cuTAES queuetest

run:
		./cuTAES

#https://live.gnome.org/Valgrind
#This is suppose to get rid of the false positives with valgrind
#but I haven't gotten it work perfectly yet
#I don't think the suppression file is even doing anything
memtest:
		G_SLICE=always-malloc G_DEBUG=gc-friendly valgrind --tool=memcheck --leak-check=full --leak-resolution=high --suppressions=valgrind/gtk.suppression2 --num-callers=20 --log-file=valgrind/dump ./cuTAES 
