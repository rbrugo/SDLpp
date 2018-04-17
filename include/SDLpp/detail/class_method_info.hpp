/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : class_method_info
 * @created     : Saturday Mar 31, 2018 22:32:43 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_DETAIL_CLASS_METHOD_INFO_HPP
#define SDLPP_DETAIL_CLASS_METHOD_INFO_HPP

#include <typeinfo>
#include <cxxabi.h>
#include <string>


namespace SDLpp
{

namespace detail
{

struct demangling_result
{
    char * origin = nullptr;
    ~demangling_result() { free(origin); }
};

template < class T >
constexpr auto classname_demangle(T && obj)
{
    auto mangled{std::type_info(obj).name()};
    int status = 0;
    std::size_t length = 0;

    auto demangled = abi::__cxa_demangle(mangled, nullptr, &length, &status);
    if ( status < 0 ) {
        //return std::string{};
    }

    //std::string result(demangled, length);
    std::free(demangled);
    char * result = nullptr;

    return result;
}

} // namespace detail

} // namespace SDLpp

#endif /* SDLPP_DETAIL_CLASS_METHOD_INFO_HPP */

