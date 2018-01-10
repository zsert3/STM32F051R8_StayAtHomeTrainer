


#include "bluetooth_stringSorter.h"

//delete later
#include "sendReceiveUART.h"
#include <math.h>


struct {
	int16_t currenRPM;
	int16_t currentTorque;
	int16_t	currentPower;
	int16_t	currentAngle;
	uint16_t	currentSymetry;
	int32_t	remainTime;
	int16_t	calories;
	int16_t	passiveRPM;
	int16_t	minPassiveRPM;
	int16_t	maxPassiveRPM;
	int16_t	driveTorque;
	int16_t	driveTorqueLimit;
	int16_t	minDriveTorque;
	int16_t	maxDriveTorque;
	int16_t	brakeTorque;
	int16_t	minBrakeTorque;
	int16_t	maxBrakeTorque;
	char	trainType[10];
	char	trainer[10];
	char	deviceMode[10];
} totalConvertedString , emptystruct;



union structpiece{
	uint32_t integerpiece;
	char		stringpiece[10];
} currentStructPiece;

union structpiece emptystructpiece;




volatile char *buffer;
volatile uint8_t  head = 0 , tail = 0;

uint16_t charNumber = 0;
uint8_t	 currentStructNumber = 0;
char newChar;

//delte later
uint16_t backresultcounter = 0;

void resetHeadTail(){
	head = 0;
	tail = 0;
}

void selectStructpiece(uint8_t pieceNumber){
	switch(pieceNumber){
		case 0:
		 totalConvertedString.currenRPM = currentStructPiece.integerpiece;
		break;
		case 1:
			totalConvertedString.currentTorque = currentStructPiece.integerpiece;
		break;
		case 2:
			totalConvertedString.currentPower = currentStructPiece.integerpiece;
		break;
		case 3:
			totalConvertedString.currentAngle = currentStructPiece.integerpiece;
		break;
		case 4:
			totalConvertedString.currentSymetry = currentStructPiece.integerpiece;
		break;
		case 5:
			totalConvertedString.remainTime = currentStructPiece.integerpiece;
		break;
		case 6:
			totalConvertedString.calories = currentStructPiece.integerpiece;
		break;
		case 7:
			totalConvertedString.passiveRPM = currentStructPiece.integerpiece;
		break;
		case 8:
			if(totalConvertedString.minPassiveRPM > currentStructPiece.integerpiece || totalConvertedString.minPassiveRPM == 0)
				totalConvertedString.minPassiveRPM = currentStructPiece.integerpiece;
		break;
		case 9:
			if(totalConvertedString.maxPassiveRPM < currentStructPiece.integerpiece)
				totalConvertedString.maxPassiveRPM = currentStructPiece.integerpiece;
		break;
		case 10:
			totalConvertedString.driveTorque = currentStructPiece.integerpiece;
		break;
		case 11:
			totalConvertedString.driveTorqueLimit = currentStructPiece.integerpiece;
		break;
		case 12:
			if(totalConvertedString.minDriveTorque > currentStructPiece.integerpiece || totalConvertedString.minDriveTorque == 0)
				totalConvertedString.minDriveTorque = currentStructPiece.integerpiece;
		break;
		case 13:
			if(totalConvertedString.maxDriveTorque < currentStructPiece.integerpiece)
				totalConvertedString.maxDriveTorque = currentStructPiece.integerpiece;
		break;
		case 14:
			totalConvertedString.brakeTorque = currentStructPiece.integerpiece;
		break;
		case 15:
			if(totalConvertedString.minBrakeTorque > currentStructPiece.integerpiece || totalConvertedString.minBrakeTorque == 0)
				totalConvertedString.minBrakeTorque = currentStructPiece.integerpiece;
		break;
		case 16:
			if(totalConvertedString.maxBrakeTorque < currentStructPiece.integerpiece)
				totalConvertedString.maxBrakeTorque = currentStructPiece.integerpiece;
		break;
		case 17:
			strcpy( totalConvertedString.trainType , currentStructPiece.stringpiece );
		break;
		case 18:
			strcpy( totalConvertedString.trainer, currentStructPiece.stringpiece );
		break;
		case 19:
			strcpy(totalConvertedString.deviceMode , currentStructPiece.stringpiece );
		break;
	}
	currentStructPiece = emptystructpiece;
}

void moveTail()
{
	if(tail >= 99)
	{
		tail = 0;
	}
	else{
		tail++;
	}
}



void sortStringData(){

		newChar = buffer[tail];
		
	
		if(newChar >= '0' && newChar <= '9')
		{
			currentStructPiece.integerpiece = (newChar-'0')+(currentStructPiece.integerpiece*10);//(10*(charNumber))*(newChar-'0');
			
			charNumber++;
			moveTail();
		}
		else if (newChar == '/')
		{
			selectStructpiece(currentStructNumber);
			currentStructNumber++;
			charNumber = 0;
			moveTail();
		}
		else if (newChar >= 'a' && newChar <= 'z')
		{
			currentStructPiece.stringpiece[charNumber] = newChar;
			charNumber++;
			moveTail();
		}
		else if (newChar >= 'A' && newChar <= 'Z')
		{
			currentStructPiece.stringpiece[charNumber] = newChar;
			charNumber++;
			moveTail();
		}
		else if (newChar == '#')
		{
			totalConvertedString = emptystruct;
			moveTail();
		}
	
}



