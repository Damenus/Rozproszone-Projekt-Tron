#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Player.h"


Player::Player(){
	this->x=0;
	this->y=0;
	this->direction_x = 1;
	this->direction_y = 0;
	rect = new SDL_Rect();
	
	}

	Player::Player(int nowyid, int nowyx, int nowyy){
		this->x = nowyx;
		this->y = nowyy;
		this->id = nowyid;
		this->direction_x = 1;
		this->direction_y = 0;
		rect = new SDL_Rect();
	}

	Player::~Player() {

	}

	void Player::newPosition() {
		this->x += this->direction_x;
		this->y += this->direction_y;

		//stary kod, renderowanie na podstawie pozycje poprzedniej na ekranie
		////bo mnozymy albo razy 1, albo -1 albo 0
		//this->rect->x += this->direction_x*(this->rect->w);
		//this->rect->y += this->direction_y*(this->rect->h);

		//nowy kod, renderowanie na podstawie pozycji w tablicy
		this->rect->x = this->x*this->rect->w;
		this->rect->y = this->y*this->rect->h;

	}

	int Player::getX(){
		return this->x;
	}

	void Player::setX(int x){
		this->x = x;
		
	}

	int Player::getY()
	{
		return this->y;
	}

	void Player::setY(int y){
		this->y = y;
		
	}

	int Player::getDirection(){
		return this->direction;
	}

	int Player::getDirectionX(){
		return this->direction_x;
	}

	Texture Player::getVehicleTexture(){
		return this->vehicleTexture;
	}

	Texture * Player::getTrailTexture()
	{
		return &(this->trailTexture);
	}

	SDL_Rect * Player::getRect()
	{
		return this->rect;
	}

	void Player::setDirectionX(int nowyx){
		this->direction_x = nowyx;
	}

	int Player::getDirectionY(){
		return this->direction_y;
	}

	void Player::setDirectionY(int nowyy){
		this->direction_y = nowyy;
	}

	int Player::getId()
	{
		return id;
	}

	//wczytywanie textur
	bool Player::loadVehTexture(std::string path, SDL_Renderer* winRenderer)
	{
		if (this->vehicleTexture.loadFromFile(path, winRenderer))	//metoda tekstury na wczytanie
		{	
			//jak sie udalo, to przypisz rozmiar obrazka rectowi
			rect->h = vehicleTexture.getHeight();
			rect->w = vehicleTexture.getWidth();
			rect->x = this->x;
			rect->y = this->y;
			return true;
			
		}
		else
			return false;
	
	}

	bool Player::loadTrailTexture(std::string path, SDL_Renderer* winRenderer)
	{
		if (this->trailTexture.loadFromFile(path, winRenderer))	//metoda tekstury na wczytanie
			return true;
		else
			return false;

	}

	//renderowanie
	void Player::renderVehicle (SDL_Renderer* winRenderer,double angle)
	{
		this->vehicleTexture.render(this->rect, winRenderer, angle);
	}


	void Player::renderTrail(SDL_Rect * rect,SDL_Renderer* winRenderer)
	{

		this->trailTexture.render(rect, winRenderer, 0);
	}


	void Player::freeTextures()
	{
		vehicleTexture.free();
		trailTexture.free();
	}

	//jak serwer bedzie zwracac pozycje startowe, to tutaj trzeba ja przekazywac
	//zeby resetowala w odpowiednim miejscu
	void Player::reset()
	{
		
		this->x=0;
		this->y = 0;
		this->rect->x = 0;
		this->rect->y = 0;
		this->direction_x = 1;
		this->direction_y = 0;
	}

	void Player::setDirection(int nowy){
		if (nowy == up) {
			this->direction = up;
			setDirectionX(0);
			setDirectionY(-1);
		}
		else if (nowy == down) {
			this->direction = down;
			setDirectionX(0);
			setDirectionY(1);
		}
		else if (nowy == right) {
			this->direction = right;
			setDirectionX(1);
			setDirectionY(0);
		}
		else if (nowy == left) {
			this->direction = left;
			setDirectionX(-1);
			setDirectionY(0);
		}

	}