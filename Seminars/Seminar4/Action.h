#ifndef SEMINAR4_ACTION_H
#define SEMINAR4_ACTION_H

#include "Song.h"
#include "Repository.h"

class Action {
public:
    virtual void executeUndo()=0;
    virtual void executeRedo()=0;
};

class ActionAdd: public Action {
private:
    Song addedSong;
    Repository repository;

public:
    ActionAdd(Song addedSong, Repository& repository);
    void executeUndo();
    void executeRedo();
};

class ActionRemove: public Action {
private:
    Song deletedSong;
    Repository repository;

public:

    ActionRemove(Song deletedSong, Repository& repository);
    void executeUndo();
    void executeRedo();
};

class ActionUpdate {
private:
public:
};


#endif
