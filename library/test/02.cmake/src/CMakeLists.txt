#必要に応じて不要なコマンドは削除のこと！
#cmake 実行時のオプション（GUIで設定可能）
#アーキテクテャに依存する場合は、cmakeのオプションで設定する
#SET(CMAKE_C_FLAGS "-O3 -march=corei7-avx")
#cmake 必要バージョン
cmake_minimum_required(VERSION 2.8)
# プロジェクト名
project(library)
#バージョン番号
SET(serial "1.0.0")
#ビルドタイプ
SET(CMAKE_BUILD_TYPE release)
#インストール場所
SET(CMAKE_INSTALL_PREFIX /usr/bin)

###### EXECUTABLE&SORCE_DEFINE #####
#作成ターゲットの設定 
SET(TARGET "sample")

SET(MAIN main.c)
SET(COMPILE_SORCE ${MAIN})


#GTKの設定
#include(FindPkgConfig)
#pkg_check_modules(GMODULE gmodule-2.0)
#pkg_check_modules(GTK gtk+-2.0)
#pkg_check_modules(VTE vte) 
#include_directories(${GTK_INCLUDE_DIRS} ${VTE_INCLUDE_DIRS})
#link_directories(${GTK_LIBRARY_DIRS} ${VTE_LIBRARY_DIRS})
#link_libraries(${GTK_LIBRARIES} ${VTE_LIBRARIES})

# Includeファイルの場所
#include_directories(hello/include)

#LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
LINK_DIRECTORIES(${PROJECT_LIBRARY_DIR})

#SET(PROJECT_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)

###### EXECUTABLE&SORCE_DEFINE #####
# 実行ファイルの生成
add_executable(${TARGET} ${COMPILE_SORCE})

# ライブラリのリンクの設定
link_libraries(${PROJECT_LIBRARY_DIR} library)
target_link_libraries(${TARGET} library)

######Compiler Option コンパイラの種類によってオプションを変更#####
# コンパイル時のオプション(OpenMP http://www.cmake.org/pipermail/cmake/2009-January/026607.html)
#ここの書き方は、GCC用　LINKER　FLAGSはビルド時間の短縮のため https://www.grapecity.com/japan/powernews/column/clang/003/page02.htm#1
if(MINGW)
  set(CMAKE_C_FLAGS -mms-bitfields)
  set(CMAKE_CXX_FLAGS -mms-bitfields)
  set(CMAKE_EXE_LINKER_FLAGS -mwindows)
endif(MINGW)

if(CMAKE_C_COMPILER MATCHES "icc")
  MESSAGE("Compiler's setting is Intel Compiler")
  #C用コンパイラの指定&コンパイラオプション
  SET(CMAKE_C_COMPILER icc)
  SET(CMAKE_C_FLAGS "-xhost -ipo -openmp")
  #C++用コンパイラの指定&コンパイラオプション
  SET(CMAKE_CXX_COMPILER icpc)
  SET(CMAKE_CXX_FLAGS "-xhost -ipo -openmp")
else()
  MESSAGE("Compiler's setting is GNU Compiler")
  #C用コンパイラの指定&コンパイラオプション
  SET(CMAKE_C_COMPILER gcc)
  SET(CMAKE_C_FLAGS "-O0 -g -pipe")
  #SET(CMAKE_EXE_LINKER_FLAGS -lgomp)#コンパイラのオプションによっては削除のこと
  #C++用コンパイラの指定&コンパイラオプション
  SET(CMAKE_CXX_COMPILER g++)
  SET(CMAKE_CXX_FLAGS "-O0 -g -pipe")
endif()
