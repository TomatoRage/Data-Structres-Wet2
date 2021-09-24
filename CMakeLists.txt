cmake_minimum_required(VERSION 3.20)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled1 main.cpp library.h BinarySearchTree.h BinarySearchTreeImp.h Image.cpp Image.h SuperPixel.cpp SuperPixel.h FlippedTree.h library.cpp ImageTagger.cpp ImageTagger.h)
