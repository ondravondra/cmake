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
// Program extracts documentation describing commands from
// the CMake system.
// 
#include "cmake.h"

#include "cmDocumentation.h"

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationName[] =
{
  {0,
   "  DumpDocumentation - Dump documentation for CMake.", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationUsage[] =
{
  {0,
   "  DumpDocumentation [filename]", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationDescription[] =
{
  {0,
   "CMake reads ... ", 0},
  {0,0,0}
};

//----------------------------------------------------------------------------
static const cmDocumentationEntry cmDocumentationOptions[] =
{
  {"--all-for-coverage", "Dump all documentation to stdout.  For testing.", 0},
  {0,0,0}
};


int DumpHTML(const char* outname)
{
  std::ofstream fout(outname);
  if(!fout)
    {
    std::cerr << "failed to open output file: " << outname << "\n";
    return -1;
    }

  cmake cmi;
  cmDocumentation doc;
  std::vector<cmDocumentationEntry> commands;
  cmi.GetCommandDocumentation(commands);
  doc.AddSection("Documentation for Commands of CMake " CMake_VERSION_FULL,
                 &commands[0]);
  doc.Print(cmDocumentation::HTMLForm, fout);
  
  return 0;
}

int DumpForCoverage()
{
  cmake cmi;
  cmDocumentation doc;
  std::vector<cmDocumentationEntry> commands;
  std::vector<cmDocumentationEntry> generators;
  cmi.GetCommandDocumentation(commands);
  cmi.GetGeneratorDocumentation(generators);
  doc.SetNameSection(cmDocumentationName);
  doc.SetUsageSection(cmDocumentationUsage);
  doc.SetDescriptionSection(cmDocumentationDescription);
  doc.SetOptionsSection(cmDocumentationOptions);
  doc.SetCommandsSection(&commands[0]);
  doc.SetGeneratorsSection(&generators[0]);
  doc.PrintDocumentation(cmDocumentation::Usage, std::cout);
  doc.PrintDocumentation(cmDocumentation::Full, std::cout);
  doc.PrintDocumentation(cmDocumentation::HTML, std::cout);
  doc.PrintDocumentation(cmDocumentation::Man, std::cout);
  return 0;
}

int main(int ac, char** av)
{
  cmSystemTools::EnableMSVCDebugHook();
  const char* outname = "cmake.html";
  bool coverage = false;
  if(ac > 1)
    {
    if(strcmp(av[1], "--all-for-coverage") == 0)
      {
      coverage = true;
      }
    else
      {
      outname = av[1];
      }
    }
  
  if(coverage)
    {
    return DumpForCoverage();
    }
  else
    {
    return DumpHTML(outname);
    }
}
