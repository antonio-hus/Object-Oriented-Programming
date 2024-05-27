#include "Action.h"

#include <utility>

ActionAdd::ActionAdd(Song addedSong, Repository& repository): repository{repository} {
    this->addedSong = std::move(addedSong);
}

void ActionAdd::executeUndo() {
    this->repository.removeSong(addedSong);
}

void ActionAdd::executeRedo() {
    this->repository.addSong(addedSong);
}

ActionRemove::ActionRemove(Song deletedSong, Repository &repository): repository{repository} {
    this->deletedSong = std::move(deletedSong);
}

void ActionRemove::executeUndo() {
    this->repository.addSong(deletedSong);
}

void ActionRemove::executeRedo() {
    this->repository.removeSong(deletedSong);
}