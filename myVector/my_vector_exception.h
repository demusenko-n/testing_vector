#pragma once
#include <exception>
namespace my_vector
{
	class my_vector_exception : public std::exception
	{
	public:
		my_vector_exception() = default;
		explicit my_vector_exception( char const * const message) : exception(message) {}
	};
}