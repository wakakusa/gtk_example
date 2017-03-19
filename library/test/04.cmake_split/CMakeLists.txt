#cmake 必要バージョン
cmake_minimum_required(VERSION 2.8)
# プロジェクト名
project(library_test)
#バージョン番号
SET(serial "1.0.0")
#ビルドタイプ
SET(CMAKE_BUILD_TYPE release)
#インストール場所
SET(CMAKE_INSTALL_PREFIX /usr/bin)

#ファイル所在の設定 
SET(PROJECT_DIR ${PROJECT_SOURCE_DIR})
SET(PROJECT_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)
SET(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

###### EXECUTABLE&SORCE_DEFINE #####
#作成ターゲットの設定 
SET(TARGET_LIB1 "mylibrary1")
SET(TARGET_LIB2 "mylibrary2")
SET(TARGET_EXE "test_lib")

#　サブディレクトリ(各，サブディレクトリにもCMakeLists.txtを置く)
ADD_SUBDIRECTORY(${PROJECT_LIBRARY_DIR})
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR})

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
  SET(CMAKE_C_FLAGS "-g -pipe")
  #SET(CMAKE_EXE_LINKER_FLAGS -lgomp)#コンパイラのオプションによっては削除のこと
  #C++用コンパイラの指定&コンパイラオプション
  SET(CMAKE_CXX_COMPILER g++)
  SET(CMAKE_CXX_FLAGS "-g -pipe")
endif()
