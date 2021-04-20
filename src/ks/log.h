//
// Created by Tobi on 07/03/2021.
//
#pragma once

#include <fmt/core.h>
#include <string>
#include <iostream>


inline void println(std::string_view message) { std::cout << message << std::endl; }

template<class T>
requires (not std::convertible_to<T, std::string_view>)
void println(const T &t) { println(std::to_string(t)); }

template<typename... Args>
void println(std::string_view format, const Args &...args) { println(fmt::format(format, args...)); }