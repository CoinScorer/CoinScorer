# Exchange Candle Splitter

Idea is to receive only one stream per exchange/symbol (probably 1minute or via trades) and calculate all timeframes on local side.

## Candle Ticker start/stop

- Type: `Message`
- Start: `MessageType::ExchangeCandleSplitter::cmdCandleTickerMultiStart`
- Stop: `MessageType::ExchangeCandleSplitter::cmdCandleTickerMultiStop`
- Params: `XString strExchange, const TlstSymbolPairs& symbol, TTimeframe timeframe`

``` cpp tab="Send"
SendMessage<XString, TlstSymbolPairs, TTimeframe>(
  MessageType::ExchangeCandleSplitter::cmdCandleTickerMultiStart::id(),
  "binance",
  { stSymbolPair("bnb","btc"),stSymbolPair("btc","usdt") },
  TTimeframe(EnmTimeframe::Min1)
);

SendMessage<XString, TlstSymbolPairs, TTimeframe>(
  MessageType::ExchangeCandleSplitter::cmdCandleTickerMultiStop::id(),
  "binance",
  { stSymbolPair("bnb","btc"),stSymbolPair("btc","usdt") },
  TTimeframe(EnmTimeframe::Min1)
);
```

``` cpp tab="Register"  
RegisterMessageCallback<XString, Currencies::TlstSymbolPairs, TTimeframe>(
  MessageType::ExchangeCandleSplitter::cmdCandleTickerMultiStart::id(),
  boost::bind(&method, this, _1, _2, _3)
);

RegisterMessageCallback<XString, Currencies::TlstSymbolPairs, TTimeframe>(
  MessageType::ExchangeCandleSplitter::cmdCandleTickerMultiStop::id(),
  boost::bind(&method, this, _1, _2, _3)
);
```

## Prepare candle storage

- Type: `Message`
- Message: `MessageType::Storage::cmdStoragePrepare`
- Message: `MessageType::Storage::cmdStorageMultiPrepare`
- Params: `XString strExchange, const stSymbolPair& symbol, TTimeframe timeframe`
- Params: `XString strExchange, const TlstSymbolPairs& symbol, TTimeframe timeframe`

``` cpp tab="Send"
SendMessage<XString,stSymbolPair, TTimeframe>(
  ExchangesData::MessageType::Storage::cmdStoragePrepare::id(),
  exchange,
  symbol,
  timeframe
);

SendMessage<XString,TlstSymbolPairs, TTimeframe>(
  ExchangesData::MessageType::Storage::cmdStoragePrepare::id(),
  exchange,
  symbol,
  timeframe
);
```

``` cpp tab="Register"
RegisterMessageCallback<XString, stSymbolPair, TTimeframe>(
  MessageType::Storage::cmdStoragePrepare::id(),
  boost::bind(&method, this, _1, _2, _3)
);

RegisterMessageCallback<XString, TlstSymbolPairs, TTimeframe>(
  MessageType::Storage::cmdStorageMultiPrepare::id(),
  boost::bind(&method, this, _1, _2, _3)
);
```

## Request latest price

- Type: `Request`
- Message: `MessageType::Storage::requestLatestPrice`
- Returns: `timeCandleStick:stTimeCandleStick`
- Params: `XString strExchange, const stSymbolPair& symbol`

``` cpp tab="Send"
SendRequest<stTimeCandleStick>(
  MessageType::Storage::requestLatestPrice::id(),
  exchange,
  symbol
);
```

``` cpp tab="Register"
RegisterRequestCallback<stTimeCandleStick, XString, stSymbolPair>(
  MessageType::Storage::requestLatestPrice::id(),
  boost::bind(&method, this, _1, _2)
);
```

## Request known pairs

- Type: `Request`
- Message: `MessageType::Storage::requestKnownPairs`
- Returns: `timeCandleStick:stTimeCandleStick`
- Params: `XString strExchange`

``` cpp tab="Send"
SendRequest<TlstSymbolPairs,XString>(
  Modules::ExchangesData::MessageType::Storage::requestKnownPairs::id(),
  exchange
);
```

``` cpp tab="Register"
RegisterRequestCallback<TlstSymbolPairs, XString>(
  MessageType::Storage::requestKnownPairs::id(),
  boost::bind(&method, this, _1)
);
```

## Demand storage data

- Type: `Demand`
- Message: `MessageType::Storage::requestKnownPairs`
- Returns: `candleData:XCandlesGapContainerSimple`
- Params: `XString strExchange, const stSymbolPair& symbol, TTimeframe timeframe, TTimestampInterval dataInterval`

``` cpp tab="Send"
  
SendDemand<XCandlesGapContainerSimple, XString, stSymbolPair, TTimeframe, TTimestampInterval>(
  MessageType::Storage::demandStorageGetData::id(),
  boost::bind(&method, this, _1),
  exchange,
  symbol,
  timeframe,
  interval
);
```

``` cpp tab="Register"
RegisterDemandCallback<XCandlesGapContainerSimple,XString,stSymbolPair,TTimeframe,TTimestampInterval>(
  MessageType::Storage::demandStorageGetData::id(),
  boost::bind(&method, this, _1, _2, _3, _4, _5)
);

```

## Storage Candle tick

Notifies that calculated symbol in storage was updated

- Type: `Message`
- Message: `MessageType::Storage::onCandleTick(exchange, symbol,timeframe)`
- Params: `const stTimeCandleStick& timeCandle`

``` cpp tab="Send"
SendMessage<stTimeCandleStick>(
  MessageType::Storage::onCandleTick(exchange, symbol,timeframe),
  timeCandleStick
);
```

``` cpp tab="Register"
RegisterMessageCallback<stTimeCandleStick>(
  MessageType::Storage::onCandleTick(exchange, symbol, timeframe),
  boost::bind(&method, this, _1)
);

```

## Candles updated in storage

Notifies that all calculated candles were updated (instead of listening several timeframes, storage will listen one data stream and calculate all others 1m -> 5m,10m,...)

- Type: `Message`
- Message: `MessageType::Storage::onCandleUpdated(exchange, symbol,timeframe)`
- Params: `originalCandle:stTimeCandleStick`

``` cpp tab="Send"
SendMessage<stTimeCandleStick>(
  MessageType::Storage::onCandleUpdated(exchange, symbol,timeframe),
  timeCandleStick
);
```

``` cpp tab="Register"
RegisterMessageCallback<stTimeCandleStick>(
  MessageType::Storage::onCandleUpdated(exchange, symbol, timeframe),
  boost::bind(&method, this, _1)
);

```
