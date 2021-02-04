# Exchange Cache

## Request/Demand cached exchange data by interval

- Type: `Request/Demand`
- Message: `MessageType::ExchangeDataCache::demandGetCachedExchangeDataByInterval`
- Returns: `candleData:XCandlesGapContainerSimple`
- Params: `XString strExchange, const stSymbolPair& symbol, TTimeframe timeframe, TTimestampInterval dataInterval`

``` cpp tab="Send"
SendDemand<XCandlesGapContainerSimple, XString, stSymbolPair, TTimeframe, TTimestampInterval>(
  MessageType::ExchangeDataCache::demandGetCachedExchangeDataByInterval::id(),
  boost::bind(&method, this, _1),
  exchange,
  symbol,
  timeframe,
  interval
);
```

``` cpp tab="Register"
RegisterDemandCallback<XCandlesGapContainerSimple,XString,stSymbolPair,TTimeframe,TTimestampInterval>(
  MessageType::ExchangeDataCache::demandGetCachedExchangeDataByInterval::id(),
  boost::bind(&method, this, _1, _2, _3, _4, _5)
);
```

``` cpp tab="Handler"
void method(Atomix::MessageBroker::IDemandEvent<XCandlesGapContainerSimple>* demandEvent, const XString& strExchange, const Modules::Currencies::stSymbolPair& pair, const TTimeframe& tfTimeframe, const TTimestampInterval& tmTimeInterval)
{

}
```

## Request/Demand cached exchange data by amount

- Type: `Request/Demand`
- Message: `MessageType::ExchangeDataCache::demandGetCachedExchangeDataByAmount`
- Returns: `candleData:XCandlesGapContainerSimple`
- Params: `XString strExchange, const stSymbolPair& symbol, TTimeframe timeframe, TTimestamp dataTimestamp, int nAmount`

Note: Requires amount data starting by dataTimestamp. For forward pass `+amount`, for backward `-amount`

``` cpp tab="Send"
SendDemand<XCandlesGapContainerSimple, XString, stSymbolPair, TTimeframe, TTimestamp,int>(
  MessageType::ExchangeDataCache::demandGetCachedExchangeDataByAmount::id(),
  boost::bind(&method, this, _1),
  exchange,
  symbol,
  timestamp,
  amount
);
```

``` cpp tab="Register"
RegisterDemandCallback<XCandlesGapContainerSimple,XString,stSymbolPair,TTimeframe,TTimestamp,int>(
  MessageType::ExchangeDataCache::demandGetCachedExchangeDataByAmount::id(),
  boost::bind(&method, this, _1, _2, _3, _4, _5, _6)
);
```

``` cpp tab="Handler"
void method(Atomix::MessageBroker::IDemandEvent<XCandlesGapContainerSimple>* demandEvent, const XString& strExchange, const Modules::Currencies::stSymbolPair& pair, const TTimeframe& tfTimeframe, const TTimestamp& tmTimeInterval, int nAmount)
{

}
```

## Request/Demand prepare cache of multiple symbols 

- Type: `Message`
- Message: `MessageType::ExchangeDataCache::messagePrecacheExchangeDataMultiple`
- Params: `XLstExchangeDataRequests requestData`

``` cpp tab="Send"
SendMessage<XLstExchangeDataRequests>(
  MessageType::ExchangeDataCache::messagePrecacheExchangeDataMultiple::id(),
  requestData
);
```

``` cpp tab="Register"
RegisterMessageCallback<XLstExchangeDataRequests>(
  MessageType::ExchangeDataCache::messagePrecacheExchangeDataMultiple::id(),
  boost::bind(&method, this, _1)
);
```

``` cpp tab="Handler"
void method(XLstExchangeDataRequests requestData)
{

}
```
