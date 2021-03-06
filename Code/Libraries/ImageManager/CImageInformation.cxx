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

#include "CImageInformation.txx"

namespace CALATK
{

template class CImageInformation< float, 1 >;
template class CImageInformation< float, 2 >;
template class CImageInformation< float, 3 >;
template class CImageInformation< double, 1 >;
template class CImageInformation< double, 2 >;
template class CImageInformation< double, 3 >;

} // namespace CALATK
