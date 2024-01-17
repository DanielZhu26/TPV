#include "customExceptions.h"
#include <string>

namespace customExceptions
{
	InvadersError::InvadersError(const char* mensaje) : std::logic_error(mensaje) {}

	const char* InvadersError::what() const throw() {
		return mensaje.c_str();
	}

	SDLError::SDLError(const char* mensaje) : InvadersError(mensaje)
	{
		this->mensaje = "Error de SDL: " + std::string(SDL_GetError());
	}

	FileNotFoundError::FileNotFoundError(const char* filename) : InvadersError(filename)
	{
		this->mensaje = "Archivo no encontrado: " + std::string(filename);
	}

	FileFormatError::FileFormatError(const char* filename, int line) : InvadersError(filename)
	{
		this->mensaje = "Error de formato en el archivo: " + std::string(filename) + " ,en la línea " + std::to_string(line);
	}
}