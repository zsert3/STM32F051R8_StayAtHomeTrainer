


#include "bluetooth_stringSorter.h"

//delete later
#include "sendReceiveUART.h"


struct {
	int16_t currenRPM;
	int16_t currentTorque;
	int16_t	currentPower;
	int16_t	currentAngle;
	uint16_t	currentSymetry;
	int32_t	remainTime;
	int16_t	calories;
	int16_t	passiveRPM;
	int16_t	minPassiveRPM ;
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
} totalConvertedString, emptystruct, /* delete later */ checker;


union structpiece{
	uint32_t integerpiece;
	char		stringpiece[10];
} currentStructPiece;

union structpiece emptystructpiece;



const int16_t int16Limit = 32767;

volatile char *buffer;
volatile uint8_t  head = 0 , tail = 0;

uint16_t charNumber = 0;
//structpiece currently beingmade
uint8_t	 currentStructNumber = 0;
char newChar;

//sets te default values for the minimum structs
void SetStructDefaults(){
	totalConvertedString.minPassiveRPM = int16Limit;
	totalConvertedString.minDriveTorque = int16Limit;
	totalConvertedString.minBrakeTorque = int16Limit;
	emptystruct.minPassiveRPM = int16Limit;
	emptystruct.minDriveTorque = int16Limit;
	emptystruct.minBrakeTorque = int16Limit;
}

//things that need to be set before the function sort String can be called for the first time
void presetStringSort(){
	head = 0;
	tail = 0;
	SetStructDefaults();
}

//places the correct struct piece in the correct location
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
			if(totalConvertedString.minPassiveRPM > currentStructPiece.integerpiece )
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
			if(totalConvertedString.minDriveTorque > currentStructPiece.integerpiece )
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
			if(totalConvertedString.minBrakeTorque > currentStructPiece.integerpiece )
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

/*
char * stringStruct()
{
	char * structString;
	sprintf(structString, "",
	currenRPM,
	currentTorque,
	currentPower,
	currentAngle,
	currentSymetry,
	remainTime,
	calories,
	passiveRPM,
	minPassiveRPM,
	maxPassiveRPM,
	driveTorque,
	driveTorqueLimit,
	minDriveTorque,
	maxDriveTorque,
	brakeTorque,
	minBrakeTorque,
	maxBrakeTorque,
	trainType,
	trainer,
	deviceMode);
	return structString;
}
*/
void sortStringData()
{
		newChar = buffer[tail];
		
		//places the numbers
		if(newChar >= '0' && newChar <= '9')
		{
			currentStructPiece.integerpiece = (newChar-'0')+(currentStructPiece.integerpiece*10);
			charNumber++;
			moveTail();
		}
		//next piece of the struct
		else if (newChar == '/')
		{
			selectStructpiece(currentStructNumber);
			currentStructNumber++;
			charNumber = 0;
			moveTail();
		}
		//places characters
		else if ((newChar >= 'a' && newChar <= 'z') || (newChar >= 'A' && newChar <= 'Z'))
		{
			currentStructPiece.stringpiece[charNumber] = newChar;
			charNumber++;
			moveTail();
		}
		//end of struct
		else if (newChar == '#')
		{
			//Delete later
			USART_putc(USART2, 'Q');
			currentStructNumber = 0;
			//checker = totalConvertedString;
			totalConvertedString = emptystruct;
			moveTail();
		}
	
}



