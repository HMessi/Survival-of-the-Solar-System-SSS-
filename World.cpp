#include <ctime>
#include "gwin.h"
#include "World.h"
#include "Jet.h"
#include "Rocks.h"
#include "Star.h"
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>

#include <math.h>
#include "sound.h"
using namespace std;

//constant variables goes here...
const int MAXJETPOINTS = 12;
const int MAXSCORE = 10;

struct Point
{
	double x;
	double y;
};

//structure for saving player highscores.
struct HighScore
{
	string PlayerName;
	int TotalScore;
};
World::World()
{
	screenWidth = 1100;
	screenHeight = 600;
}

void World::runGame()
{
	HighScore PlayerScore[MAXSCORE];
	ifstream IFfile ("highscore.txt");
	int linecount = 0;
	while (!IFfile.eof())
	{
		IFfile >> PlayerScore[linecount].PlayerName >> PlayerScore[linecount].TotalScore;
		linecount++;
	}

	srand(time(0));

	//Game variables and objects
	GWindow Gwin(screenWidth,screenHeight);
	Gwin.setTitle("Survival of the Solar System");
	Jet jet(100,250);  //position of the je when the game lunch
	GImage background("Store/bakg.png");
	GImage tutorbkg("Store/tutorbkg.png");
	GImage SSSLogo("Store/SSSLogo.png");
	GImage instructionpage("Store/hwto.png");
	GImage gameoverbanner("Store/gmovr.png");
	GImage exit1("Store/exit1.png");
	GImage exit2("Store/exit2.png");
	GImage play1("Store/play1.png");
	GImage play2("Store/play2.png");
	GImage tutor1("Store/tutor1.png");
	GImage tutor2("Store/tutor2.png");
	GImage highscore1("Store/highscore1.png");
	GImage highscore2("Store/highscore2.png");
	GImage jetimage("Store/jet1.png");
	GImage rockimage("Store/stone1.png");
	GImage rockimage2("Store/stone2.png");
	GImage rockimage3("Store/stone3.png");
	int shootCounter = 0;
	int shootDelay = 10;
	std::vector<Rocks> stones;
	int spawnCounter = 0;
	int starSpawnCounter = 0;
	std::vector<Star> stars;
	int spawnDelay = 12;
	int starSpawnDelay = 15;
	GTimer timer;
	timer.start();
	Point jetPoints[MAXJETPOINTS];
	int Score = 0;
	int screen = 1;
	bool gameRun = true;
	bool isPlaying();


	GKey key(0);
	int runMenu = 1;

	GSound sund;
	sund.load("Sound/earth.wav");
	sund.play();


	while (gameRun)
    {

		//MAIN MENU SCREEN
		while(screen == 1)
		{


			if (key == GwinKeyNames::CURSOR_LEFT)
			{
				runMenu+=1;
			}
			if ( key == GwinKeyNames::CURSOR_RIGHT)
			{
				runMenu-= 1;
			}
			if (runMenu == 0)
			{
				runMenu = 1;
			}
			if (runMenu == 5)
			{
				runMenu = 4;
			}

			Gwin.refresh();

			Gwin.drawImage(0,0, &background);
			Gwin.drawImage(200,0,&SSSLogo);
			GFont font("Arial", 15, GwinFontStyles::BOLD);
			Gwin.setFont(&font);
			Gwin.setPenColour(YELLOW);
			Gwin.writeText(Gwin.getWidth()-780,Gwin.getHeight() - 30, "Tips: You can select an option by pressing Right and Left arrow keys.");





			if(runMenu == 1)
			{

				Gwin.drawImage(345,280,&play2);
				Gwin.drawImage(-25,350,&tutor1);
				Gwin.drawImage(700,350,&highscore1);
				Gwin.drawImage(345,450,&exit1);
				Gwin.refresh();
				key = Keyboard.waitKey();

				if(Keyboard.isPressed(GwinKeyNames::RETURN))
				{
					screen = 2;
				}
			}
			else if(runMenu == 2)
			{
				Gwin.drawImage(345,280,&play1);
				Gwin.drawImage(-25,350,&tutor2);
				Gwin.drawImage(700,350,&highscore1);
				Gwin.drawImage(345,450,&exit1);
				Gwin.refresh();
				key = Keyboard.waitKey();
				if(Keyboard.isPressed(GwinKeyNames::RETURN))
				{
					screen = 5;
				}
			}
			else if(runMenu == 3)
			{
				Gwin.drawImage(345,280,&play1);
				Gwin.drawImage(-25,350,&tutor1);
				Gwin.drawImage(700,350,&highscore2);
				Gwin.drawImage(345,450,&exit1);
				Gwin.refresh();
				key = Keyboard.waitKey();
				if (Keyboard.isPressed(GwinKeyNames::RETURN))
				{
					screen = 4;
				}
			}
			else if(runMenu == 4)
			{
				Gwin.drawImage(345,280,&play1);
				Gwin.drawImage(-25,350,&tutor1);
				Gwin.drawImage(700,350,&highscore1);
				Gwin.drawImage(420,450,&exit2);
				Gwin.refresh();
				key = Keyboard.waitKey();
				if(Keyboard.isPressed(GwinKeyNames::RETURN))
				{
					exit(0);
				}
			}
			Gsleep(1);

		}

		while (screen == 5)
		{
			Gwin.clear();
			Gwin.drawImage(0,0,&tutorbkg);
			Gwin.drawImage(320,25, &tutor1);
			Gwin.drawImage(200,162, &instructionpage);
			Gwin.setPenColour(YELLOW);
			GFont font("Arial", 15, GwinFontStyles::BOLD);
			Gwin.setFont(&font);
			Gwin.writeText(320,570, "Please press the 'Backspace' key to go back to the main menu");
			Gwin.refresh();
			key = Keyboard.waitKey();
			if(Keyboard.isPressed(GwinKeyNames::BACKSPACE))
			{
				screen = 1;
			}
			Gwin.refresh();
		}

		//objects positions before the game loop starts
		jet.health = 5;
		Jet jet(100,250);
		Score = 0;
		stones.clear ();


		//GAME SCREEN
		while(screen == 2)
		{
			timer.reset();
			Gwin.clear(BLACK);
			Gwin.setPenColour(WHITE);

			//user input for jet movement
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_UP) && jet.y > 0)
			{
				jet.move(0,-5.5);
			}
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_DOWN) && jet.y < screenHeight - jetimage.getHeight())
			{
				jet.move(0,5.5);
			}
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_LEFT) && jet.x > -40)
			{
				jet.move(-5.5,0);
			}
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_RIGHT) && jet.x < screenWidth - jetimage.getWidth())
			{
				jet.move(5.5,0);
			}
			if(Keyboard.isPressed(GwinKeyNames::BACKSPACE))
			{
				screen = 1;
			}


			if(shootCounter > 0)
			{
				shootCounter--;
			}

			//user input for shooting missiles
			if(shootCounter == 0)
			{
				if(Keyboard.isPressed(GwinKeyNames::SPACE))
					jet.shoot(jet.x+jetimage.getWidth(),jet.y+20,1);

					shootCounter=shootDelay;
			}

			//values of each jet collision point
			jetPoints[0].x = jet.x;
			jetPoints[0].y = jet.y;
			jetPoints[1].x = jet.x + 26.25;
			jetPoints[1].y = jet.y;
			jetPoints[2].x = jet.x + 52.5;
			jetPoints[2].y = jet.y;
			jetPoints[3].x = jet.x + 52.5 +26.25;
			jetPoints[3].y = jet.y;
			jetPoints[4].x = jet.x + 105;
			jetPoints[4].y = jet.y;
			jetPoints[5].x = jet.x + 105;
			jetPoints[5].y = jet.y + 20;
			jetPoints[6].x = jet.x + 105;
			jetPoints[6].y = jet.y + 40;
			jetPoints[7].x = jet.x + 52.5 +26.25;
			jetPoints[7].y = jet.y + 40;
			jetPoints[8].x = jet.x + 52.5;
			jetPoints[8].y = jet.y + 40;
			jetPoints[9].x = jet.x + 26.25;
			jetPoints[9].y = jet.y + 40;
			jetPoints[10].x = jet.x;
			jetPoints[10].y = jet.y + 40;

			//spawn counter
			if(spawnCounter > 0)
			{
				spawnCounter--;
			}

			//star spawn couter
			if(starSpawnCounter > 0)
			{
				starSpawnCounter--;
			}

			//check if it's time to spawn a new rockes
			if(spawnCounter == 0)
			{
				stones.push_back(Rocks(screenWidth+(rand()%100),(rand()%(screenHeight-200))+100,10+(rand()%20)));
				spawnCounter = spawnDelay;
			}

			//check if it's time to spawn a new star
			if(starSpawnCounter == 0)
			{
				stars.push_back(Star(screenWidth+(rand()%100),(rand()%(screenHeight-5))));
				starSpawnCounter = starSpawnDelay;
			}

			//update health of stones and fires after the accedent
			for(int i=0; i<stones.size(); i++)
			{
				for(int j=0; j<jet.fire.size(); j++)
				{
					double dx = jet.fire[j].x-stones[i].x;
					double dxSquared = dx * dx;
					double dy = jet.fire[j].y-stones[i].y;
					double dySquared = dy * dy;
					double distance = sqrt(dxSquared + dySquared);
					if (distance < stones[i].radius)
					{
						while(jet.fire[j].health != 0 && stones[i].health != 0)
						{
							jet.fire[j].health--;
							stones[i].health--;
							Score+=5;
						}
					}
				}
			}





			//check the collision between rocks and jet and reduce the health after the accident
			for (int k = 0; k < stones.size(); k++)
			{
				for(int m = 0; m < MAXJETPOINTS; m++)
				{
					double dx = jetPoints[m].x - stones[k].x;
					double dxSquared = dx * dx;
					double dy = jetPoints[m].y - stones[k].y;
					double dySquared = dy * dy;
					double distanceJetToObstacle = sqrt(dxSquared + dySquared);
					if (distanceJetToObstacle <= stones[k].radius)
					{
						while (jet.health != 0 && stones[k].health != 0)
						{
							jet.health--;
							stones[k].health--;
						}
					}
				}
			}

			//destroy stones that have gone out of the screen or have a health of 0 or less
			for(int i=0; i<stones.size(); i++)//obstacles
			{
				if(stones[i].x + stones[i].radius < 0 || stones[i].health <= 0)
				{
					stones.erase(stones.begin()+i);
					i++;
				}
			}


			//destroy fires that are out of screen or have a health of 0 or less
			for(int i=0; i<jet.fire.size(); i++)
			{
				if(jet.fire[i].x > screenWidth || jet.fire[i].x < 0 || jet.fire[i].y < 0 || jet.fire[i].y > screenHeight || jet.fire[i].health <= 0)
				{
					jet.fire.erase(jet.fire.begin()+i);
					i++;
				}
			}


			//destroy stars that have gone out left of the screen
			for(int i=0; i<stars.size(); i++)//stars
			{
				if(stars[i].x < 0)
				{
					stars.erase(stars.begin()+i);
					i++;
				}
			}




			//update missiles' positions
			for(int i=0; i<jet.fire.size(); i++)
			{
				jet.fire[i].move(jet.fire[i].dx,jet.fire[i].dy);
			}





			//update stars' positions
			for(int i=0; i<stars.size(); i++)
			{
				stars[i].move(stars[i].dx,stars[i].dy);
			}



			//update stones positions and angle
			for(int i=0; i<stones.size(); i++)
			{
				stones[i].move(stones[i].dx,stones[i].dy);
			}



			 //destroy jet if it has a health of 0 or less
			if (jet.health == 0)
			{
				screen = 3;
			}


			//putting everything into GUI
			for(int i=0; i<stars.size(); i++)//stars
			{
				Gwin.setPenColour(YELLOW);

				Gwin.circle(stars[i].x, stars[i].y,1);
			}

			Gwin.drawImage(jet.x,jet.y,&jetimage);//jet

			for(int i=0; i<stones.size(); i++)//rocks
			{
				if(stones[i].health == 3)

					Gwin.drawImageScaled(stones[i].x,stones[i].y-stones[i].radius,stones[i].radius*2,stones[i].radius*2,&rockimage);
				else if(stones[i].health == 2)

					Gwin.drawImageScaled(stones[i].x,stones[i].y-stones[i].radius,stones[i].radius*2,stones[i].radius*2,&rockimage2);
				else if(stones[i].health == 1)

					Gwin.drawImageScaled(stones[i].x,stones[i].y-stones[i].radius,stones[i].radius*2,stones[i].radius*2,&rockimage3);

			}



			for(int i=0; i<jet.fire.size(); i++)//fire
			{

                Gwin.setPenColour(YELLOW);
				Gwin.circle(jet.fire[i].x,jet.fire[i].y,4);
			}

			//showiing the health and the score
			GFont font("Arial", 20);
			Gwin.setFont(&font);
			Gwin.setPenColour(WHITE);
			Gwin.writeText(100, 8, "Jet Health: ");
			Gwin.writeInt(200, 8, jet.health);
			Gwin.writeText(screenWidth-225, 8, "Score: ");
			Gwin.writeInt(screenWidth-163, 8, Score);

			Gwin.refresh();



		}

		//GAME OVER SCREEN
		while(screen == 3)
		{
			Gwin.clear(BLACK);
			GFont font("Arial", 25, GwinFontStyles::BOLD);
			Gwin.setFont(&font);
			Gwin.setPenColour(RED);

			Gwin.drawImage(300,20, &gameoverbanner);
			Gwin.writeText(150,200,"CONTRATULATIONS! Your have achieved a high score");
			Gwin.writeText(150,300, "Your total score: ");
			Gwin.writeText(150,350, "Please enter your name: ");
			GFont font1("Arial", 15, GwinFontStyles::BOLD);
			Gwin.setFont(&font1);
			Gwin.setPenColour(RED);
			Gwin.writeText(300,Gwin.getHeight() - 30, "Press 'Enter' after you have entered your name");

			//finding the minimum score in the hgihscore list
			int x = 0;
			int min = PlayerScore[0].TotalScore;
			for ( int i = 1; i < MAXSCORE; i++)
			{
				if(PlayerScore[i].TotalScore < min)
				{
					min = PlayerScore[i].TotalScore;
					x = i;
				}
			}

			GFont font2("Arial", 25, GwinFontStyles::BOLD);
			Gwin.setFont(&font2);
			Gwin.setPenColour(GREEN);

			Gwin.writeInt(400,300,Score); //showing the player score in game over screen. if new score is higher than the minimum score then ask for player's name.
			if (Score > PlayerScore[x].TotalScore)
			{
				PlayerScore[x].TotalScore = Score;
				PlayerScore[x].PlayerName = Gwin.readString(500,350,20);
			}

			ofstream OFfile; //Writting everything from the struct into the file
			OFfile.open("highscore.txt");
			for (int i = 0; i < MAXSCORE; i++)
			{
				OFfile << PlayerScore[i].PlayerName << " " << PlayerScore[i].TotalScore << endl;
			}

			OFfile.close();

			screen = 4;
			Gwin.refresh();
		}

		//displaying the high score assendently
		while (screen == 4)
		{
			Gwin.clear(BLACK);

			Gwin.drawImage(300,20, &highscore1);
			GFont font("Arial", 15, GwinFontStyles::BOLD);
			Gwin.setFont(&font);
			Gwin.setPenColour(YELLOW);
			Gwin.writeText(300,Gwin.getHeight() - 30, "Please press the 'Backspace' key to go back to the main menu");
			Gwin.setPenColour(LIGHTBLUE);


			int tempscore;
			string tempname;

			//the bubble sort to sort asecndindly
			for( int i = 0; i <= MAXSCORE-2; i++)
			{
				for (int j = i+1; j<=MAXSCORE-1; j++)
				{
					if(PlayerScore[i].TotalScore < PlayerScore[j].TotalScore)
					{
						tempscore = PlayerScore[i].TotalScore;
						tempname = PlayerScore[i].PlayerName;
						PlayerScore[i].TotalScore = PlayerScore[j].TotalScore;
						PlayerScore[i].PlayerName = PlayerScore[j].PlayerName;
						PlayerScore[j].TotalScore = tempscore;
						PlayerScore[j].PlayerName = tempname;
					}
				}
			}


			int nln = 175;
			for (int i = 0; i < MAXSCORE; i++)
			{
				Gwin.writeString(400,nln,PlayerScore[i].PlayerName);
				Gwin.writeInt(620, nln,PlayerScore[i].TotalScore);
				nln= nln+35;

			}
			Gwin.refresh();
			key = Keyboard.waitKey();
			if(Keyboard.isPressed(GwinKeyNames::BACKSPACE))
			{
				screen = 1;
			}
			Gwin.refresh();
		}
	Gwin.refresh();
	}
}
