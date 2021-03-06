NEED_GPERFTOOLS=0
BRPC_PATH=./brpc
include $(BRPC_PATH)/config.mk
# Notes on the flags:
# 1. Added -fno-omit-frame-pointer: perf/tcmalloc-profiler use frame pointers by default
# 2. Added -D__const__= : Avoid over-optimizations of TLS variables by GCC>=4.8
CXXFLAGS+=$(CPPFLAGS) -std=c++0x -DNDEBUG -O2 -D__const__= -pipe -W -Wall -Wno-unused-parameter -fPIC -fno-omit-frame-pointer -Wno-write-strings -Wno-literal-suffix -Wno-ignored-qualifiers -Wno-unused-local-typedefs -Wno-invalid-offsetof -Wno-unused-parameter -Wno-unused-function -Wno-narrowing -Wno-deprecated -Wno-parentheses -Wno-unused-but-set-variable -Wno-unused-variable -Wno-unused-parameter -Wno-multichar -Werror -march=nocona -minline-all-stringops -msse4.2
STATIC_LINKINGS += -rdynamic -static-libgcc -static-libstdc++

ifeq ($(NEED_GPERFTOOLS), 1)
	CXXFLAGS+=-DBRPC_ENABLE_CPU_PROFILER
endif
HDRS+=$(BRPC_PATH)/include
HDRS+=./
LIBS+=$(BRPC_PATH)/lib
OUTPUT=./output

HDRPATHS=$(addprefix -I, $(HDRS))
LIBPATHS=$(addprefix -L, $(LIBS))

BOOST_LINKINGS = -lboost_system -lboost_filesystem -lboost_serialization
MYSQL_LINKINGS = -lmysqlclient

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

PELEUS_INCLUDE_PATH = $(HDRPATHS)
PELEUS_SOURCES = $(wildcard src/entrance/*.cpp src/main/*.cpp src/modules/*.cpp src/utils/*.cpp src/plugins/*.cpp src/plugins/*/*.cpp)
PELEUS_SOURCES_OBJS = $(addsuffix .o, $(basename $(PELEUS_SOURCES))) 

PELEUS_PROTOS = $(wildcard src/modules/configure/*.proto src/plugins/configure/*.proto src/plugins/*/configure/*.proto src/plugins/*/interface/*.proto)
PELEUS_PROTO_OBJS = $(PELEUS_PROTOS:.proto=.pb.o)
PELEUS_PROTO_GENS = $(PELEUS_PROTOS:.proto=.pb.h) $(PELEUS_PROTOS:.proto=.pb.cc)

PELEUS_OUTPUT = $(OUTPUT)/peleus
PELEUS_INCLUDE_OUTPUT = $(PELEUS_OUTPUT)/include
PELEUS_LIBS_OUTPUT = $(PELEUS_OUTPUT)/libs

PELEUS_OUT_HEADERS = $(wildcard src/entrance/*.h src/utils/*.h src/plugins/*/*.h)

peleus:$(PELEUS_PROTO_OBJS) $(PELEUS_SOURCES_OBJS)
	for path in $(PELEUS_OUT_HEADERS);do\
		dir=$${path%/*};\
		dir_without_src=$${dir#*/};\
		head_out_path=$(PELEUS_INCLUDE_OUTPUT)/$$dir_without_src;\
		test -d $$head_out_path || mkdir -p $$head_out_path;\
		cp $$path $$head_out_path;\
	done
		
	test -d $(PELEUS_LIBS_OUTPUT) || mkdir -p $(PELEUS_LIBS_OUTPUT)
	ar rcs $(PELEUS_LIBS_OUTPUT)/lib$@.a $(PELEUS_PROTO_OBJS) $(PELEUS_SOURCES_OBJS)
########################################################################################################
#DEMO

#SERVER
DEMO_SERVER_SOURCES = $(wildcard src/demo/server/*.cpp)
DEMO_SERVER_SOURCES_OBJS = $(addsuffix .o, $(basename $(DEMO_SERVER_SOURCES))) 
DEMO_SERVER_PROTOS = $(wildcard src/demo/proto/*.proto)
DEMO_SERVER_PROTO_OBJS = $(DEMO_SERVER_PROTOS:.proto=.pb.o)
DEMO_SERVER_PROTO_GENS = $(DEMO_SERVER_PROTOS:.proto=.pb.h) $(DEMO_SERVER_PROTOS:.proto=.pb.cc)

DEMO_SERVER_OUTPUT = $(OUTPUT)/demo/server
DEMO_SERVER_BIN_OUTPUT = $(DEMO_SERVER_OUTPUT)/bin
DEMO_SERVER_CONF_OUTPUT = $(DEMO_SERVER_OUTPUT)/conf

DEMO_SERVER_WHOLE_LINKINGS = -lpeleus
DEMO_SERVER_STATIC_LINKINGS = -lbrpc
DEMO_SERVER_LINKINGS = $(BOOST_LINKINGS)
DEMO_SERVER_LINKINGS += $(MYSQL_LINKINGS)
DEMO_SERVER_LINKINGS += $(STATIC_LINKINGS)
DEMO_SERVER_LINKINGS += $(DYNAMIC_LINKINGS)

DEMO_SERVER_LIBPATHS = $(LIBS)
DEMO_SERVER_LIBPATHS += $(PELEUS_LIBS_OUTPUT)
DEMO_SERVER_LIBPATHS_WITH_L = $(addprefix -L, $(DEMO_SERVER_LIBPATHS))

DEMO_SERVER_LINK_OPTIONS=-Xlinker "-(" $^ -Wl,-Bstatic,--whole-archive $(DEMO_SERVER_WHOLE_LINKINGS) -Wl,-Bdynamic,--no-whole-archive -Wl,-Bstatic $(DEMO_SERVER_STATIC_LINKINGS) -Wl,-Bdynamic -Xlinker "-)" 

demo_server:$(DEMO_SERVER_PROTO_OBJS) $(DEMO_SERVER_SOURCES_OBJS)
	test -d $(DEMO_SERVER_BIN_OUTPUT) || mkdir -p $(DEMO_SERVER_BIN_OUTPUT)
	@$(CXX) $(DEMO_SERVER_LIBPATHS_WITH_L) $(DEMO_SERVER_LINK_OPTIONS) $(DEMO_SERVER_LINKINGS) -o $(DEMO_SERVER_BIN_OUTPUT)/$@
	test -d $(DEMO_SERVER_CONF_OUTPUT) || mkdir -p $(DEMO_SERVER_CONF_OUTPUT)
	cp -r src/demo/server/conf/* $(DEMO_SERVER_CONF_OUTPUT)

#CLIENT
DEMO_CLIENT_SOURCES = $(wildcard src/demo/client/*.cpp)
DEMO_CLIENT_SOURCES_OBJS = $(addsuffix .o, $(basename $(DEMO_CLIENT_SOURCES))) 
DEMO_CLIENT_PROTOS = $(wildcard src/demo/proto/*.proto)
DEMO_CLIENT_PROTO_OBJS = $(DEMO_CLIENT_PROTOS:.proto=.pb.o)
DEMO_CLIENT_PROTO_GENS = $(DEMO_CLIENT_PROTOS:.proto=.pb.h) $(DEMO_CLIENT_PROTOS:.proto=.pb.cc)

DEMO_CLIENT_OUTPUT = $(OUTPUT)/demo/client
DEMO_CLIENT_BIN_OUTPUT = $(DEMO_CLIENT_OUTPUT)/bin
DEMO_CLIENT_CONF_OUTPUT = $(DEMO_CLIENT_OUTPUT)/conf

DEMO_CLIENT_STATIC_LINKINGS = -lbrpc

DEMO_CLIENT_LINKINGS = $(STATIC_LINKINGS)
DEMO_CLIENT_LINKINGS += $(BOOST_LINKINGS)
DEMO_CLIENT_LINKINGS += $(DYNAMIC_LINKINGS)

DEMO_CLIENT_LIBPATHS = $(LIBS)
DEMO_CLIENT_LIBPATHS_WITH_L = $(addprefix -L, $(DEMO_CLIENT_LIBPATHS))

DEMO_CLIENT_LINK_OPTIONS=-Xlinker "-(" $^ -Wl,-Bstatic,--whole-archive $(DEMO_CLIENT_STATIC_LINKINGS) -Wl,-Bdynamic,--no-whole-archive -Xlinker "-)"

demo_client:$(DEMO_CLIENT_PROTO_OBJS) $(DEMO_CLIENT_SOURCES_OBJS)
	test -d $(DEMO_CLIENT_BIN_OUTPUT) || mkdir -p $(DEMO_CLIENT_BIN_OUTPUT)
	@$(CXX) $(DEMO_CLIENT_LIBPATHS_WITH_L) $(DEMO_CLIENT_LINK_OPTIONS) $(DEMO_CLIENT_LINKINGS) -o $(DEMO_CLIENT_BIN_OUTPUT)/$@
	#test -d $(DEMO_CLIENT_CONF_OUTPUT) || mkdir -p $(DEMO_CLIENT_CONF_OUTPUT)
	#cp -r src/demo/client/conf/* $(DEMO_SERVER_CONF_OUTPUT)

########################################################################################################
#.PHONY:all
all: peleus demo_server demo_client

#.PHONY:clean
clean:
	@echo "Cleaning"
	@rm -rf $(PELEUS_PROTO_GENS) $(PELEUS_PROTO_OBJS) $(PELEUS_SOURCES_OBJS) $(DEMO_CLIENT_PROTO_OBJS) $(DEMO_CLIENT_SOURCES_OBJS) $(DEMO_SERVER_PROTO_OBJS) $(DEMO_SERVER_SOURCES_OBJS) $(OUTPUT)

%.pb.cc %.pb.h:%.proto
	@echo "Generating $@"
	@$(PROTOC) --cpp_out=. --proto_path=. $(PROTOC_EXTRA_ARGS) $<

%.o:%.cpp
	@echo "Compiling $@"
	@$(CXX) -c $(HDRPATHS) $(CXXFLAGS) $< -o $@

%.o:%.cc
	@echo "Compiling $@"
	@$(CXX) -c $(HDRPATHS) $(CXXFLAGS) $< -o $@
