#ifndef IGNITION_PLUGIN_SRC_DEMANGLE_HH_
#define IGNITION_PLUGIN_SRC_DEMANGLE_HH_

#include <string>
#include <iostream>
#include <cassert>

#if defined(__GNUC__) || defined(__clang__)
// This header is used for name demangling on GCC and Clang
#include <cxxabi.h>
#endif

namespace ignition
{
  namespace plugin
  {
    /////////////////////////////////////////////////
    inline std::string Demangle(const std::string &_name)
    {
    #if defined(__GNUC__) || defined(__clang__)
      int status;
      char *demangled_cstr = abi::__cxa_demangle(
            _name.c_str(), nullptr, nullptr, &status);

      if (0 != status)
      {
        std::cerr << "[Demangle] Failed to demangle the symbol name [" << _name
                  << "]. Error code: " << status << "\n";
        assert(false);
        return _name;
      }

      const std::string demangled(demangled_cstr);
      free(demangled_cstr);

      return demangled;
    #elif _MSC_VER

      assert(_name.substr(0, 6) == "class ");

      // Visual Studio's typeid(~).name() does not mangle the name, except that
      // it prefixes the normal name of the class with the character sequence
      // "class ". So to get the "demangled" name, all we have to do is remove
      // the first six characters. The plugin framework does not handle any
      // non-class types, so we do not lose anything by removing the "class "
      // designator.
      return _name.substr(6);
    #else
      // If we don't know the compiler, then we can't perform name demangling.
      // The tests will probably fail in this situation, and the class names
      // will probably look gross to users. Plugin name aliasing can be used
      // to make plugins robust to this situation.
      return _name;
    #endif
    }
  }
}

#endif
