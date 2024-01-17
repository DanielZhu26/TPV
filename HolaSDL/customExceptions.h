#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H
#include "../checkML.h"
#include <exception>
#include <stdexcept>
#include "SDL.h"

namespace customExceptions
{
	class InvadersError : public std::logic_error
	{
	protected:
		std::string mensaje;
	public:
		InvadersError(const char* mensaje);

		const char* what() const throw() override;
	};

	class SDLError : public InvadersError
	{
	public:
		SDLError(const char* mensaje);
	};

	class FileNotFoundError : public InvadersError
	{
	public:
		FileNotFoundError(const char* filename);
	};

	class FileFormatError : public InvadersError
	{
	public:
		FileFormatError(const char* filename, int line);
	};
};
#endif