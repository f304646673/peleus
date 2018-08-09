NEED_GPERFTOOLS=0
BRPC_PATH=./brpc
include $(BRPC_PATH)/config.mk
# Notes on the flags:
# 1. Added -fno-omit-frame-pointer: perf/tcmalloc-profiler use frame pointers by default
# 2. Added -D__const__= : Avoid over-optimizations of TLS variables by GCC>=4.8
CXXFLAGS+=$(CPPFLAGS) -std=c++0x -DNDEBUG -O2 -D__const__= -pipe -W -Wall -Wno-unused-parameter -fPIC -fno-omit-frame-pointer
ifeq ($(NEED_GPERFTOOLS), 1)
	CXXFLAGS+=-DBRPC_ENABLE_CPU_PROFILER
endif
HDRS+=$(BRPC_PATH)/include
HDRS+=./
LIBS+=$(BRPC_PATH)/lib
OUTPUT=./output

HDRPATHS=$(addprefix -I, $(HDRS))
LIBPATHS=$(addprefix -L, $(LIBS))
COMMA=,
SOPATHS=$(addprefix -Wl$(COMMA)-rpath$(COMMA), $(LIBS))
BOOST_LINKINGS = -lboost_system -lboost_filesystem -lboost_serialization

ifeq ($(SYSTEM),Darwin)
 ifneq ("$(LINK_SO)", "")
	STATIC_LINKINGS += -lbrpc
 else
	# *.a must be explicitly specified in clang
	STATIC_LINKINGS += $(BRPC_PATH)/lib/libbrpc.a
 endif
	LINK_OPTIONS_SO = $^ $(STATIC_LINKINGS) $(DYNAMIC_LINKINGS)
	LINK_OPTIONS = $^ $(STATIC_LINKINGS) $(DYNAMIC_LINKINGS)
else ifeq ($(SYSTEM),Linux)
	STATIC_LINKINGS += -lbrpc
	LINK_OPTIONS_SO = -Xlinker "-(" $^ -Xlinker "-)" $(STATIC_LINKINGS) $(DYNAMIC_LINKINGS)
	LINK_OPTIONS = -Xlinker "-(" $^ -Wl,-Bstatic $(STATIC_LINKINGS) -Wl,-Bdynamic -Xlinker "-)" $(DYNAMIC_LINKINGS)
endif

########################################################################################################
#STL_SERIALIZATION_TEST
STL_SERIALIZATION_TEST_LIBS = $(BOOST_LINKINGS)
STL_SERIALIZATION_TEST_INCLUDE = ./ /usr/include
STL_SERIALIZATION_TEST_INCLUDE_PATH = $(addprefix -I, $(STL_SERIALIZATION_TEST_INCLUDE))
STL_SERIALIZATION_TEST_LIBS_PATH = $(addprefix -L, /usr/lib)
STL_SERIALIZATION_TEST_LIBS += -lgtest -lpthread
STL_SERIALIZATION_TEST_SOURCES = $(wildcard src/unit_test/stl_serialization/*.cpp)
STL_SERIALIZATION_TEST_OUTPUT = $(OUTPUT)/stl_serialization_test/

stl_serialization_test:
	test -d $(STL_SERIALIZATION_TEST_OUTPUT) || mkdir -p $(STL_SERIALIZATION_TEST_OUTPUT)
	for obj_path in $(STL_SERIALIZATION_TEST_SOURCES);do\
		name=$$(basename $$obj_path .cpp);\
		$(CXX) $$obj_path $(STL_SERIALIZATION_TEST_INCLUDE_PATH) $(CXXFLAGS) $(STL_SERIALIZATION_TEST_LIBS_PATH) $(STL_SERIALIZATION_TEST_LIBS) -o $(STL_SERIALIZATION_TEST_OUTPUT)$$name;\
	done
########################################################################################################
#PELEUS

PELEUS_LIBS = $(STATIC_LINKINGS)
PELEUS_LIBS += $(BOOST_LINKINGS)
PELEUS_LIBS += -lgtest -lpthread

PELEUS_INCLUDE_PATH = $(HDRPATHS)
PELEUS_LIBS_PATH = $(LIBPATHS)
PELEUS_SOURCES = $(wildcard src/entrance/*.cpp src/main/*.cpp src/modules/*.cpp src/utils/*.cpp src/plugins/*/*.cpp)
PELEUS_SOURCES_OBJS = $(addsuffix .o, $(basename $(PELEUS_SOURCES))) 
PELEUS_OUTPUT = $(OUTPUT)/peleus/

PELEUS_PROTOS = $(wildcard src/modules/configure/*.proto src/plugins/*/configure/*.proto src/plugins/*/interface/*.proto)
PELEUS_PROTO_OBJS = $(PELEUS_PROTOS:.proto=.pb.o)
PELEUS_PROTO_GENS = $(PELEUS_PROTOS:.proto=.pb.h) $(PROTOS:.proto=.pb.cc)
PELEUS_OUTPUT = $(OUTPUT)/peleus
PELEUS_INCLUDE_OUTPUT = $(PELEUS_OUTPUT)/include
PELEUS_LIBS_OUTPUT = $(PELEUS_OUTPUT)/libs

PELEUS_OUT_HEADERS = $(wildcard src/entrance/*.h src/utils/*.h src/plugins/*/*.h)

#		test -d $(PELEUS_ENTRANCE_INCLUDE_OUTPUT) || mkdir -p $(PELEUS_ENTRANCE_INCLUDE_OUTPUT);\
#		cp $$path $(P_INCLUDE_OUTPUT);\
#		HEAD_OUT_PATH = $(PELEUS_INCLUDE_OUTPUT)/path;\

peleus:$(PELEUS_PROTO_OBJS) $(PELEUS_SOURCES_OBJS)
	for path in $(PELEUS_OUT_HEADERS);do\
		dir=$${path%/*};\
		dir_without_src=$${dir#*/};\
		head_out_path=$(PELEUS_INCLUDE_OUTPUT)/$$dir_without_src;\
		test -d $$head_out_path || mkdir -p $$head_out_path;\
		cp $$path $$head_out_path;\
	done
		
	test -d $(PELEUS_LIBS_OUTPUT) || mkdir -p $(PELEUS_LIBS_OUTPUT)
	ar cr $(PELEUS_LIBS_OUTPUT)/lib$@.a $(PELEUS_SOURCES_OBJS)
#	echo $(CXX) $$obj_path $(PELEUS_INCLUDE_PATH) $(CXXFLAGS) $(PELEUS_LIBS_PATH) $(PELEUS_LIBS) -o $(PELEUS_OUTPUT)$@.a;\
########################################################################################################
	
#CLIENT_SOURCES = client.cpp
#SERVER_SOURCES = server.cpp
#PROTOS = $(wildcard *.proto)
#
#PROTO_OBJS = $(PROTOS:.proto=.pb.o)
#PROTO_GENS = $(PROTOS:.proto=.pb.h) $(PROTOS:.proto=.pb.cc)
#CLIENT_OBJS = $(addsuffix .o, $(basename $(CLIENT_SOURCES))) 
#SERVER_OBJS = $(addsuffix .o, $(basename $(SERVER_SOURCES))) 
#
#ifeq ($(SYSTEM),Darwin)
# ifneq ("$(LINK_SO)", "")
#	STATIC_LINKINGS += -lbrpc
# else
#	# *.a must be explicitly specified in clang
#	STATIC_LINKINGS += $(BRPC_PATH)/output/lib/libbrpc.a
# endif
#	LINK_OPTIONS_SO = $^ $(STATIC_LINKINGS) $(DYNAMIC_LINKINGS)
#	LINK_OPTIONS = $^ $(STATIC_LINKINGS) $(DYNAMIC_LINKINGS)
#else ifeq ($(SYSTEM),Linux)
#	STATIC_LINKINGS += -lbrpc
#	LINK_OPTIONS_SO = -Xlinker "-(" $^ -Xlinker "-)" $(STATIC_LINKINGS) $(DYNAMIC_LINKINGS)
#	LINK_OPTIONS = -Xlinker "-(" $^ -Wl,-Bstatic $(STATIC_LINKINGS) -Wl,-Bdynamic -Xlinker "-)" $(DYNAMIC_LINKINGS)
#endif
#
#.PHONY:all
#all: echo_client echo_server
#
#.PHONY:clean
#clean:
#	@echo "Cleaning"
#	@rm -rf echo_client echo_server $(PROTO_GENS) $(PROTO_OBJS) $(CLIENT_OBJS) $(SERVER_OBJS)
#
#echo_client:$(PROTO_OBJS) $(CLIENT_OBJS)
#	@echo "Linking $@"
#ifneq ("$(LINK_SO)", "")
#	@$(CXX) $(LIBPATHS) $(SOPATHS) $(LINK_OPTIONS_SO) -o $@
#else
#	@$(CXX) $(LIBPATHS) $(LINK_OPTIONS) -o $@
#endif
#
#echo_server:$(PROTO_OBJS) $(SERVER_OBJS)
#	@echo "Linking $@"
#ifneq ("$(LINK_SO)", "")
#	@$(CXX) $(LIBPATHS) $(SOPATHS) $(LINK_OPTIONS_SO) -o $@
#else
#	@$(CXX) $(LIBPATHS) $(LINK_OPTIONS) -o $@
#endif
#

#.PHONY:all
all: peleus

#.PHONY:clean
clean:
	@echo "Cleaning"
	@rm -rf $(PELEUS_PROTO_OBJS) $(PELEUS_SOURCES_OBJS) $(OUTPUT)

%.pb.cc %.pb.h:%.proto
	@echo "Generating $@"
	@$(PROTOC) --cpp_out=. --proto_path=. $(PROTOC_EXTRA_ARGS) $<

%.o:%.cpp
	@echo "Compiling $@"
	@$(CXX) -c $(HDRPATHS) $(CXXFLAGS) $< -o $@

%.o:%.cc
	@echo "Compiling $@"
	@$(CXX) -c $(HDRPATHS) $(CXXFLAGS) $< -o $@
