//#pragma once
#define SHOT_SIZE_X 32
#define SHOT_SIZE_Y 32

#define SHOT_MAX 1

class Shot
{

private:
	//ÉÅÉìÉoïœêî
	int ShotImage;
	int ShotPosX;
	int ShotPosY;
	int Shotflag;
	int ShotSpeed;
public:
	Shot(const char image[]);
	~Shot();
public:
	void SystemInit(void);
	void GameInit(void);
	void Control(void);
	void Draw(void);

	void CreateShot(XY pos);
	void DeleteShot(void);

	XY GetPos(void);
	XY GetSize(void);
	bool visible(void);

};