#include "Pacman.h"

Pacman::Pacman(){
    setLives(3);
    setStatus(ALIVE);
}

Pacman::~Pacman(){
	//UnloadTexture(this->texture);
}

//  Returns number of lives Pacman has left
int Pacman::getLives(){

    return this->lives;

}

//  Set the number of lives
void Pacman::setLives(int lives){
    
    this->lives = lives;

}

void Pacman::setAng(float ang){
    
    this->ang = ang;
}

float Pacman::getAng(){
    
    return this->ang;

}

void Pacman::setScale(float scale){
    
    this->scale = scale;
}

float Pacman::getScale(){
    
    return this->scale;

}
