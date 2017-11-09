INCFLAGS  = -I /usr/include/GL
INCFLAGS += -I /usr/include/vecmath

LINKFLAGS  = -lglut -lGL -lGLU
LINKFLAGS += -L /usr/lib -lvecmath

CFLAGS    = -O2
CC        = g++ -std=c++11
SRCS      = main.cpp
OBJS      = $(SRCS:.cpp=.o)
PROG      = a0

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)

