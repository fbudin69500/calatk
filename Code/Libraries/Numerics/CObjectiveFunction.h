#ifndef C_OBJECTIVE_FUNCTION_H
#define C_OBJECTIVE_FUNCTION_H

#include "CALATKCommon.h"
#include "CMetric.h"

namespace CALATK
{

template <class T, class TState, unsigned int VImageDimension=3 >
class CObjectiveFunction
{
public:
  
  typedef TState* ptrStateType;
  typedef CMetric< T, VImageDimension >* ptrMetricType;

  CObjectiveFunction();
  virtual ~CObjectiveFunction();

  virtual T GetCurrentEnergy() = 0;
  virtual void ComputeGradient();
  
  virtual void InitializeState() = 0;

  void SetStatePointer( ptrStateType pState )
  {
    m_pState = pState;
  };

  ptrStateType GetStatePointer()
  {
    return m_pState;
  };

  void SetGradientPointer( ptrStateType pGradient )
  {
    m_pGradient = pGradient;
  };

  ptrStateType GetGradientPointer()
  {
    return m_pGradient;
  };

  void SetMetric( ptrMetricType pMetric )
  {
    m_pMetric = pMetric;
  };

  ptrMetricType GetMetric()
  {
    return m_pMetric;
  };

protected:

  ptrStateType m_pState;
  ptrStateType m_pGradient;
  ptrMetricType m_pMetric;

private:



};

#include "CObjectiveFunction.txx"

} // end namespace

#endif