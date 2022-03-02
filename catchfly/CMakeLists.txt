cmake_minimum_required(VERSION 3.5)

project(catchfly VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置自动生成moc文件,AUTOMOC打开可以省去QT5_WRAP_CPP命令 ## 解决emit 报错 undefined reference to  问题
SET(CMAKE_AUTOMOC ON)
## 设置自动生成ui_xxx.h文件,AUTOUIC打开可以省去QT5_WRAP_UI命令
SET(CMAKE_AUTOUIC ON)
## 【optional】设置自动处理.qrc文件
SET(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui PrintSupport Sql Xml Network Concurrent)

set(HEADER_FILES
    mainwindow.h
    global.h
    globalplus.h

    Plot/CandleCreatorDF.h

    Board/containsshow/CandleBoardContains.h

    RealTime/RealtimeData.h
    RealTime/boardsnapshot.h
    RealTime/RealtimeMonitor.h

    qcustomplot.h

)

set(SOURCE_FILES
    main.cpp
    mainwindow.cpp

    Plot/CandleCreatorDF.cpp

    Board/containsshow/CandleBoardContains.cpp

    RealTime/RealtimeData.cpp
    RealTime/boardsnapshot.cpp
    RealTime/RealtimeMonitor.cpp

    qcustomplot.cpp
)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5Sql_INCLUDE_DIRS}
  ${Qt5PrintSupport_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}/5.15.2/QtWidgets ## I:/CXXTools/Qt/5.15.2/mingw81_64/include/QtWidgets  所需文件：I:\CXXTools\Qt\5.15.2\mingw81_64\include\QtWidgets\5.15.2\QtWidgets\private + <private/qtableview_p.h>
)

##引入UI文件：
set(UI_FILES
    mainwindow.ui
    Board/containsshow/CandleBoardContains.ui
    RealTime/boardsnapshot.ui
)

# 【optional】生成UI文件夹
SOURCE_GROUP("UI" FILES ${UI_FILES})


# dataframe =====================================================================================================
list(APPEND CMAKE_PREFIX_PATH I:/CXXlibs/DATAFRAME/DataFrame-2022-02-28/cmakeinstalled/lib/cmake/DataFrame)
find_package(DataFrame REQUIRED)
include_directories("I:/CXXlibs/DATAFRAME/DataFrame-2022-02-28/cmakeinstalled/include")
include_directories("I:/CXXlibs/DATAFRAME/DataFrame-2022-02-28/cmakeinstalled/lib")
# ================================================================================================================


# 生成可执行文件 *******************************************************************************
ADD_EXECUTABLE(catchfly ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})

target_link_libraries(catchfly PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui Qt5::PrintSupport Qt5::Sql Qt5::Xml Qt5::Network Qt5::Concurrent)
#target_link_libraries(catchfly PRIVATE Qt5::CorePrivate Qt5::WidgetsPrivate)


# dataframe =======================================================================================================
##target_link_libraries(${PROJECT_NAME} PRIVATE DataFrame)
target_link_libraries(${PROJECT_NAME} PRIVATE DataFrame::DataFrame)
# =================================================================================================================

