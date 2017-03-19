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
SET(PROJECT_LIBRARY_SUBDIR1 ${PROJECT_SOURCE_DIR}/lib1)
SET(PROJECT_LIBRARY_SUBDIR2 ${PROJECT_SOURCE_DIR}/lib2)

###### EXECUTABLE&SORCE_DEFINE #####
#作成ターゲットの設定 
#SET(TARGET_LIB "mylibrary")
SET(TARGET_EXE "test_lib")

#　サブディレクトリ(各，サブディレクトリにもCMakeLists.txtを置く)
ADD_SUBDIRECTORY(${PROJECT_LIBRARY_SUBDIR1})
ADD_SUBDIRECTORY(${PROJECT_LIBRARY_SUBDIR2})

