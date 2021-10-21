target := testsim
SRCS := testsim.c
objs := $(SRCS:.c=.o)

target2 := runsim
SRCS2 := runsim.c
objs2 := $(SRCS2:.c=.o)


CC := gcc
CFLAGS := -Wall

all: $(target) $(target2)

deps := $(patsubst %.o, %.d, $(objs), $(objs2))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)


target2: $(objs2)
	$(CC) $(CFLAGS) -o $@ $^

target: $(objs)
	$(CC) $(CFLAGS) -o $@ $^

%o: %.c 
	$(CC) $(CFLAGS) -c $< $(DEPFLAGS)

clean:
	rm -f $(target) $(target2) $(deps) .log .txt

.PHONY: all clean


