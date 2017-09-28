src = $(shell find . -name '*.cpp')
dst = $(src:%.cpp=%)

all: $(dst)
	@echo $(dst)
%: %.cpp
	g++ $< -o $@

clean:
	rm $(dst)
