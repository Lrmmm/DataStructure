#ifndef myExceptions_
#define myExceptions_
#include <string>
using namespace std;
class illegalParameterValue : public std::exception
{
public:
    illegalParameterValue(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class illegalIndex : public std::exception
{
public:
    illegalIndex(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class MatrixIndexOutOfBounds : public std::exception
{
public:
    MatrixIndexOutOfBounds(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class MatrixSizeMisMatch : public std::exception
{
public:
    MatrixSizeMisMatch(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class StackEmpty : public std::exception
{
public:
    StackEmpty(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class QueueEmpty : public std::exception
{
public:
    QueueEmpty(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class HashTableFull : public std::exception
{
public:
    HashTableFull(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};


class EmptyTree : public std::exception
{
public:
    EmptyTree(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class HeapEmpty : public std::exception
{
public:
    HeapEmpty(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};
#endif