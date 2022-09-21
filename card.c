#include <stdio.h>
#include "Types.h"
#include "card.h"
#include <string.h>
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	uint8_t u8iLoc;
	EN_cardError_t enuCardError;
	printf("PLease, Enter the cardholder's name: ");
	gets(cardData->cardHolderName);
	if(((strlen(cardData->cardHolderName)<=24) && (strlen(cardData->cardHolderName)>=20)) && (cardData->cardHolderName != NULL))
	{
		for(u8iLoc=0;u8iLoc<strlen(cardData->cardHolderName);u8iLoc++)
		{
			if(((cardData->cardHolderName[u8iLoc] >= 'a')&&(cardData->cardHolderName[u8iLoc] <= 'z'))||((cardData->cardHolderName[u8iLoc] >= 'A')&&(cardData->cardHolderName[u8iLoc] <= 'Z')) || (cardData->cardHolderName[u8iLoc] == ' '))
			{
				if(u8iLoc==strlen(cardData->cardHolderName)-1)
				{
					enuCardError = OK;
				}
			}
			else
			{
				enuCardError = WRONG_NAME;
				break;
			}
		}
	}
	else
	{
		enuCardError = WRONG_NAME;
	}
	return enuCardError;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	uint8_t u8iLoc;
	EN_cardError_t enuCardError;
	printf("PLease, Enter the card expiry date(MM/YY): ");
	gets(cardData->cardExpirationDate);
	if(((strlen(cardData->cardExpirationDate)==5) && (cardData->cardExpirationDate[2]=='/')) && (cardData->cardExpirationDate != NULL))
	{
		for(u8iLoc=0;u8iLoc<strlen(cardData->cardExpirationDate);u8iLoc++)
		{
			if(((cardData->cardExpirationDate[u8iLoc] >= '0')&&(cardData->cardExpirationDate[u8iLoc] <= '9'))||((cardData->cardExpirationDate[u8iLoc]=='/')))
			{
				if(u8iLoc==strlen(cardData->cardExpirationDate)-1)
				{
					enuCardError = OK;
				}
			}
			else
			{
				enuCardError = WRONG_EXP_DATE;
				break;
			}
		}
	}
	else
	{
		enuCardError = WRONG_EXP_DATE;
	}

	return enuCardError;

}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	uint8_t u8iLoc;
	EN_cardError_t enuCardError;
	printf("PLease, Enter the card's Primary Account Number: ");
	gets(cardData->primaryAccountNumber);
	if((strlen(cardData->primaryAccountNumber)<=19) && (strlen(cardData->primaryAccountNumber) >= 16) && (cardData->primaryAccountNumber != NULL))
	{
		for(u8iLoc=0;u8iLoc<strlen(cardData->primaryAccountNumber);u8iLoc++)
		{
			if((cardData->primaryAccountNumber[u8iLoc] >= '0')&&(cardData->primaryAccountNumber[u8iLoc] <= '9'))
			{
				if(u8iLoc==strlen(cardData->primaryAccountNumber)-1)
				{
					enuCardError = OK;
				}
			}
			else
			{
				enuCardError = WRONG_PAN;
				break;
			}
		}
	}
	else
	{
		enuCardError = WRONG_PAN;
	}
	return enuCardError;
}
