cmake_minimum_required(VERSION 3.27)
project(Seminar4)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        Seminar4
        main.cpp
        CSVPlaylist.cpp
        CSVPlaylist.h
        FilePlaylist.cpp
        FilePlaylist.h
        PlayList.cpp
        PlayList.h
        Repository.cpp
        Repository.h
        RepositoryExceptions.cpp
        RepositoryExceptions.h
        Service.cpp
        Service.h
        Song.cpp
        Song.h
        SongValidator.cpp
        SongValidator.h
        UI.cpp
        UI.h
        Utils.cpp
        Utils.h
        Action.cpp
        Action.h
)
