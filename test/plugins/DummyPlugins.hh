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


#ifndef IGNITION_PLUGIN_TEST_PLUGINS_DUMMYPLUGINS_HH_
#define IGNITION_PLUGIN_TEST_PLUGINS_DUMMYPLUGINS_HH_

#include <string>
#include <memory>

namespace test
{
namespace util
{

/// \brief An interface that returns a string
class DummyNameBase
{
  public: virtual std::string MyNameIs() const = 0;

  public: virtual ~DummyNameBase() = default;
};

/// \brief An interface that returns a double
class DummyDoubleBase
{
  public: virtual double MyDoubleValueIs() const = 0;

  public: virtual ~DummyDoubleBase() = default;
};

/// \brief An interface that returns an int
class DummyIntBase
{
  public: virtual int MyIntegerValueIs() const = 0;

  public: virtual ~DummyIntBase() = default;
};

/// \brief An interface that allows values to be set
class DummySetterBase
{
  public: virtual void SetName(const std::string &_name) = 0;
  public: virtual void SetDoubleValue(const double _val) = 0;
  public: virtual void SetIntegerValue(const int _val) = 0;

  public: virtual ~DummySetterBase() = default;
};

/// \brief An arbitrary struct
struct SomeObject
{
  int someInt;
  double someDouble;

  inline SomeObject(int _intValue = 0, double _doubleValue = 0.0)
    : someInt(_intValue),
      someDouble(_doubleValue)
  {
    // Do nothing
  }

  public: virtual ~SomeObject() = default;
};

/// \brief An interface that returns a reference to an arbitrary struct
class DummyGetSomeObjectBase
{
  public: virtual std::unique_ptr<SomeObject> GetSomeObject() const = 0;
};

}
}


#endif
