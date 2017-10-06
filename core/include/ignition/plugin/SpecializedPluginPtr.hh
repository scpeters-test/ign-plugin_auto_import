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


#ifndef IGNITION_COMMON_SPECIALIZEDPLUGINPTR_HH_
#define IGNITION_COMMON_SPECIALIZEDPLUGINPTR_HH_

#include "ignition/common/PluginPtr.hh"
#include "ignition/common/SpecializedPlugin.hh"

namespace ignition
{
  namespace common
  {
    /// \brief This alias allows PluginPtr instances to have low-cost access to
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
    /// to the SpecializedPluginPtr template. To specialize an interface, simply
    /// put the macro IGN_COMMON_SPECIALIZE_INTERFACE(~) from
    /// ignition/common/PluginMacros.hh into a public location of its class
    /// definition.
    template <typename... SpecInterfaces>
    using SpecializedPluginPtr =
              TemplatePluginPtr< SpecializedPlugin<SpecInterfaces...> >;

    /// \brief This alias creates a specialized PluginPtr whose interfaces are
    /// all const-qualified.
    template <typename... SpecInterfaces>
    using ConstSpecializedPluginPtr =
              TemplatePluginPtr< const SpecializedPlugin<SpecInterfaces...> >;
  }
}

#endif
