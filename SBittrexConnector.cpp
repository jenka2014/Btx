#pragma hdrstop

#include "SBittrexConnector.h"
#include <System.DateUtils.hpp>
#include <dbxjson.hpp>
#include <System.StrUtils.hpp>

#include "SMainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TBittrexConnector::TBittrexConnector()
{
	ApiKey="";
	SecretKey="";
	FIdSSLIOHandlerSocketOpenSSL=new TIdSSLIOHandlerSocketOpenSSL(NULL);
}

__fastcall TBittrexConnector::~TBittrexConnector()
{
	delete FIdSSLIOHandlerSocketOpenSSL;
}

//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::RequestCurrencies()
{
	UnicodeString responseStr="";
	UnicodeString url;

	TIdHTTP* HTTP;
	HTTP=new TIdHTTP(NULL);
	HTTP->IOHandler=FIdSSLIOHandlerSocketOpenSSL;

	HTTP->HandleRedirects=true;
	HTTP->AllowCookies=true;
	HTTP->ConnectTimeout=5000;
	HTTP->ReadTimeout=5000;

	if(HTTP){
		try{
			if(HTTP->Connected())
				HTTP->Disconnect();

			HTTP->Request->UserAgent="Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0";
			HTTP->Request->Accept="text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";
			url="https://bittrex.com//api//v1.1//public//getcurrencies";

			responseStr=HTTP->Get(url);
			HTTP->Disconnect();

			try{
				HTTP->Socket->Close();
			}catch(...){
				HTTP->Disconnect();
				MainForm->MemoMessages->Lines->Add("Close socket error!");
			}
		}
		catch(Exception &e){
			MainForm->MemoMessages->Lines->Add("Error! "+e.Message);
		}
	}
	delete HTTP;
	HTTP = NULL;
	return responseStr;
}
//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::RequestBalance()
{
	UnicodeString responseStr="";

	TIdHTTP* HTTP;
	HTTP=new TIdHTTP(NULL);
	HTTP->IOHandler=FIdSSLIOHandlerSocketOpenSSL;

	HTTP->HandleRedirects=true;
	HTTP->AllowCookies=true;
	HTTP->ConnectTimeout=5000;
	HTTP->ReadTimeout=5000;

	AnsiString secretKey=SecretKey;
	AnsiString nonce=IntToStr(System::Dateutils::DateTimeToUnix(Now()));
	AnsiString url="https://bittrex.com/api/v1.1/account/getbalances?apikey="+ApiKey+"&nonce="+nonce;

	char* hash = hmac_sha512_str(secretKey.c_str(), secretKey.Length(), url.c_str());
	AnsiString sign=AnsiString(hash);

	if(HTTP){
		try{
			if(HTTP->Connected())
				HTTP->Disconnect();

			HTTP->Request->ContentEncoding="utf-8";
			HTTP->Request->UserAgent="Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0";
			HTTP->Request->Accept="text/utf-8,application/json;q=0.9,*/*;q=0.8";
			HTTP->Request->CustomHeaders->Add("apisign:"+sign);

			responseStr=HTTP->Get(url);
			HTTP->Disconnect();

			try{
				HTTP->Socket->Close();
			}catch(...){
				HTTP->Disconnect();
			}
		}
		catch(Exception &e){
			MainForm->MemoMessages->Lines->Add("Error! "+e.Message);
		}
	}
	delete HTTP;
	HTTP = NULL;

	return responseStr;
}
//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::RequestMarketSummaries()
{
	UnicodeString responseStr="";
	UnicodeString url;

	TIdHTTP* HTTP;
	HTTP=new TIdHTTP(NULL);
	HTTP->IOHandler=FIdSSLIOHandlerSocketOpenSSL;

	HTTP->HandleRedirects=true;
	HTTP->AllowCookies=true;
	HTTP->ConnectTimeout=5000;
	HTTP->ReadTimeout=5000;

	if(HTTP){
		try{
			if(HTTP->Connected())
				HTTP->Disconnect();

			HTTP->Request->UserAgent="Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0";
			HTTP->Request->Accept="text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";
			url="https://bittrex.com/api/v1.1/public/getmarketsummaries";
			responseStr=HTTP->Get(url);
			HTTP->Disconnect();

			try{
				HTTP->Socket->Close();
			}catch(...){
				HTTP->Disconnect();
			}
		}
		catch(Exception &e){
			MainForm->MemoMessages->Lines->Add("Error! "+e.Message);
		}
	}
	delete HTTP;
	HTTP = NULL;

	return responseStr;
}
//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::RequestMarketSummary(UnicodeString aCurrency1, UnicodeString aCurrency2)
{
	UnicodeString responseStr="";
	UnicodeString url;

	TIdHTTP* HTTP;
	HTTP=new TIdHTTP(NULL);
	HTTP->IOHandler=FIdSSLIOHandlerSocketOpenSSL;

	HTTP->HandleRedirects=true;
	HTTP->AllowCookies=true;
	HTTP->ConnectTimeout=5000;
	HTTP->ReadTimeout=5000;

	if(HTTP){
		try{
			if(HTTP->Connected())
				HTTP->Disconnect();

			HTTP->Request->UserAgent="Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0";
			HTTP->Request->Accept="text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";
			url="https://bittrex.com/api/v1.1/public/getmarketsummary?market="+aCurrency1.LowerCase()+"-"+aCurrency2.LowerCase();

			responseStr=HTTP->Get(url);
			HTTP->Disconnect();

			try{
				HTTP->Socket->Close();
			}catch(...){
				HTTP->Disconnect();
			}
		}
		catch(Exception &e){
			MainForm->MemoMessages->Lines->Add("Error! "+e.Message);
		}
	}
	delete HTTP;
	HTTP = NULL;

	return responseStr;
}
//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::RequestOpenOrders()
{
	UnicodeString responseStr="";

	TIdHTTP* HTTP;
	HTTP=new TIdHTTP(NULL);
	HTTP->IOHandler=FIdSSLIOHandlerSocketOpenSSL;

	HTTP->HandleRedirects=true;
	HTTP->AllowCookies=true;
	HTTP->ConnectTimeout=5000;
	HTTP->ReadTimeout=5000;

	AnsiString secretKey=SecretKey;
	AnsiString nonce=IntToStr(System::Dateutils::DateTimeToUnix(Now()));
	AnsiString url="https://bittrex.com/api/v1.1/market/getopenorders?apikey="+ApiKey+"&nonce="+nonce;

	char* hash = hmac_sha512_str(secretKey.c_str(), secretKey.Length(), url.c_str());
	AnsiString sign=AnsiString(hash);

	if(HTTP){
		try{
			if(HTTP->Connected())
				HTTP->Disconnect();

			HTTP->Request->ContentEncoding="utf-8";
			HTTP->Request->UserAgent="Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0";
			HTTP->Request->Accept="text/utf-8,application/json;q=0.9,*/*;q=0.8";
			HTTP->Request->CustomHeaders->Add("apisign:"+sign);

			responseStr=HTTP->Get(url);
			HTTP->Disconnect();

			try{
				HTTP->Socket->Close();
			}catch(...){
				HTTP->Disconnect();
			}
		}
		catch(Exception &e){
			MainForm->MemoMessages->Lines->Add("Error! "+e.Message);
		}
	}
	delete HTTP;
	HTTP = NULL;

	return responseStr;
}
//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::ParseCurrencies(UnicodeString aJsonStr, TCurrencyList* aCurrencyList)
{
	UnicodeString resultStr="";

	TJSONPair* jsonMetaParamPair=NULL;
	AnsiString strMetaParam="";
	TJSONArray* jsonResultArray=NULL;
	bool requestResult=false;
	TJSONObject* jsonCurrencyObject=NULL;

	aCurrencyList->Clear();

	TJSONObject *jsonDocumentObject=new TJSONObject;
	jsonDocumentObject=(TJSONObject*)TJSONObject::ParseJSONValue(aJsonStr);
	if(jsonDocumentObject!=NULL){
		for(int i=0; i<jsonDocumentObject->Count; i++){
			jsonMetaParamPair=jsonDocumentObject->Pairs[i];
			strMetaParam=jsonMetaParamPair->JsonString->ToString();
			//Success param
			if(strMetaParam=="\"success\""){
				AnsiString successStr=jsonMetaParamPair->JsonValue->ToString();
				if(successStr=="true"){
					requestResult=true;
				}else{
					requestResult=false;
					//ShowMessage("Invalid request \"GetCurrencies\"");
				}
			}
			//Message param
			if(strMetaParam=="\"message\""){
				resultStr=jsonMetaParamPair->JsonValue->ToString();
			}
			//Result param
			if(strMetaParam=="\"result\""){
				jsonResultArray=(TJSONArray*)jsonMetaParamPair->JsonValue;
				for(int i=0; i<jsonResultArray->Count; i++){
					jsonCurrencyObject=(TJSONObject*)jsonResultArray->Items[i];
					TCurrencyInfo* currencyInfo=new TCurrencyInfo();
					currencyInfo->Currency=ReplaceStr(jsonCurrencyObject->GetValue("Currency")->ToString(),"\"","");
					currencyInfo->CurrencyLong=ReplaceStr(jsonCurrencyObject->GetValue("CurrencyLong")->ToString(),"\"","");
					currencyInfo->MinConfirmation=jsonCurrencyObject->GetValue("MinConfirmation")->ToString();
					currencyInfo->TxFee=jsonCurrencyObject->GetValue("TxFee")->ToString();
					currencyInfo->IsActive=jsonCurrencyObject->GetValue("IsActive")->ToString();
					currencyInfo->CoinType=ReplaceStr(jsonCurrencyObject->GetValue("CoinType")->ToString(),"\"","");;
					aCurrencyList->Add(currencyInfo);
				}
			}
		}
	}

	delete jsonDocumentObject;
	return resultStr;
}
//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::ParseBalance(UnicodeString aJsonStr,TBalance* aBalance)
{
	UnicodeString resultStr="";

	TJSONPair* jsonMetaParamPair=NULL;
	AnsiString strMetaParam="";
	TJSONArray* jsonResultArray=NULL;
	bool requestResult=false;
	TJSONObject* jsonCurrencyObject=NULL;
	AnsiString strBalance="";
	AnsiString strPending="";

	aBalance->Clear();

	TJSONObject *jsonDocumentObject=new TJSONObject;
	jsonDocumentObject=(TJSONObject*)TJSONObject::ParseJSONValue(aJsonStr);
	if(jsonDocumentObject!=NULL){
		for(int i=0; i<jsonDocumentObject->Count; i++){
			jsonMetaParamPair=jsonDocumentObject->Pairs[i];
			strMetaParam=jsonMetaParamPair->JsonString->ToString();
			//Success param
			if(strMetaParam=="\"success\""){
				AnsiString successStr=jsonMetaParamPair->JsonValue->ToString();
				if(successStr=="true"){
					requestResult=true;
				}else{
					requestResult=false;
					//ShowMessage("Invalid request \"GetCurrencies\"");
				}
			}
			//Message param
			if(strMetaParam=="\"message\""){
				resultStr=jsonMetaParamPair->JsonValue->ToString();
			}
			//Result param
			if(strMetaParam=="\"result\""){
				jsonResultArray=(TJSONArray*)jsonMetaParamPair->JsonValue;
				for(int i=0; i<jsonResultArray->Count; i++){
					jsonCurrencyObject=(TJSONObject*)jsonResultArray->Items[i];

					TCurrencyBalance* currencyBalance=new TCurrencyBalance();
					currencyBalance->Currency=ReplaceStr(jsonCurrencyObject->GetValue("Currency")->ToString(),"\"","");
					strBalance=ReplaceStr(jsonCurrencyObject->GetValue("Balance")->ToString(),"\"","");
					strBalance=ReplaceStr(strBalance,".",",");
					currencyBalance->Balance=StrToFloat(strBalance);
					strPending=ReplaceStr(jsonCurrencyObject->GetValue("Pending")->ToString(),"\"","");
					strPending=ReplaceStr(strPending,".",",");
					currencyBalance->Pending=StrToFloat(strPending);
					currencyBalance->CryptoAddress=ReplaceStr(jsonCurrencyObject->GetValue("CryptoAddress")->ToString(),"\"","");
					aBalance->Add(currencyBalance);
				}
			}
		}
	}

	delete jsonDocumentObject;

	return resultStr;
}
//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::ParseMarketSummaries(UnicodeString aJsonStr, std::vector<TMarketSummary>& aMarketSummaryVect)
{
	UnicodeString resultStr="";

	TJSONPair* jsonMetaParamPair=NULL;
	AnsiString strMetaParam="";
	TJSONArray* jsonResultArray=NULL;
	bool requestResult=false;
	TJSONObject* jsonMarketSummaryObject=NULL;

	aMarketSummaryVect.clear();
	TMarketSummary marketSummary;

	TJSONObject *jsonDocumentObject=new TJSONObject;
	jsonDocumentObject=(TJSONObject*)TJSONObject::ParseJSONValue(aJsonStr);
	if(jsonDocumentObject!=NULL){
		for(int i=0; i<jsonDocumentObject->Count; i++){
			jsonMetaParamPair=jsonDocumentObject->Pairs[i];
			strMetaParam=jsonMetaParamPair->JsonString->ToString();
			//Success param
			if(strMetaParam=="\"success\""){
				AnsiString successStr=jsonMetaParamPair->JsonValue->ToString();
				if(successStr=="true"){
					requestResult=true;
				}else{
					requestResult=false;
					//ShowMessage("Invalid request \"MarketSummaries\"");
				}
			}
			//Message param
			if(strMetaParam=="\"message\""){
				resultStr=jsonMetaParamPair->JsonValue->ToString();
			}
			//Result param
			UnicodeString marketName;
			UnicodeString timeStamp;
			UnicodeString created;
			if(strMetaParam=="\"result\""){
				jsonResultArray=(TJSONArray*)jsonMetaParamPair->JsonValue;
				for(int i=0; i<jsonResultArray->Count; i++){
					jsonMarketSummaryObject=(TJSONObject*)jsonResultArray->Items[i];
					marketName=ReplaceStr(jsonMarketSummaryObject->GetValue("MarketName")->ToString(),"\"","");
					marketSummary.MarketName=marketName;
					marketSummary.High=jsonMarketSummaryObject->GetValue("High")->ToString();
					marketSummary.Low=jsonMarketSummaryObject->GetValue("Low")->ToString();
					marketSummary.Volume=jsonMarketSummaryObject->GetValue("Volume")->ToString();
					marketSummary.Last=jsonMarketSummaryObject->GetValue("Last")->ToString();
					marketSummary.BaseVolume=jsonMarketSummaryObject->GetValue("BaseVolume")->ToString();
					timeStamp=ReplaceStr(jsonMarketSummaryObject->GetValue("TimeStamp")->ToString(),"\"","");
					marketSummary.TimeStamp=GetTimeStampDate(timeStamp)+" "+GetTimeStampTime(timeStamp);
					marketSummary.Bid=jsonMarketSummaryObject->GetValue("Bid")->ToString();
					marketSummary.Ask=jsonMarketSummaryObject->GetValue("Ask")->ToString();
					marketSummary.OpenBuyOrders=jsonMarketSummaryObject->GetValue("OpenBuyOrders")->ToString();
					marketSummary.OpenSellOrders=jsonMarketSummaryObject->GetValue("OpenSellOrders")->ToString();
					marketSummary.PrevDay=jsonMarketSummaryObject->GetValue("PrevDay")->ToString();
					created=ReplaceStr(jsonMarketSummaryObject->GetValue("Created")->ToString(),"\"","");
					marketSummary.Created=created;
					aMarketSummaryVect.push_back(marketSummary);
				}
			}
		}
	}

	delete jsonDocumentObject;

	return resultStr;
}
//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::ParseMarketSummary(UnicodeString aJsonStr, TMarketSummary& aMarketSummary)
{
	UnicodeString resultStr="";

	TJSONPair* jsonMetaParamPair=NULL;
	UnicodeString strMetaParam="";
	TJSONArray* jsonResultArray=NULL;
	bool requestResult=false;
	TJSONObject* jsonMarketSummaryObject=NULL;

	TJSONObject *jsonDocumentObject=new TJSONObject;
	jsonDocumentObject=(TJSONObject*)TJSONObject::ParseJSONValue(aJsonStr);
	if(jsonDocumentObject!=NULL){
		for(int i=0; i<jsonDocumentObject->Count; i++){
			jsonMetaParamPair=jsonDocumentObject->Pairs[i];
			strMetaParam=jsonMetaParamPair->JsonString->ToString();
			//Success param
			if(strMetaParam=="\"success\""){
				AnsiString successStr=jsonMetaParamPair->JsonValue->ToString();
				if(successStr=="true"){
					requestResult=true;
				}else{
					requestResult=false;
					ShowMessage("Invalid request \"GetCurrencies\"");
				}
			}
			//Message param
			if(strMetaParam=="\"message\""){
				resultStr=jsonMetaParamPair->JsonValue->ToString();
			}
			//Result param
			UnicodeString timeStamp="";
			if(strMetaParam=="\"result\""){
				jsonResultArray=(TJSONArray*)jsonMetaParamPair->JsonValue;
				for(int i=0; i<jsonResultArray->Count; i++){
					jsonMarketSummaryObject=(TJSONObject*)jsonResultArray->Items[i];
					aMarketSummary.MarketName=jsonMarketSummaryObject->GetValue("MarketName")->ToString();
					aMarketSummary.High=jsonMarketSummaryObject->GetValue("High")->ToString();
					aMarketSummary.Low=jsonMarketSummaryObject->GetValue("Low")->ToString();
					aMarketSummary.Volume=jsonMarketSummaryObject->GetValue("Volume")->ToString();
					aMarketSummary.Last=jsonMarketSummaryObject->GetValue("Last")->ToString();
					aMarketSummary.BaseVolume=jsonMarketSummaryObject->GetValue("BaseVolume")->ToString();
					timeStamp=jsonMarketSummaryObject->GetValue("TimeStamp")->ToString();
					timeStamp=ReplaceStr(jsonMarketSummaryObject->GetValue("TimeStamp")->ToString(),"\"","");
					aMarketSummary.TimeStamp=GetTimeStampDate(timeStamp)+" "+GetTimeStampTime(timeStamp);
					aMarketSummary.Bid=jsonMarketSummaryObject->GetValue("Bid")->ToString();
					aMarketSummary.Ask=jsonMarketSummaryObject->GetValue("Ask")->ToString();
					aMarketSummary.OpenBuyOrders=jsonMarketSummaryObject->GetValue("OpenBuyOrders")->ToString();
					aMarketSummary.OpenSellOrders=jsonMarketSummaryObject->GetValue("OpenSellOrders")->ToString();
					aMarketSummary.PrevDay=jsonMarketSummaryObject->GetValue("PrevDay")->ToString();
					aMarketSummary.Created=jsonMarketSummaryObject->GetValue("Created")->ToString();
				}
			}
		}
	}

	delete jsonDocumentObject;

	return resultStr;
}
//----------------------------------------------------------------------------
void __fastcall TBittrexConnector::UpdateCurrencyList(TCurrencyList* aCurrencyList)
{
	UnicodeString bittrexResponce=RequestCurrencies();
	ParseCurrencies(bittrexResponce, aCurrencyList);
}
//----------------------------------------------------------------------------
void __fastcall TBittrexConnector::UpdateBalance(TBalance* aBalance)
{
	UnicodeString bittrexResponce=RequestBalance();
	ParseBalance(bittrexResponce, aBalance);
}
//----------------------------------------------------------------------------
void __fastcall TBittrexConnector::GetMarketSummaries(std::vector<TMarketSummary>& aMarketSummaryVect)
{
	UnicodeString bittrexResponce=RequestMarketSummaries();
	ParseMarketSummaries(bittrexResponce,aMarketSummaryVect);
}
//----------------------------------------------------------------------------
void __fastcall TBittrexConnector::GetMarketSummary(UnicodeString aCurrency1, UnicodeString aCurrency2, TMarketSummary& aMarketSummary)
{
	UnicodeString bittrexResponce=RequestMarketSummary(aCurrency1,aCurrency2);
	ParseMarketSummary(bittrexResponce,aMarketSummary);
}
//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::GetTimeStampDate(UnicodeString aBittrexStrTimeStamp)
{
	UnicodeString resultStr="";
	UnicodeString year="";
	UnicodeString month="";
	UnicodeString day="";
	int pos=aBittrexStrTimeStamp.Pos("T");
	if(pos>0){
		year=aBittrexStrTimeStamp.SubString(1,4);
		month=aBittrexStrTimeStamp.SubString(6,2);
		day=aBittrexStrTimeStamp.SubString(9,2);
		resultStr=day+"."+month+"."+year;
	}
	return resultStr;
}
//----------------------------------------------------------------------------
UnicodeString __fastcall TBittrexConnector::GetTimeStampTime(UnicodeString aBittrexStrTimeStamp)
{
	UnicodeString resultStr="";
	UnicodeString h="";
	UnicodeString m="";
	UnicodeString s="";
	int pos=aBittrexStrTimeStamp.Pos("T");
	if(pos>0){
		h=aBittrexStrTimeStamp.SubString(12,2);
		m=aBittrexStrTimeStamp.SubString(15,2);
		s=aBittrexStrTimeStamp.SubString(18,2);
		resultStr=h+":"+m+":"+s;
	}
	return resultStr;
}
//------------------------------------------------------------------------------
