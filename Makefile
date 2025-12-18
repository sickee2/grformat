# Compiler settings
cxx = g++
# CXX = clang++

inc = include

cxxflags = -O2 -march=native -Wall -Wextra -std=c++2c -MMD -MP -MF $(@:%.o=%.d) -I$(inc)
# cxxflags = -g -march=native -Wall -Wextra -std=c++2c -MMD -MP -MF $(@:%.o=%.d) -Iinc

# Build directory
build_dir = build

# Target executable
target = $(build_dir)/grstr

# Source files
src_dir = src
test_dir = test

gr_src = $(src_dir)/gr/utf_sequence.cpp \
				 $(src_dir)/gr/utf_string.cpp \
				 $(src_dir)/gr/external_data.cpp 

cpp_src = $(gr_src)

cpp_src += $(test_dir)/test.cpp
# cpp_src += $(test_dir)/test_char_conv_performance.cpp
# cpp_src += $(test_dir)/test_ftoss.cpp
# cpp_src += $(test_dir)/test_format.cpp
# cpp_src += $(test_dir)/test_format_performance.cpp
# cpp_src += $(test_dir)/test_from_chars.cpp
# cpp_src += $(test_dir)/test_sstoi_edgecases.cpp
# cpp_src += $(test_dir)/test_bom.cpp
# cpp_src += $(test_dir)/test_cbuf.cpp
# cpp_src += $(test_dir)/test_convert.cpp
# cpp_src += $(test_dir)/test_convert2.cpp
# cpp_src += $(test_dir)/test_cptr.cpp
# cpp_src += $(test_dir)/test_endian.cpp
# cpp_src += $(test_dir)/test_to_chars.cpp
# cpp_src += $(test_dir)/test_iconv.cpp
# cpp_src += $(test_dir)/test_logger.cpp
# cpp_src += $(test_dir)/test_print.cpp
# cpp_src += $(test_dir)/test_printable.cpp
# cpp_src += $(test_dir)/test_RE2.cpp
# cpp_src += $(test_dir)/test_stoi.cpp
# cpp_src += $(test_dir)/test_trim.cpp
# cpp_src += $(test_dir)/test_upper_lower.cpp
# cpp_src += $(test_dir)/test_utf_string.cpp
# cpp_src += $(test_dir)/test_utfiter.cpp


# OBJ = $(build_dir)/main.o
objects = $(cpp_src:%.cpp=$(build_dir)/%.o)

# Dependency files
dep_dir = $(build_dir)/.deps

# Detect operating system
uname_s := $(shell uname -s)
MSYSTEM := $(shell echo $$MSYSTEM 2>/dev/null)

# Set linker flags based on operating system
ifeq ($(uname_s), Linux)
	ldflags = $(shell pkg-config --libs re2) -liconv -lfmt
else
	ldflags = $(shell pkg-config --libs re2) -liconv -lfmt
endif

# Default target
all: $(build_dir) $(target)

# Create build directory
$(build_dir):
	@mkdir -p $(build_dir)
	@mkdir -p $(build_dir)/gr
	@mkdir -p $(build_dir)/test

# Compile
$(build_dir)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(cxx) $(cxxflags) -c $< -o $@

# Link
$(target): $(objects)
	@echo linking...
	@$(cxx) $^ -o $@ $(ldflags)

# 包含依赖文件
-include $(wildcard $(build_dir)/*.d)
-include $(wildcard $(build_dir)/**/*.d)

# 清理
clean:
	@rm -rf $(build_dir)/test $(target)

clean_all:
	@rm -rf $(build_dir) $(target)
# 运行
run: $(target)
	./$(target)


.PHONY: all clean clean_all run
