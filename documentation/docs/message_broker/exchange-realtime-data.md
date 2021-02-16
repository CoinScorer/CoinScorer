# Exchange Realtime Data

## Candle Ticker start/stop

- Type: `Message`
- Start: `MessageType::ExchangeDataOnline::cmdCandleTickerStart`
- Stop: `MessageType::ExchangeDataOnline::cmdCandleTickerStop`
- Params: `stExchangeId exchangeId, const stSymbolPair& symbol, timeframe_t timeframe`

``` cpp tab="Send"
SendMessage<stExchangeId, stSymbolPair, timeframe_t>(
  MessageType::ExchangeDataOnline::cmdCandleTickerStart::id(),
  exchangeBinanceId,
  stSymbolPair("bnb","btc"),
  timeframe_t(EnmTimeframe::Min1)
);

SendMessage<stExchangeId, stSymbolPair, timeframe_t>(
  MessageType::ExchangeDataOnline::cmdCandleTickerStop::id(),
  exchangeBinanceId,
  stSymbolPair("bnb","btc"),
  timeframe_t(EnmTimeframe::Min1)
);
```

``` cpp tab="Register"  
RegisterMessageCallback<stExchangeId, stSymbolPair, timeframe_t>(
  MessageType::ExchangeDataOnline::cmdCandleTickerStart::id(),
  boost::bind(&method, this, _1, _2, _3)
);

RegisterMessageCallback<stExchangeId, stSymbolPair, timeframe_t>(
  MessageType::ExchangeDataOnline::cmdCandleTickerStop::id(),
  boost::bind(&method, this, _1, _2, _3)
);
```

## HighRes Candle Ticker start/stop

- Type: `Message`
- Start: `MessageType::ExchangeDataOnline::cmdCandleTickerHigResolutionStart`
- Stop: `MessageType::ExchangeDataOnline::cmdCandleTickerHigResolutionStop`
- Params: `stExchangeId exchangeId, const stSymbolPair& symbol, timeframe_t timeframe`

``` cpp tab="Send"
SendMessage<stExchangeId, stSymbolPair, timeframe_t>(
  MessageType::ExchangeDataOnline::cmdCandleTickerHigResolutionStart::id(),
  exchangeBinanceId,
  stSymbolPair("bnb","btc"),
  timeframe_t(EnmTimeframe::Min1)
);

SendMessage<stExchangeId, stSymbolPair, timeframe_t>(
  MessageType::ExchangeDataOnline::cmdCandleTickerHigResolutionStop::id(),
  exchangeBinanceId,
  stSymbolPair("bnb","btc"),
  timeframe_t(EnmTimeframe::Min1)
);
```

``` cpp tab="Register"
RegisterMessageCallback<stExchangeId, stSymbolPair, timeframe_t>(
  MessageType::ExchangeDataOnline::cmdCandleTickerHigResolutionStart::id(),
  boost::bind(&method, this, _1, _2, _3)
);

RegisterMessageCallback<stExchangeId, stSymbolPair, timeframe_t>(
  MessageType::ExchangeDataOnline::cmdCandleTickerHigResolutionStop::id(),
  boost::bind(&method, this, _1, _2, _3)
);
```

## Candle ticker

Ticker message for normal and high-resolution ticker.

- Type: `Message`
- Message: `MessageType::ExchangeDataOnline::onCandleTickerTick::id(exchange, symbol, timeframe)`
- Params: `tradeData:stTimeCandleStick`

``` cpp tab="Register"
RegisterMessageCallback<stTimeCandleStick>(
  MessageType::ExchangeDataOnline::onCandleTickerTick::id(exchangeId, pair, timeframe),
  boost::bind(&method, this, _1)
);
```

``` cpp tab="Send"
SendMessage<stTimeCandleStick>(
  MessageType::ExchangeDataOnline::onCandleTickerTick::id(exchangeId, symbol, timeframe),
  dataCandleStick
);
```

## Trade Ticker start/stop

- Type: `Message`
- Start: `MessageType::ExchangeDataOnline::cmdTradeTickerStart`
- Stop: `MessageType::ExchangeDataOnline::cmdTradeTickerStop`
- Params: `stExchangeId exchangeId, const stSymbolPair& symbol`

``` cpp tab="Send"
SendMessage<stExchangeId, stSymbolPair>(
  MessageType::ExchangeDataOnline::cmdTradeTickerStart::id(),
  exchangeBinanceId,
  stSymbolPair("bnb","btc"),
);

SendMessage<stExchangeId, stSymbolPair>(
  MessageType::ExchangeDataOnline::cmdTradeTickerStop::id(),
  exchangeBinanceId,
  stSymbolPair("bnb","btc"),
);
```

``` cpp tab="Register"
RegisterMessageCallback<stExchangeId, stSymbolPair>(
  MessageType::ExchangeDataOnline::cmdTradeTickerStart::id(),
  boost::bind(&method, this, _1, _2)
);

RegisterMessageCallback<stExchangeId, stSymbolPair>(
  MessageType::ExchangeDataOnline::cmdTradeTickerStop::id(),
  boost::bind(&method, this, _1, _2)
);
```

## Trade ticker

- Type: `Message`
- Message: `MessageType::ExchangeDataOnline::onTradeTick::id(exchange, symbol)`
- Params: `tradeData:stTimeTradeData`

``` cpp tab="Register"
RegisterMessageCallback<stTimeTradeData>(
  MessageType::ExchangeDataOnline::onTradeTick::id(exchange, pair),
  boost::bind(&method, this, _1)
);
```

``` cpp tab="Send"
SendMessage<stTimeTradeData>(
  MessageType::ExchangeDataOnline::onTradeTick::id(exchange, symbol),
  dataTradeTick
);
```


## Market Ticker start/stop

- Type: `Message`
- Start: `MessageType::ExchangeDataOnline::cmdMarketTickerStart`
- Stop: `MessageType::ExchangeDataOnline::cmdMarketTickerStop`
- Params: `stExchangeId exchangeId`

``` cpp tab="Send"
SendMessage<stExchangeId>(
  MessageType::ExchangeDataOnline::cmdMarketTickerStart::id(),
  exchangeBinanceId
);

SendMessage<stExchangeId, stSymbolPair, timeframe_t>(
  MessageType::ExchangeDataOnline::cmdMarketTickerStop::id(),
  exchangeBinanceId
);
```

``` cpp tab="Register"  
RegisterMessageCallback<stExchangeId>(
  MessageType::ExchangeDataOnline::cmdMarketTickerStart::id(),
  boost::bind(&method, this, _1)
);

RegisterMessageCallback<stExchangeId>(
  MessageType::ExchangeDataOnline::cmdMarketTickerStop::id(),
  boost::bind(&method, this, _1)
);
```

## Market ticker

- Type: `Message`
- Message: `MessageType::ExchangeDataOnline::onMarketTick::id(exchange)`
- Params: `tradeData:TlstMarketTickers`

``` cpp tab="Register"
RegisterMessageCallback<TlstMarketTickers>(
  MessageType::ExchangeDataOnline::onMarketTick::id(exchange),
  boost::bind(&method, this, _1)
);
```

``` cpp tab="Send"
SendMessage<TlstMarketTickers>(
  MessageType::ExchangeDataOnline::onMarketTick::id(exchange ),
  lstMarketTicks
);
```
