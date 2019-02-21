#/*============================================================================
#
#  MPHYG0022CW1: CW1, 2019: Linear Regression.
#
#  Copyright (c) University College London (UCL). All rights reserved.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  See LICENSE.txt in the top level directory for details.
#
#============================================================================*/

set(MPHYG0022CW1_LIBRARY_NAME mphy0022cw1)

set(MPHYG0022CW1_LIBRARY_SRCS
  mphyBasicTypes.cpp
  mphyException.cpp
  mphyLinearDataCreator.cpp
  mphyNormalEquationSolverStrategy.cpp
  mphyGradientDescentSolverStrategy.cpp
  # Add .cpp files here
)

set(MPHYG0022CW1_LIBRARY_HDRS
  mphyExceptionMacro.h
  mphyDataCreatorI.h
  mphyLinearDataCreator.h
  mphyLinearModelSolverStrategyI.h
  mphyNormalEquationSolverStrategy.h
  vectorPairTypes.h
  mphyGradientDescentSolverStrategy.h
  # Add h files here
)

add_library(${MPHYG0022CW1_LIBRARY_NAME} ${MPHYG0022CW1_LIBRARY_HDRS} ${MPHYG0022CW1_LIBRARY_SRCS})

if(BUILD_SHARED_LIBS)
  if(WIN32)
    add_definitions(-DMPHYG0022CW1_WINDOWS_EXPORT)
  endif(WIN32)
endif(BUILD_SHARED_LIBS)

target_link_libraries(${MPHYG0022CW1_LIBRARY_NAME} PRIVATE ${ALL_THIRD_PARTY_LIBRARIES})

