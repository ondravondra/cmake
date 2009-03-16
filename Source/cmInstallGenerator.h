/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef cmInstallGenerator_h
#define cmInstallGenerator_h

#include "cmScriptGenerator.h"

class cmLocalGenerator;

/** \class cmInstallGenerator
 * \brief Support class for generating install scripts.
 *
 */
class cmInstallGenerator: public cmScriptGenerator
{
public:
  cmInstallGenerator(const char* destination,
                     std::vector<std::string> const& configurations,
                     const char* component);
  virtual ~cmInstallGenerator();

  void AddInstallRule(
    std::ostream& os, int type,
    std::vector<std::string> const& files,
    bool optional = false,
    const char* properties = 0,
    const char* permissions_file = 0,
    const char* permissions_dir = 0,
    const char* rename = 0,
    const char* literal_args = 0,
    Indent const& indent = Indent()
    );

  const char* GetDestination() const
    { return this->Destination.c_str(); }

  /** Get the install destination as it should appear in the
      installation script.  */
  std::string GetInstallDestination() const;

  /** Test if this generator installs something for a given configuration.  */
  bool InstallsForConfig(const char*);

protected:
  virtual void GenerateScript(std::ostream& os);

  std::string CreateComponentTest(const char* component);

  // Information shared by most generator types.
  std::string Destination;
  std::string Component;
};

#endif
