#include <stdio.h>
#include "Types.h"
#include <string.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	uint8_t u8iLoc;
	EN_terminalError_t enuTerminalError;
	printf("PLease, Enter the transaction date(DD/MM/YYYY): ");
	gets(termData->transactionDate);
	if(((strlen(termData->transactionDate)==10) && (termData->transactionDate[2]=='/') && (termData->transactionDate[5]=='/')) && (termData->transactionDate != NULL))
	{
		for(u8iLoc=0;u8iLoc<strlen(termData->transactionDate);u8iLoc++)
		{
			if(((termData->transactionDate[u8iLoc] >= '0')&&(termData->transactionDate[u8iLoc] <= '9'))||((termData->transactionDate[u8iLoc]=='/')))
			{
				if(u8iLoc==strlen(termData->transactionDate)-1)
				{
					enuTerminalError = TERMINAL_OK;
				}
			}
			else
			{
				enuTerminalError = WRONG_DATE;
				break;
			}
		}
	}
	else
	{
		enuTerminalError = WRONG_DATE;
	}

	return enuTerminalError;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	EN_terminalError_t enuTerminalError;
	if(cardData->cardExpirationDate[3] > termData->transactionDate[8])
	{
		enuTerminalError = TERMINAL_OK;
	}
	else if(cardData->cardExpirationDate[3] == termData->transactionDate[8])
	{
		if(cardData->cardExpirationDate[4] > termData->transactionDate[9])
		{
			enuTerminalError = TERMINAL_OK;
		}
		else if(cardData->cardExpirationDate[4] == termData->transactionDate[9])
		{
			if(cardData->cardExpirationDate[0] > termData->transactionDate[3])
			{
				enuTerminalError = TERMINAL_OK;
			}
			else if(cardData->cardExpirationDate[0] == termData->transactionDate[3])
			{
				if(cardData->cardExpirationDate[1] >= termData->transactionDate[4])
				{
					enuTerminalError = TERMINAL_OK;
				}
				else
				{
					enuTerminalError = EXPIRED_CARD;
				}
			}
			else
			{
				enuTerminalError = EXPIRED_CARD;
			}
		}
		else
		{
			enuTerminalError = EXPIRED_CARD;
		}
	}
	else
	{
		enuTerminalError = EXPIRED_CARD;
	}
	return enuTerminalError;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	EN_terminalError_t enuTerminalError;
	printf("PLease, Enter the transaction amount: ");
	scanf("%f",&termData->transAmount);
	if(termData->transAmount > 0)
	{
		enuTerminalError = TERMINAL_OK;
	}
	else
	{
		enuTerminalError = INVALID_AMOUNT;
	}
	return enuTerminalError;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	EN_terminalError_t enuTerminalError;
	if((termData->transAmount) > (termData->maxTransAmount))
	{
		enuTerminalError = EXCEED_MAX_AMOUNT;
	}
	else
	{
		enuTerminalError = TERMINAL_OK;
	}
	return enuTerminalError;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
	EN_terminalError_t enuTerminalError;
	termData->maxTransAmount = 5000;
	if(termData->maxTransAmount > 0)
	{
		enuTerminalError = TERMINAL_OK;
	}
	else
	{
		enuTerminalError = INVALID_MAX_AMOUNT;
	}
	return enuTerminalError;
}





























