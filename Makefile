# 定义编译器
CXX = g++

# 定义编译选项
CXXFLAGS = -std=c++11 -O2

# 定义目标可执行文件的名称
TARGET = warehouse_location

# 定义源文件
SRCS = main.cpp utils.cpp kmeans.cpp findOptWarehouseLocs.cpp

# 如果有 customer.cpp 和 warehouse.cpp，请取消注释以下两行
# SRCS += customer.cpp
# SRCS += warehouse.cpp

# 自动推导对象文件名
OBJS = $(SRCS:.cpp=.o)

# 定义头文件目录（如果有其他目录，可以在此添加）
INCLUDES = -I.

# 链接选项（如有需要，可以在此添加库链接，例如 -lm）
LDFLAGS =

# 规则：默认目标
all: $(TARGET)

# 规则：链接可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

# 规则：编译源文件为对象文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 规则：清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

# 规则：重新编译
rebuild: clean all

# 伪目标，不实际生成文件
.PHONY: all clean rebuild

