IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
# LDIR =../lib

LIBS=

_DEPS = utils.h vec.h color.h ray.h camera.h hit_record.h sphere.h hittable_list.h interval.h material.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = vec.o main.o color.o ray.o camera.o hit_record.o sphere.o hittable_list.o interval.o utils.o material.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

raytracer: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ rm raytracer rm output.ppm