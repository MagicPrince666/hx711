# CXX = /home/leo/xos/output/host/bin/arm-f1c100s-linux-gnueabi-g++

#目标文件
TARGET	= hx711 

DIR		= .
INC		= -I.
CFLAGS	= -Wall

OBJPATH	= .

FILES	= $(foreach dir,$(DIR),$(wildcard $(dir)/*.cpp))

OBJS	= $(patsubst %.cpp,%.o,$(FILES))

all:$(OBJS) $(TARGET)

$(OBJS):%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -c -o $(OBJPATH)/$(notdir $@) $< 

$(TARGET):$(OBJPATH)
	$(CXX) -o $@ $(OBJPATH)/*.o

$(OBJPATH):
	mkdir -p $(OBJPATH)

#清除
clean:
	-rm $(OBJPATH)/*.o
	-rm $(TARGET)
