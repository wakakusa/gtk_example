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
# SHARED Libraryのバージョン
SET(soserial "1.0.0")

SET(TARGET "library")
SET(ADD library.c)
SET(COMPILE_SORCE ${ADD})

#　サブディレクトリ(各，サブディレクトリにもCMakeLists.txtを置く)
#add_subdirectory(test)
#add_subdirectory(sample)

# 生成するライブラリ名，元となるソース
#add_library(Hello ${PROJECT_SOURCE_DIR}/hello.c ${PROJECT_SOURCE_DIR}/hello2.c)
# SHARED Libraryの場合
 add_library(${TARGET} SHARED ${COMPILE_SORCE})


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


