// Exception.h
#pragma once
#include <exception>
#include <string>

// Base exception class for the application
class ApplicationException : public std::exception {
protected:
    std::string message;
public:
    ApplicationException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Repository specific exceptions
class RepositoryException : public ApplicationException {
public:
    RepositoryException(const std::string& msg) : ApplicationException("Repository error: " + msg + "\n") {}
};

// Validation specific exceptions
class ValidationException : public ApplicationException {
public:
    ValidationException(const std::string& msg) : ApplicationException("Validation error: \n" + msg + "\n") {}
};

// Service layer exceptions
class ServiceException : public ApplicationException {
public:
    ServiceException(const std::string& msg) : ApplicationException("Service error: " + msg + "\n") {}
};