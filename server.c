#include <stdio.h>
#include <string.h>

#include "Types.h"


#include "server.h"


ST_accountsDB_t Server_astrAccDB[max_Size] = {{2000.0 , RUNNING, "8989374615436851"},{1000.0 , BLOCKED, "5804856076043875"},
								              {3000.0 , RUNNING, "1234574615436851"},{20000.0, BLOCKED, "3987007076043875"},
								              {4000.0 , RUNNING, "5989568315436851"},{5000.0 , BLOCKED, "0693586076043875"},
								              {5000.0 , RUNNING, "7689874665436851"},{10000.0, BLOCKED, "5802507001253875"},
								              {10000.0, RUNNING, "6389374255436851"},{4000.0 , BLOCKED, "2360700702043875"}
								             };

ST_transaction Server_astrTransDB[max_Size] = {0};

uint8_t Server_u8AccNum = 0;

EN_transStat_t recieveTransactionData(ST_transaction *transData)
{
	EN_serverError_t enuValidStatusCpy     = isValidAccount(&transData->cardHolderData,Server_astrAccDB);
	EN_serverError_t enuAmountStatusCpy    = isAmountAvailable(&transData->terminalData)                ;
	EN_serverError_t enuSaveTransStatusCpy = saveTransaction(transData)                                 ;
	EN_serverError_t enuAccountStatusCpy   = isAccountBlocked(Server_astrAccDB);
	if(enuValidStatusCpy     == ACCOUNT_NOT_FOUND)
	{
		return FRAUD_CARD;
	}
	if(enuAccountStatusCpy == BLOCKED_ACCOUNT)
	{
		return DECLINED_STOLEN_CARD;

	}
	if(enuAmountStatusCpy    == LOW_BALANCE)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
	if(enuSaveTransStatusCpy == SAVING_FAILED)
	{
		return INTERNAL_SERVER_ERROR;
	}
	printf("Balance before Transaction : %f\n",Server_astrAccDB[Server_u8AccNum].balance);
	Server_astrAccDB[Server_u8AccNum].balance -= transData->terminalData.transAmount   ;
	printf("Balance after  Transaction : %f\n",Server_astrAccDB[Server_u8AccNum].balance);
	
	return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t enuValidStatus = ACCOUNT_NOT_FOUND ;
	for(Server_u8AccNum = 0;Server_u8AccNum < max_Size ;Server_u8AccNum++)
	{
		if(strcmp(cardData->primaryAccountNumber,accountRefrence[Server_u8AccNum].primaryAccountNumber) == 0)
		{
			enuValidStatus = SERVER_OK;
			break;
		}
	}
	return enuValidStatus;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
	EN_serverError_t enuAmountStatus;
	if((termData->transAmount) > (Server_astrAccDB[Server_u8AccNum].balance))
	{
		enuAmountStatus = LOW_BALANCE;
	}
	else
	{
		enuAmountStatus = SERVER_OK;
	}
	return enuAmountStatus;
}
EN_serverError_t saveTransaction(ST_transaction *transData)
{
	EN_serverError_t enuSaveTransStatus = SAVING_FAILED;
	static uint8_t u8cntrLoc = 0;
	transData->transactionSequenceNumber = u8cntrLoc;
	if(transData->transactionSequenceNumber < max_Size)
	{
		Server_astrTransDB[u8cntrLoc].cardHolderData            = transData->cardHolderData               ;
		Server_astrTransDB[u8cntrLoc].terminalData              = transData->terminalData                 ;
		Server_astrTransDB[u8cntrLoc].transState                = transData->transState                   ;
		Server_astrTransDB[u8cntrLoc].transactionSequenceNumber = transData->transactionSequenceNumber + 1;
		u8cntrLoc++;
		enuSaveTransStatus = SERVER_OK;
	}
	return enuSaveTransStatus;
}

EN_serverError_t isAccountBlocked(ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t enuAccountStatus;
	if(accountRefrence[Server_u8AccNum].state == BLOCKED)
	{
		enuAccountStatus = BLOCKED_ACCOUNT;
	}
	else
	{
		enuAccountStatus = SERVER_OK;
	}
	return enuAccountStatus;
	
}