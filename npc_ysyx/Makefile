TOPNAME = top
VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc \
				-O3 --x-assign fast --x-initial fast \
				--trace --trace-fst \
				--top-module $(TOPNAME)

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

# 创建构建目录
$(shell mkdir -p $(BUILD_DIR))

# Verilog源文件
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v" -or -name "*.sv")

# C++源文件
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")

# 可能需要的包含路径，通过make INC_PATH=xxx指定
INC_PATH ?=
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

# 默认目标
default: $(BIN)

# 编译目标
$(BIN): $(VSRCS) $(CSRCS)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) \
		$(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

# 添加其他目标
all: default

run: $(BIN)
	@$^

wave: run
	@echo "打开波形文件..."
	gtkwave waveform.fst &

clean:
	rm -rf $(BUILD_DIR)

.PHONY: default all clean run wave