SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)
EXE=prog
CXXFLAGS=-lbcm2835 -pthread -I.
BUILD_DIR=build/host
BIN_DIR=bin/host
cxx=g++


$(BIN_DIR)/$(EXE): $(addprefix $(BUILD_DIR)/, $(DEPS) $(OBJECTS))
# << Check the $(DEPS) new dependency
	@mkdir -p $(BIN_DIR)
	$(CXX)  -o $@ $(addprefix $(BUILD_DIR)/,$(OBJECTS)) $(CXXFLAGS)


# Rule that describes how a .d ( dependency ) file is created from a .cpp file
# Similar to the assigment that you just completed %. cpp -> %.o
${BUILD_DIR}/%.d: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) -c  -o $(@:.d=.o) $^ $(CXXFLAGS)
	$(CXX) -MT $(BUILD_DIR)/$(@:.d=.o) -MM $(CXXFLAGS) $^ > $@

clean:
	@rm -rf bin build


ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif
