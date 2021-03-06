/*
*
*  Copyright 2011, 2012 by the CALATK development team
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
*
*/

#ifndef COMPARE_WARPING_H
#define COMPARE_WARPING_H

#include "CALATKCommon.h"
#include "VectorField.h"
#include "VectorImage.h"
#include "CImageInformation.h"

namespace CALATK
{
template < class TFloat, unsigned int VImageDimension=3 >
class Warping : public CProcessBase
{
public:
    typedef Warping                         Self;
    typedef CProcessBase                    Superclass;
    typedef itk::SmartPointer< Self >       Pointer;
    typedef itk::SmartPointer< const Self > ConstPointer;

    int TestOpenJSON( const char *baselineJSONFileName);
    int ReadJSONContent( const Json::Value & baseline);
};
}
#endif
