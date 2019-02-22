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

set(_command_line_apps
  fitLinearData
  # Put the name of your app here, without the .cpp extension.
)

foreach(_app ${_command_line_apps})
  add_executable(${_app} ${_app}.cpp)
  target_link_libraries(${_app} ${MPHYG0022CW1_LIBRARIES} ${ALL_THIRD_PARTY_LIBRARIES})
endforeach()
