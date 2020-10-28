#CROSS_COMPILE := arm-f1c200s-linux-gnueabi-
CXX = $(CROSS_COMPILE)g++
CC  = $(CROSS_COMPILE)gcc

TARGET	= hx711

DIR		= .
INC		= -I.
CFLAGS	= -Os -Wall# -std=gnu++11 
LDFLAGS += -lpthread

OBJPATH	= .
INSTALLPATH	= ./bin

FILES	= $(foreach dir,$(DIR),$(wildcard $(dir)/*.cpp))
CFILES	= $(foreach dir,$(DIR),$(wildcard $(dir)/*.c))

OBJS	= $(patsubst %.cpp,%.o,$(FILES))
COBJS	= $(patsubst %.c,%.o,$(CFILES))

all:$(OBJS) $(COBJS) $(TARGET)

$(OBJS):%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -c -o $(OBJPATH)/$(notdir $@) $< 

$(COBJS):%.o:%.c
	$(CC) $(CFLAGS) $(INC) -c -o $(OBJPATH)/$(notdir $@) $< 

$(TARGET):$(OBJPATH)
	$(CXX) -o $@ $(OBJPATH)/*.o $(LDFLAGS) 

install:
	echo "install"

clean:
	-rm -f $(OBJPATH)/*.o
	-rm -f $(TARGET)
