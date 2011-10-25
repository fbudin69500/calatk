#ifndef C_LDDMM_GROWTH_MODEL_OBJECTIVE_FUNCTION_H
#define C_LDDMM_GROWTH_MODEL_OBJECTIVE_FUNCTION_H

#include "CLDDMMSpatioTemporalVelocityFieldObjectiveFunction.h"

namespace CALATK
{

template <class T, unsigned int VImageDimension, class TState >
class CLDDMMGrowthModelObjectiveFunction : public CLDDMMSpatioTemporalVelocityFieldObjectiveFunction< T, VImageDimension, TState >
{
public:

  /** some useful typedefs */

  typedef CLDDMMSpatioTemporalVelocityFieldObjectiveFunction< T, VImageDimension, TState > Superclass;
  typedef typename Superclass::VectorImageType VectorImageType;
  typedef typename Superclass::VectorFieldType VectorFieldType;

  CLDDMMGrowthModelObjectiveFunction();
  virtual ~CLDDMMGrowthModelObjectiveFunction();

  T GetCurrentEnergy();
  void ComputeGradient();

  SetMacro( SigmaSqr, T );
  GetMacro( SigmaSqr, T );

  void GetImage( VectorImageType* ptrIm, T dTime );

protected:

  /** Some useful protected typedefs */

  typedef typename Superclass::STimePoint STimePoint;
  typedef typename Superclass::VectorFieldPointerType VectorFieldPointerType;
  typedef typename Superclass::VectorImagePointerType VectorImagePointerType;
  typedef typename Superclass::VectorPointerToVectorFieldPointerType VectorPointerToVectorFieldPointerType;
  typedef typename Superclass::VectorPointerToVectorImagePointerType VectorPointerToVectorImagePointerType;
  
  typedef typename Superclass::ImageManagerType ImageManagerType;
  typedef typename Superclass::SImageInformation SImageInformation;
  typedef typename Superclass::SubjectInformationType SubjectInformationType;

  void ComputeImagesForward();
  void ComputeAdjointBackward();

  void DetermineTimePointData( std::vector< STimePoint >& vecTimePointData );

  void DeleteAuxiliaryStructures();
  void CreateAuxiliaryStructures();

private:

  VectorFieldPointerType m_ptrMapIn; // map for the numerical solution
  VectorFieldPointerType m_ptrMapOut; // map for the numerical solution
  VectorFieldPointerType m_ptrMapTmp; // map for the numerical solution

  VectorFieldPointerType m_ptrTmpVelocityField; // generic temporary velocity field
  VectorFieldPointerType m_ptrTmpGradient; // to store the temporary gradient
  VectorImagePointerType m_ptrI0; // initial image
  VectorImagePointerType m_ptrCurrentLambdaEnd; // current value of the adjoint, gets successively updated for multiple time points
  VectorImagePointerType m_ptrCurrentAdjointDifference;

  VectorImagePointerType m_ptrDeterminantOfJacobian;

  VectorPointerToVectorImagePointerType m_ptrI; // image
  VectorPointerToVectorImagePointerType m_ptrLambda; // adjoint

  T m_SigmaSqr; // 1/m_SigmaSqr is the multiplier for the data attachment term

};

#include "CLDDMMGrowthModelObjectiveFunction.txx"

}

#endif
