#pragma once

#include <EchoGenHeader.h>

#ifdef ECHO_GEN_DEBUG
#define LOG_init(x)\
	std::cout << "[EchoGen][" << __func__ << "][initialize]: " << x << std::endl;

#define LOG_message(x)\
	std::cout << "[EchoGen][" << __func__ << "][message]: " << x << std::endl;

#define LOG_error(x)\
	std::cout << "[EchoGen][" << __func__ << "][error]: " << x << std::endl;

#define LOG_warning(x)\
	std::cout << "[EchoGen][" << __func__ << "][warning]: " << x << std::endl;

#define LOG_erase(x)\
	std::cout << "[EchoGen][" << __func__ << "][warning]: " << x << std::endl;
#else
#define LOG_init(x)
#define LOG_message(x)
#define LOG_error(x)
#define LOG_warning(x)
#define LOG_erase(x)
#endif