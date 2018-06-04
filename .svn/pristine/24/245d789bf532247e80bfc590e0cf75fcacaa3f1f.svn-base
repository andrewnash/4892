CXXFLAGS=	-std=c++11 -Wall
SRCS=		templates.cpp template-math.cpp
OBJS=		${SRCS:.cpp=.o}

all: template-test
template-test: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o template-test

templates.o: templates.h
template-math.o: templates.h

clean:
	rm -f ${OBJS} template-test
