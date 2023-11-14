# Makefile模板

# 编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O0 -g -pthread

# 目标文件名
TARGET = my_program

# 源文件和对象文件
SRCS =   ./main.cpp
OBJS = $(SRCS:.cpp=.o)

all: clean $(TARGET)
# 链接规则
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 编译规则
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# 清理规则
clean:
	rm -f $(TARGET) $(OBJS)

run: all
	./my_program
