/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmPropertyMap.h"

#include <algorithm>
#include <assert.h>
#include <cmConfigure.h>
#include <utility>

cmProperty* cmPropertyMap::GetOrCreateProperty(const std::string& name)
{
  cmPropertyMap::iterator it = this->find(name);
  cmProperty* prop;
  if (it == this->end()) {
    prop = &(*this)[name];
  } else {
    prop = &(it->second);
  }
  return prop;
}

std::vector<std::string> cmPropertyMap::GetPropertyList() const
{
  std::vector<std::string> keyList;
  for (cmPropertyMap::const_iterator i = this->begin(), e = this->end();
       i != e; ++i) {
    keyList.push_back(i->first);
  }
  std::sort(keyList.begin(), keyList.end());
  return keyList;
}

void cmPropertyMap::SetProperty(const std::string& name, const char* value)
{
  if (!value) {
    this->erase(name);
    return;
  }

  cmProperty* prop = this->GetOrCreateProperty(name);
  prop->Set(value);
}

void cmPropertyMap::AppendProperty(const std::string& name, const char* value,
                                   bool asString)
{
  // Skip if nothing to append.
  if (!value || !*value) {
    return;
  }

  cmProperty* prop = this->GetOrCreateProperty(name);
  prop->Append(value, asString);
}

const char* cmPropertyMap::GetPropertyValue(const std::string& name) const
{
  assert(!name.empty());

  cmPropertyMap::const_iterator it = this->find(name);
  if (it == this->end()) {
    return CM_NULLPTR;
  }
  return it->second.GetValue();
}
