  cmake_minimum_required(VERSION 2.8)
  project(qt-fbo)

  # Tell CMake to run moc when necessary:
  set(CMAKE_AUTOMOC ON)
  # As moc files are generated in the binary dir, tell CMake
  # to always look for includes there:
  set(CMAKE_INCLUDE_CURRENT_DIR ON)

  # Widgets finds its own dependencies (QtGui and QtCore).
  find_package(Qt5Widgets REQUIRED)
  find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Svg REQUIRED)




  # The Qt5Widgets_INCLUDES also includes the include directories for
  # dependencies QtCore and QtGui
  include_directories(${Qt5Widgets_INCLUDES})

  # We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
  add_definitions(${Qt5Widgets_DEFINITIONS})

  # The Qt5Widgets_INCLUDES also includes the include directories for
  # dependencies QtCore and QtGui
  include_directories(${Qt5OpenGL_INCLUDES})

  # We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
  add_definitions(${Qt5OpenGL_DEFINITIONS})

  find_package(OpenGL)

     include_directories(${OPENGL_INCLUDE_DIR} )
     link_libraries(${OPENGL_LIBRARY})



  # Executables fail to build with Qt 5 in the default configuration
  # without -fPIE. We add that here.
  set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS} ${Qt5Svg_EXECUTABLE_COMPILE_FLAGS}")

  add_executable(qt-fbo main.cpp glwidget.cpp)

qt5_use_modules(qt-fbo Widgets OpenGL Svg)

  # The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
  target_link_libraries(qt-fbo ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${Qt5Svg_LIBRARIES})
