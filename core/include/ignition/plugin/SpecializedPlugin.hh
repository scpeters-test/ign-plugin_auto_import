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


#ifndef IGNITION_COMMON_SPECIALIZEDPLUGIN_HH_
#define IGNITION_COMMON_SPECIALIZEDPLUGIN_HH_

#include "ignition/common/Plugin.hh"

namespace ignition
{
  namespace common
  {
    // Forward declarations
    namespace detail { template <class, class> class ComposePlugin; }
    struct PluginInfo;

    /// \brief Declaration of the variadic template for SpecializedPlugin.
    /// This class definition is a C++ syntax formality.
    ///
    /// Look at the definition of SpecializedPlugin<SpecInterface> instead.
    template <class... OtherSpecInterfaces>
    class SpecializedPlugin
    {
      public: ~SpecializedPlugin() = default;
    };

    /// \brief This class allows Plugin instances to have low-cost access to
    /// interfaces that can be anticipated at compile time. The plugin does
    /// not have to actually offer the specialized interface in order to get
    /// this performance improvement. This template is variadic, so it can
    /// support arbitrarily many interfaces.
    ///
    /// Usage example:
    ///
    ///     using MySpecialPluginPtr = SpecializedPluginPtr<
    ///         MyInterface1, FooInterface, MyInterface2, BarInterface>;
    ///
    ///     MySpecialPluginPtr plugin = loader->Instantiate(pluginName);
    ///
    /// Then, calling the function
    ///
    ///     plugin->GetInterface<FooInterface>();
    ///
    /// will have extremely low cost associated with it. It will provide direct
    /// access to the the `FooInterface*` of `plugin`. If `plugin` does not
    /// actually offer `FooInterface`, then it will return a nullptr, still at
    /// extremely low cost.
    ///
    /// Only interfaces that have been "specialized" can be passed as arguments
    /// to the SpecializedPlugin template. To specialize an interface, simply
    /// put the macro IGN_COMMON_SPECIALIZE_INTERFACE(~) from
    /// ignition/common/PluginMacros.hh into a public location of its class
    /// definition.
    template <class SpecInterface>
    class SpecializedPlugin<SpecInterface> : public virtual Plugin
    {
      // -------------------- Public API ---------------------

      // Inherit function overloads
      public: using Plugin::GetInterface;
      public: using Plugin::as_shared_ptr;
      public: using Plugin::HasInterface;

      // Documentation inherited
      public: template <class Interface>
              Interface *GetInterface();

      // Documentation inherited
      public: template <class Interface>
              const Interface *GetInterface() const;

      // Documentation inherited
      public: template <class Interface>
              std::shared_ptr<Interface> as_shared_ptr();

      // Documentation inherited
      public: template <class Interface>
              std::shared_ptr<const Interface> as_shared_ptr() const;

      // Documentation inherited
      public: template <class Interface>
              bool HasInterface() const;


      // -------------------- Private API ---------------------

      // Declare friendship
      template <class...> friend class SpecializedPlugin;
      template <class, class> friend class detail::ComposePlugin;
      template <class> friend class TemplatePluginPtr;

      /// \brief type is an empty placeholder class which is used by the private
      /// member functions to provide two overloads: a high-performance one for
      /// SpecInterface, and a normal-performance one for all other Interface
      /// types.
      private: template <class T> struct type { };

      /// \brief Delegate the function to the standard Plugin method
      private: template <class Interface>
               Interface *PrivateGetSpecInterface(type<Interface>);

      /// \brief Use a low-cost accessor to provide this specialized interface
      private: SpecInterface *PrivateGetSpecInterface(type<SpecInterface>);

      /// \brief Delegate the function to the standard Plugin method
      private: template <class Interface>
               const Interface *PrivateGetSpecInterface(type<Interface>) const;

      /// \brief Use a low-cost accessor to provide this specialized interface
      private: const SpecInterface *PrivateGetSpecInterface(
                   type<SpecInterface>) const;

      /// \brief Delegate the function to the standard PluginPtr method
      private: template <class Interface>
               bool PrivateHasSpecInterface(type<Interface>) const;

      /// \brief Use a low-cost accessor to check on this specialized interface
      private: bool PrivateHasSpecInterface(type<SpecInterface>) const;

      /// \brief Iterator that points to the entry of the specialized interface
      private:
      const Plugin::InterfaceMap::iterator privateSpecInterfaceIterator;
      // Dev note (MXG): The privateSpecInterfaceIterator object must be
      // available to the user during their compile time, so it cannot be hidden
      // using PIMPL. The iterator is const because it must always point to the
      // same entry throughout its entire lifecycle.

      /// \brief Default constructor
      private: SpecializedPlugin();
    };
  }
}

#include "ignition/common/detail/SpecializedPlugin.hh"

#endif
