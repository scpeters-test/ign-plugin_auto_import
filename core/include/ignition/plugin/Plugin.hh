/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#ifndef IGNITION_COMMON_PLUGIN_HH_
#define IGNITION_COMMON_PLUGIN_HH_

#include <memory>
#include <map>
#include <string>

namespace ignition
{
  namespace common
  {
    // Forward declarations
    struct PluginInfo;
    class PluginPrivate;
    namespace detail { template <class B1, class B2> class ComposePlugin; }

    class Plugin
    {
      // -------------------- Public API ---------------------

      /// \brief Get an interface of the specified type. Note that this function
      /// only works when the Interface type is specialized using the macro
      /// IGN_COMMON_SPECIALIZE_INTERFACE. For more general  interfaces which do
      /// not meet this condition, use GetInterface<Interface>(_interfaceName).
      public: template <class Interface>
              Interface *GetInterface();

      /// \brief const-qualified version of GetInterface<Interface>()
      public: template <class Interface>
              const Interface *GetInterface() const;

      /// \brief Get an interface with the given name, casted to the specified
      /// class type.
      public: template <class Interface>
              Interface *GetInterface(const std::string &_interfaceName);

      /// \brief const-qualified version of GetInterface<Interface>(std::string)
      public: template <class Interface>
              const Interface *GetInterface(
                  const std::string &_interfaceName) const;

      /// \brief Get the requested interface as a std::shared_ptr. Note that
      /// this function only works when the Interface type is specialized using
      /// the macro IGN_COMMON_SPECIALIZE_INTERFACE. For more general interfaces
      /// which do not meet this condition, use
      /// as_shared_ptr<Interface>(_interfaceName).
      public: template <class Interface>
              std::shared_ptr<Interface> as_shared_ptr();

      /// \brief Same as as_shared_ptr<Interface>(), but it returns a
      /// std::shared_ptr to a const-qualified Interface.
      public: template <class Interface>
              std::shared_ptr<const Interface> as_shared_ptr() const;

      /// \brief Get the requested interface as a std::shared_ptr.
      public: template <class Interface>
              std::shared_ptr<Interface> as_shared_ptr(
                  const std::string &_interfaceName);

      /// \brief Same as as_shared_ptr<Interface>(std::string), but it returns a
      /// std::shared_ptr to a const-qualified Interface.
      public: template <class Interface>
              std::shared_ptr<const Interface> as_shared_ptr(
                  const std::string &_interfaceName) const;

      /// \brief Returns true if this PluginPtr has the specified type of
      /// interface. Note that this function only works when the Interface type
      /// is specialized using the macro IGN_COMMON_SPECIALIZE_INTERFACE. For
      /// more general interfaces which do not meet this condition, use
      /// GetInterface<Interface>(_interfaceName).
      public: template <class Interface>
              bool HasInterface() const;

      /// \brief Returns true if this PluginPtr has the specified type of
      /// interface.
      public: bool HasInterface(const std::string &_interfaceName) const;

      /// \brief This function always returns false if it is called on this
      /// basic PluginPtr class type. The SpecializedPluginPtr can shadow this
      /// to return true when it is specialized for this Interface type, however
      /// the function must be called on the SpecializedPluginPtr type and not
      /// this base class type, because this is a shadowed function, not a
      /// virtual function.
      public: template <class Interface>
              static constexpr bool IsSpecializedFor();


      // -------------------- Private API -----------------------

      template <class> friend class TemplatePluginPtr;
      template <class...> friend class SpecializedPlugin;
      template <class B1, class B2> friend class detail::ComposePlugin;

      /// \brief Default constructor. This is kept private to ensure that
      /// Plugins are always managed by a PluginPtr object.
      private: Plugin();

      /// \brief Type-agnostic retriever for interfaces
      private: void *PrivateGetInterface(
                  const std::string &_interfaceName) const;

      /// \brief Copy the plugin instance from another Plugin object
      private: void PrivateCopyPluginInstance(const Plugin &_other) const;

      /// \brief Create a new plugin instance based on the info provided
      private: void PrivateSetPluginInstance(const PluginInfo *_info) const;

      /// \brief Get a reference to the std::shared_ptr being managed by this
      /// wrapper
      private: const std::shared_ptr<void>& PrivateGetInstancePtr() const;


      public: using InterfaceMap = std::map<std::string, void*>;

      /// \brief Get or create an iterator to the std::map that holds pointers
      /// to the various interfaces provided by this plugin instance.
      private: InterfaceMap::iterator PrivateGetOrCreateIterator(
          const std::string &_interfaceName);

      /// \brief PIMPL pointer to the implementation of this class.
      private: const std::unique_ptr<PluginPrivate> dataPtr;

      /// \brief Virtual destructor
      public: virtual ~Plugin();
    };
  }
}

#include "ignition/common/detail/Plugin.hh"

#endif
