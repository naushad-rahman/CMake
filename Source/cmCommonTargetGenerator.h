/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2015 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmCommonTargetGenerator_h
#define cmCommonTargetGenerator_h

#include <cmConfigure.h> // IWYU pragma: keep

#include "cmOutputConverter.h"

#include <map>
#include <string>
#include <vector>

class cmGeneratorTarget;
class cmGlobalCommonGenerator;
class cmLocalCommonGenerator;
class cmMakefile;
class cmSourceFile;

/** \class cmCommonTargetGenerator
 * \brief Common infrastructure for Makefile and Ninja per-target generators
 */
class cmCommonTargetGenerator
{
public:
  cmCommonTargetGenerator(cmGeneratorTarget* gt);
  virtual ~cmCommonTargetGenerator();

  std::string const& GetConfigName() const;

protected:
  // Add language feature flags.
  void AddFeatureFlags(std::string& flags, const std::string& lang);

  // Feature query methods.
  const char* GetFeature(const std::string& feature);
  bool GetFeatureAsBool(const std::string& feature);

  // Helper to add flag for windows .def file.
  void AddModuleDefinitionFlag(std::string& flags);

  cmGeneratorTarget* GeneratorTarget;
  cmMakefile* Makefile;
  cmLocalCommonGenerator* LocalGenerator;
  cmGlobalCommonGenerator* GlobalGenerator;
  std::string ConfigName;

  // The windows module definition source file (.def), if any.
  cmSourceFile const* ModuleDefinitionFile;

  void AppendFortranFormatFlags(std::string& flags,
                                cmSourceFile const& source);

  virtual void AddIncludeFlags(std::string& flags,
                               std::string const& lang) = 0;

  void AppendOSXVerFlag(std::string& flags, const std::string& lang,
                        const char* name, bool so);

  typedef std::map<std::string, std::string> ByLanguageMap;
  std::string GetFlags(const std::string& l);
  ByLanguageMap FlagsByLanguage;
  std::string GetDefines(const std::string& l);
  ByLanguageMap DefinesByLanguage;
  std::string GetIncludes(std::string const& l);
  ByLanguageMap IncludesByLanguage;
  std::string GetManifests();

  std::vector<std::string> GetLinkedTargetDirectories() const;
};

#endif
