/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {

   for (int i = 0; i < numberOfRobots; i++) {
       Robot* robot = new Robot();
       while(!isEmpty(*robot)){
           delete robot;
           robot = new Robot();
       }
       robots.push_back(robot);
   }
   teleportHero();
}

GameState::GameState(const GameState& gameState){
    for (auto robot: gameState.robots){
        this->robots.push_back(robot->clone());
    }
    this->hero = gameState.hero;
}

GameState& GameState::operator=(const GameState& gameState){

    for (auto robot: this->robots){
        delete robot;
    }

    robots.clear();

    for (auto robot : gameState.robots){
        this->robots.push_back(robot->clone());
    }

    this->hero = gameState.hero;

    return *this;

}


GameState::~GameState(){
    for(auto robot: this->robots){
        delete robot;
    }
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const Robot* robot: robots){
        robot->draw(scene);
    }

}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Robot* robot: robots)
        robot->moveTowards(hero);
}


void GameState::updateCrashes() {
    for(unsigned i=0; i < robots.size(); ++i){
        for(unsigned o=i+1; o < robots.size(); ++o){
            if(robots[i]->at(robots[o]->asPoint())){
                robots[i]->doCrash();
                robots[o]->doCrash();
            }
        }
    }
}

int GameState::countJustCrashed()const{
    int numberDestroyed =0;
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->justCrashed())
            numberDestroyed++;
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < robots.size(); ++i){
        if (robots[i]->justCrashed()) {
            Robot* newJunk = new Junk(robots[i]->asPoint());
            delete robots[i];
            robots[i] = newJunk;
        }
    }
}

bool GameState::stillLiveRobots() const {
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->canMove())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for(const Robot* robot: robots){
        if(hero.at(robot->asPoint())){
            return true;
        }
    }
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit) const {
    for(const Robot* robot: robots)
        if(robot->at(unit))
            return false;
    return true;
}

