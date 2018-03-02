//---------------------------------------------------------------------------
#ifndef SBittrexConnectorH
#define SBittrexConnectorH

#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Vcl.ComCtrls.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
#include "SHmacSha512.h"
#include "SCryptoTrader.h"
#include <vector>

class TCurrencyList;
class TBalance;
class TMarketSummary;

class TBittrexConnector
{
private:
	TIdSSLIOHandlerSocketOpenSSL *FIdSSLIOHandlerSocketOpenSSL;

	UnicodeString __fastcall RequestCurrencies();
	UnicodeString __fastcall RequestBalance();
	UnicodeString __fastcall RequestMarketSummaries();
	UnicodeString __fastcall RequestMarketSummary(UnicodeString aCurrency1, UnicodeString aCurrency2);

	UnicodeString __fastcall ParseCurrencies(UnicodeString aJsonStr,TCurrencyList* aCurrencyList);
	UnicodeString __fastcall ParseBalance(UnicodeString aJsonStr,TBalance* aBalance);
	UnicodeString __fastcall ParseMarketSummaries(UnicodeString aJsonStr, std::vector<TMarketSummary>& aMarketSummaryVect);
	UnicodeString __fastcall ParseMarketSummary(UnicodeString aJsonStr, TMarketSummary& aMarketSummary);

	UnicodeString __fastcall GetTimeStampDate(UnicodeString aBittrexStrTimeStamp);
	UnicodeString __fastcall GetTimeStampTime(UnicodeString aBittrexStrTimeStamp);

public:
	UnicodeString ApiKey;
	UnicodeString SecretKey;

	__fastcall TBittrexConnector();
	__fastcall ~TBittrexConnector();

	UnicodeString __fastcall RequestOpenOrders();

	void __fastcall UpdateCurrencyList(TCurrencyList* aCurrencyList);
	void __fastcall UpdateBalance(TBalance* aBalance);
	void __fastcall GetMarketSummaries(std::vector<TMarketSummary>& aMarketSummaryVect);
	void __fastcall GetMarketSummary(UnicodeString aCurrency1, UnicodeString aCurrency2, TMarketSummary& aMarketSummary);
};

#endif
