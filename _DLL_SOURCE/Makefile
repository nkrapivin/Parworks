.PHONY : clean

CC		=	clang-3.8
CXX		=	clang++-3.8
STEAMWORKS	=	$(HOME)/steamworks_sdk
CPPFLAGS	=	-std=c++11 -fPIC -g -I$(STEAMWORKS)/public/steam
LDFLAGS		=	-shared -L$(STEAMWORKS)/redistributable_bin/linux64 -L$(STEAMWORKS)/public/steam/lib/linux64 -lsteam_api
SOURCES		=	$(shell echo *.cpp)
HEADERS		=	$(shell echo *.h)
OBJECTS		=	$(SOURCES:.cpp=.o)
TARGET		=	libPar_linux.so


all: $(TARGET)


clean:
	rm -f $(OBJECTS) $(TARGET)


$(TARGET) : $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)



