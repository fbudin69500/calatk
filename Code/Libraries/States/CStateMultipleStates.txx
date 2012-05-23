/*
*
*  Copyright 2011 by the CALATK development team
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

#ifndef C_STATE_MULTIPLE_STATES_TXX
#define C_STATE_MULTIPLE_STATES_TXX

//
// empty constructor
//
template < class TState >
CStateMultipleStates< TState  >::CStateMultipleStates()
{
}

//
// copy constructor
//
template < class TState >
CStateMultipleStates< TState >::CStateMultipleStates( const CStateMultipleStates & c )
{
  if ( this != &c )
    {
      assert ( this->m_vecIndividualStates.empty() );
      typename VectorIndividualStatesType::const_iterator iter;
      for ( iter=c.m_vecIndividualStates.begin(); iter!=c.m_vecIndividualStates.end(); ++iter )
        {
          typename TIndividualState::Pointer pCopiedState = new TIndividualState( **iter );
          this->m_vecIndividualStates.push_back( pCopiedState );
        }
    }
}

//
// copy constructor (from individual states which have been allocated externally)
//
template < class TState >
CStateMultipleStates< TState >::CStateMultipleStates( const std::vector< TIndividualState* >* pVec )
{
  typename VectorIndividualStatesType::const_iterator iter;
  for ( iter = pVec->begin(); iter != pVec->end(); ++iter )
    {
      m_vecIndividualStates.push_back( *iter );
    }
}


//
// clear data structure
//
template < class TState >
void CStateMultipleStates< TState >::ClearDataStructure()
{
  this->m_vecIndividualStates.clear();
}

//
// destructor
//
template < class TState>
CStateMultipleStates< TState >::~CStateMultipleStates()
{
  ClearDataStructure();
}

//
// Upsampling
//
template < class TState >
typename CStateMultipleStates< TState >::TState*
CStateMultipleStates< TState >::CreateUpsampledStateAndAllocateMemory( const VectorImageType* pGraftImage ) const
{
    VectorIndividualStatesType* ptrUpsampledState = new VectorIndividualStatesType;

    // upsample all the individual state components
    typename VectorIndividualStatesType::const_iterator iter;
    for ( iter = m_vecIndividualStates.begin(); iter != m_vecIndividualStates.end(); ++iter )
    {
      ptrUpsampledState->push_back( (*iter)->CreateUpsampledStateAndAllocateMemory( pGraftImage ) );
    }

    TState * upsampledState = new TState( ptrUpsampledState );

    return upsampledState;
}

// Here come the algebraic operators and assignment

template < class TState >
CStateMultipleStates< TState > &
CStateMultipleStates< TState >::operator=(const CStateMultipleStates & p )
{
  if ( this != &p )
    {
    
    // now do a deep copy
    
    // check if we already have the same number of elements. If so overwrite, otherwise recreate
    if ( m_vecIndividualStates.size() == p.m_vecIndividualStates.size() )
      {
      // already memory of appropriate size allocated, so just copy
      // iterate and copy
      
      typename VectorIndividualStatesType::const_iterator iterSource;
      typename VectorIndividualStatesType::iterator iterTarget;
      for ( iterSource = p.m_vecIndividualStates.begin(), iterTarget = m_vecIndividualStates.begin(); 
            iterSource != p.m_vecIndividualStates.end(), iterTarget != m_vecIndividualStates.end(); 
            ++iterSource, ++iterTarget )
        {
        // copy the current state
        *(*iterTarget) = *(*iterSource);
        }
      }
    else
      {
      // clear and then allocate, this should typically not be necessary
      std::cerr << "WARNING: reallocating memory, should already have been assigned." << std::endl;
      ClearDataStructure();

      typename VectorIndividualStatesType::const_iterator iter;
      for ( iter=p.m_vecIndividualStates.begin(); iter!=p.m_vecIndividualStates.end(); ++iter )
        {
          typename TIndividualState::Pointer pCopiedState = new TIndividualState( **iter );
          this->m_vecIndividualStates.push_back( pCopiedState );
        }
      }
    return *this;
    }
  else
    {
    return *this;
    }
}

template < class TState >
CStateMultipleStates< TState > &
CStateMultipleStates< TState >::operator+=(const CStateMultipleStates & p )
{
  if ( m_vecIndividualStates.size() != p.m_vecIndividualStates.size() )
    {
    throw std::runtime_error( "Size mismatch of state vectors. ABORT." );
    }

  typename VectorIndividualStatesType::const_iterator iterSource;
  typename VectorIndividualStatesType::iterator iterTarget;
  for ( iterSource = p.m_vecIndividualStates.begin(), iterTarget = m_vecIndividualStates.begin(); 
        iterSource != p.m_vecIndividualStates.end(), iterTarget != m_vecIndividualStates.end(); 
        ++iterSource, ++iterTarget )
    {
    // add the source to the target
    *(*iterTarget) += *(*iterSource );
    }

  return *this;
}

template < class TState >
CStateMultipleStates< TState > &
CStateMultipleStates< TState >::operator-=(const CStateMultipleStates & p )
{

  if ( m_vecIndividualStates.size() != p.m_vecIndividualStates.size() )
    {
    throw std::runtime_error( "Size mismatch of vector of vector fields. ABORT." );
    return;
    }

  typename VectorIndividualStatesType::const_iterator iterSource;
  typename VectorIndividualStatesType::iterator iterTarget;
  for ( iterSource = p.m_vecIndividualStates.begin(), iterTarget = m_vecIndividualStates.begin(); 
        iterSource != p.m_vecIndividualStates.end(), iterTarget != m_vecIndividualStates.end(); 
        ++iterSource, ++iterTarget )
    {
     // subtract the source from the target
    *(*iterTarget) -= *( *iterSource );
    }

  return *this;
}

template < class TState >
CStateMultipleStates< TState > &
CStateMultipleStates< TState >::operator*=(const TFloat & p )
{

  typename VectorIndividualStatesType::iterator iterTarget;
  for ( iterTarget = m_vecIndividualStates.begin(); iterTarget != m_vecIndividualStates.end(); ++iterTarget )
    {
    // multiply by the value
    *(*iterTarget)*= p;
    }

  return *this;
}

template < class TState >
CStateMultipleStates< TState >
CStateMultipleStates< TState >::operator+(const CStateMultipleStates & p ) const
{
  CStateMultipleStates r = *this;
  return r += p;
}

template < class TState >
CStateMultipleStates< TState >
CStateMultipleStates< TState >::operator-(const CStateMultipleStates & p ) const
{
  CStateMultipleStates r = *this;
  return r -= p;
}

template < class TState >
CStateMultipleStates< TState >
CStateMultipleStates< TState >::operator*(const TFloat & p ) const
{
  CStateMultipleStates r = *this;
  return r*= p;
}

//
// returns one of the individual states
//
template < class TState >
typename CStateMultipleStates< TState >::TIndividualState*
CStateMultipleStates< TState >::GetIndividualStatePointer( unsigned int uiState )
{
  int iNrOfStates = m_vecIndividualStates.size();
  if ( iNrOfStates==0 || iNrOfStates<=(int)uiState )
    {
      return NULL;
    }
  else
    {
      return m_vecIndividualStates[ uiState ];
    }
}

//
// computes the squared norm of the state, by adding all the individual square norm components
//
template < class TState >
typename CStateMultipleStates< TState >::TFloat
CStateMultipleStates< TState >::SquaredNorm()
{
  TFloat dSquaredNorm = 0;

  typename VectorIndividualStatesType::iterator iter;
  for ( iter = m_vecIndividualStates.begin(); iter != m_vecIndividualStates.end(); ++iter )
  {
    dSquaredNorm += (*iter)->SquaredNorm();
  }

  return dSquaredNorm;

}

//
// Allows to query if the state contains the initial image
//
template < class TState >
bool CStateMultipleStates< TState >::StateContainsInitialImage()
{
  return false;
}


#endif