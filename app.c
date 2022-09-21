#include <stdio.h>
#include <string.h>

#include "Types.h"


#include "app.h"

int appStart(void)
{
	// From the Flow Chart 
	// Card Module
	// Global Variables For Card Data (pointer to structure)
	ST_cardData_t strCardHolderData;
	ST_cardData_t* strCardData = &strCardHolderData;

	// Card Errors 
	EN_cardError_t enuCard_holder_name_error ;
	
	do
	{
		enuCard_holder_name_error = getCardHolderName(strCardData);
		// get the Card Holder Name and check the Validity
		if (enuCard_holder_name_error == WRONG_NAME)
		{
			printf("Wrong Name !, please enter a valid name\n");
			//return 0;
		}
		else
		{
			break;
		}
	}while(1);
	

	EN_cardError_t enuCard_expiry_date_error ;
	
	do
	{
		enuCard_expiry_date_error = getCardExpiryDate(strCardData);
			// get the Card Expiry Date and check the Validity
		if (enuCard_expiry_date_error == WRONG_EXP_DATE)
		{
			printf("Wrong Expiry Date !, please enter a valid name\n");
			//return 0;
		}
		else
		{
			break;
		}
	}while(1);
	
	EN_cardError_t enuCard_PAN_error ;
	do
	{
		enuCard_PAN_error = getCardPAN(strCardData);
			// get the Card PAN and check the Validity
		if (enuCard_PAN_error == WRONG_PAN)
		{
			printf("Wrong Primary Account Number !, please enter a valid PAN\n");
			//return 0;
		}
		else
		{
			break;
		}
	}while(1);
	
	
	// From the Flow Chart 
	// Terminal Module

	// Global Variables For terminal Data (pointer to structure)
	ST_terminalData_t strTerminal_data;
	ST_terminalData_t* strTermData = &strTerminal_data;

	// Terminal Errors
	EN_terminalError_t enuTransactionDate;
	do
	{
		enuTransactionDate = getTransactionDate(strTermData);
		// get the transaction date and check the Validity
		if (enuTransactionDate == WRONG_DATE)
		{
			printf("Wrong Date !, please enter a valid date\n");
			//return 0;
		}
		else
		{
			break;
		}
	}while(1);
	EN_terminalError_t enuCardExpired ;
	
	do
	{
		enuCardExpired = isCardExpired(strCardData, strTermData);
		// check the card is expired or not 
		if (enuCardExpired == EXPIRED_CARD)
		{
			printf("This Card is Expired !, please enter a valid card");
			//return 0;
		}
		else
		{
			break;
		}
	}while(1);
	
	
	EN_terminalError_t enuTransAmount ;
	EN_terminalError_t enuBelowMaxamount ;
	EN_terminalError_t enuMaxAmount ;
	do
	{
		uint8_t u8flagLoc = 1;
		enuTransAmount = getTransactionAmount(strTermData);
		// check the Validity of the transaction amount 
		if (enuTransAmount == INVALID_AMOUNT)
		{
			printf("Invalid Amount !, please enter a valid amount\n");
			//return 0;
		}
		else
		{
			// set the maximum amount of the transaction
			enuMaxAmount = setMaxAmount(strTermData);
			if (enuMaxAmount == INVALID_MAX_AMOUNT)
			{
				printf("Invalid Max Amount !, please enter a valid Max amount\n");
				//return 0;
				u8flagLoc = 0;
			}
			// check that the trans amount is exceed the max amount or not
			enuBelowMaxamount = isBelowMaxAmount(strTermData);
			if (enuBelowMaxamount == EXCEED_MAX_AMOUNT)
			{
				printf("Transaction Amount Exceed The Maximum Amount !, please enter a valid amount\n");
				//return 0;		
				u8flagLoc = 0;
			}
			
			// From the Flow Chart 
			// Server Module

			// Global Variables for transaction data (pointer to structure)
			ST_transaction strTransaction_data;
			ST_transaction* strTransData = &strTransaction_data;
			strTransData->cardHolderData = strCardHolderData;
			strTransData->terminalData = strTerminal_data;
			
			
			// Transaction Error
			EN_serverError_t enuRecieveTransaction_Data = recieveTransactionData(strTransData);
			// Switch Case Alogrthim Check the Transaction Data Validity for many cases of erros
			switch (enuRecieveTransaction_Data)
			{
			case FRAUD_CARD:
				printf("This account is not found !\n");
				u8flagLoc = 0;
				break;
			case DECLINED_STOLEN_CARD:
				printf("This account is STOLEN and BLOCKED \n");
				break;
			case DECLINED_INSUFFECIENT_FUND:
				saveTransaction(strTransData);
				printf("Transaction Amount Greater Than The Balance Amount !\n");
				u8flagLoc = 0;
				break;

			case INTERNAL_SERVER_ERROR:
				saveTransaction(strTransData);
				printf("The Transaction Can't Be Saved !, Try Again\n");
				u8flagLoc = 0;
				break;
			case APPROVED:
				printf("The Transaction Is Done Successfully, thanks !");
				break;

			default:
				break;
			}
		}
		if(u8flagLoc)
		{
			break;
		}
	}while(1);
	



// Our project is finished
}